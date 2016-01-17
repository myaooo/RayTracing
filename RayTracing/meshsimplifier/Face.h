//
//  face.h
//  MeshSimplifier
//
//  Created by Ming Yao on 16/1/14.
//
#include "../geometry.h"
#ifndef FACE_H
#define FACE_H

#define EDGE_NUM 3

using MyMath::Vec3d;

struct Vertex;

struct Face {
public:
    Vertex* vertex[EDGE_NUM];
    Vec3d norm;

    Face(Vertex* a, Vertex* b, Vertex* c);

    // delete this face (containing u, v) when collapsing from u to v
    void deleteFrom(Vertex* u, Vertex* v);

    // change vertex u to v when collapsing from u to v
    void changeTo(Vertex* u, Vertex* v);

    inline bool contain(Vertex* v) const {
        return (v == vertex[0]) + (v == vertex[1]) + (v == vertex[2]) == 1;
    }

    inline int count(Vertex* v) const {
        return (v == vertex[0]) + (v == vertex[1]) + (v == vertex[2]);
    }

};



#endif