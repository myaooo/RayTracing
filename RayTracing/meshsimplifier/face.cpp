//
//  face.cpp
//  MeshSimplifier
//
//  Created by Ming Yao on 16/1/14.
//

#include "Face.h"
#include "Vertex.h"


Face::Face(Vertex* a, Vertex* b, Vertex* c) {
    vertex[0] = a;
    vertex[1] = b;
    vertex[2] = c;
    norm = Vec3d::cross((c->pos - a->pos), ((b->pos - a->pos)));
    norm.normalize();
}

void Face::deleteFrom(Vertex* u, Vertex* v) {
    assert(contain(v));
    for (int k = 0; k < 3; k++) {
        if (vertex[k] != u && vertex[k] != v) {
            vertex[k]->adjFace.erase(this);
            break;
        }
    }
    v->adjFace.erase(this);
    vertex[0] = vertex[1] = vertex[2] = nullptr;
}

void Face::changeTo(Vertex* u, Vertex* v) {
    assert(count(v) == 0);
    assert(count(u) == 1);
    for (int k = 0; k < 3; k++)
    {
        if (vertex[k] == u) vertex[k] = v;
    }
    assert(vertex[0] != vertex[1] && vertex[1] != vertex[2] && vertex[2] != vertex[0]);
    Vec3d newnorm = Vec3d::cross((vertex[2]->pos - vertex[0]->pos),((vertex[1]->pos - vertex[0]->pos)));
    if (newnorm.getNormSqr() > 0)		// sometimes three vertex will be on the same line
        norm = newnorm;
    norm.normalize();
    v->adjFace.insert(this);
}

