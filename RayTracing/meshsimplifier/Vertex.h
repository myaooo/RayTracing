//
//  vertex.h
//  MeshSimplifier
//
//  Created by Ming Yao on 16/1/14.
//

#ifndef VERTEX_H
#define VERTEX_H

#include <unordered_set>
#include "../geometry.h"
#include "Face.h"
using MyMath::Vec3d;
using namespace std;
struct Vertex {
    Vec3d pos;
    int id = -1;
    bool erased = false;
    unordered_set<Vertex*> adjVertex;
    unordered_set<Face*> adjFace;

    int timeStamp = 0;
    real_t cost;
    Vertex* candidate = nullptr;

    Vertex(Vec3d _pos, int _id = -1) :pos(_pos), id(_id) {}

    inline void addFace(Face* f) {
        adjFace.insert(f);
        for (int k = 0; k < 3; k++) {
            if (f->vertex[k] != this)
                adjVertex.insert(f->vertex[k]);
        }
    }

    // change adj_vertex, u to v
    void change_to(Vertex* u, Vertex* v) {
        assert(this != v);
        adjVertex.erase(u);
        adjVertex.insert(v);
    }

};
#endif