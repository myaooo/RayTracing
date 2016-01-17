

#include <list>
#include <limits>
#include <algorithm>
#include <omp.h>
#include "meshSimplifier.h"
using namespace std;

// A simple, fast, and effective polygon reduction algorithm
// Melax, Stan, 1998

MeshSimplifier::MeshSimplifier(Mesh& _mesh, real_t ratio) : mesh(_mesh) {
    int nvertex = mesh.vertices.size();
    int nface = mesh.faceIdx.size();
    target_num = nface * ratio;

    vertices.reserve(nvertex);		// in case it change size
    faces.reserve(nface);

    for (int k = 0; k < nvertex;k++) {
        vertices.emplace_back(mesh.vertices[k], k);
    }

    for (int k = 0; k < nface; k++) {
        auto & tmp = mesh.faceIdx[k];
        int a = tmp[0], b = tmp[1], c = tmp[2];
        faces.emplace_back(&vertices[a], &vertices[b], &vertices[c]);
        vertices[a].addFace(&faces[k]);
        vertices[b].addFace(&faces[k]);
        vertices[c].addFace(&faces[k]);
    }

//#pragma omp parallel for schedule(dynamic)
    for (int k = 0; k < nvertex; ++k) {
        updateCost(&vertices[k]);
    }
    /*
    *for (auto& vertex: vertices) update_cost(&vertex);
    */
}

real_t MeshSimplifier::getCost(Vertex* u, Vertex* v) const {
    list<Face*> common_faces;
    // common adj triangle of u and v
    copy_if(begin(u->adjFace), end(u->adjFace),
        back_inserter(common_faces),
        [&v](Face* f) -> bool {
        return v->adjFace.count(f) > 0;
    });

    real_t max = 0;
    for (const auto & uface : u->adjFace) {
        real_t min = 1;
        for (auto & cf : common_faces) {
            real_t dot = 1 - Vec3d::dot(uface->norm,cf->norm);
            min = getMin(min, dot);
        }
        max = getMax(max, min);
    }
    return (u->pos - v->pos).getNorm() * max;
}

void MeshSimplifier::updateCost(Vertex* u) {
    // cost of `I collapse to other`
    if (u->adjVertex.size() == 0) {
        u->erased = true;
        return;
    }

    real_t min = DBL_MAX;
    u->candidate = nullptr;

    for (const auto & uvertex : u->adjVertex) {
        assert(!uvertex->erased);
        real_t tempcost = getCost(u, uvertex);
        if (tempcost < min) {
            min = tempcost;
            u->candidate = uvertex;
        }
    }
    assert(u->candidate != nullptr);
    u->cost = min;
    u->timeStamp++;
//#pragma omp critical
    heap.push(u);
}

int MeshSimplifier::collapse(Vertex* u, Vertex* v) {
    // move u onto v
    u->erased = true;
    int ret = 0;

    for (auto itr = begin(u->adjFace); itr != end(u->adjFace);) {
        assert((*itr)->contain(u));
        if (v->adjFace.count(*itr)) {
            (*itr)->deleteFrom(u, v);
            ret++;
            u->adjFace.erase(itr++);
        }
        else {
            (*itr)->changeTo(u, v);
            ++itr;
        }
    }

    for (auto uvertex : u->adjVertex)
        if (!uvertex->erased && uvertex != v) {
            uvertex->change_to(u, v);
            v->adjVertex.insert(uvertex);
        }
    v->adjVertex.erase(u);		// this must be put after the above line

    /*
    *#pragma omp parallel
    *#pragma omp single
    *    {
    *        for (auto itr = u->adjVertex.begin(); itr != u->adjVertex.end(); ++itr)
    *    #pragma omp task firstprivate(itr)
    *            update_cost(*itr);
    *    #pragma omp taskwait
    *    }
    */
    for_each(u->adjVertex.begin(), u->adjVertex.end(),
        [&](Vertex* n) {
        updateCost(n);
    });
    return ret;
}

void MeshSimplifier::doSimplify() {
    int nowcnt = faces.size();
    while (nowcnt > target_num && nowcnt > 4) {
        /*// without heap
        *real_t min = numeric_limits<real_t>::max();
        *Vertex* candidate_u;
        *for (auto & u : vertices) {
        *    if (u.erased) continue;
        *    if (update_min(min, u.cost))
        *        candidate_u = &u;
        *}
        */

        // use heap
        auto & ele = heap.top();
        heap.pop();
        if (ele.outofdate()) continue;
        if (ele.v->erased) continue;
        Vertex* candidate_u = ele.v;

        assert(candidate_u != nullptr);
        assert(candidate_u->candidate != nullptr);
        nowcnt -= collapse(candidate_u, candidate_u->candidate);
        if (nowcnt % 1000 == 0)
            cout<<((faces.size() - nowcnt) * 100 / (faces.size() - target_num))<<"%\n";
    }
}

void MeshSimplifier::writeBack() {		// write vertices and faceIdx
    mesh.clear();
    int cnt = 0;
    for (auto & v : vertices) {
        if (!v.erased) mesh.addVertex(v.pos), v.id = cnt++;
        else v.id = -1;
    }

    for (auto & f : faces) {
        bool erased = false;
        for (int k = 0; k < 3;k++)
        {
            if (!f.vertex[k] || f.vertex[k]->erased) 
                erased = true;
        }
        if (erased) continue;
        for (int k = 0; k < 3; k++) {
            if (f.vertex[k]->id == -1) { assert(false); }
        }

        mesh.addFaceIdx(f.vertex[0]->id, f.vertex[1]->id, f.vertex[2]->id);
    }
}

void MeshSimplifier::simplify() {
    doSimplify();
    writeBack();
}
