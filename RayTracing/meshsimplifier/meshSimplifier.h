//
//  meshsimplifier.h
//  MeshSimplifier
//
//  Created by Ming Yao on 16/1/14.
//

#ifndef MESHSIMPLIFIER_H
#define MESHSIMPLIFIER_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "../renderer.h"
#include "../geometry.h"
#include "Vertex.h"
#include "Face.h"
using std::vector;
using std::unordered_set;
using std::priority_queue;
using namespace RayTracing;
using MyMath::Vec3d;

class MeshSimplifier {
private:
    Mesh& mesh;
public:

    struct Elem {
        // element type to use in the heap
        Vertex* v;
        int timeStamp;

        Elem(Vertex* _v) :
            v(_v), timeStamp(v->timeStamp) {}

        bool operator < (const Elem& r) const {
            return v->cost > r.v->cost;
        }

        inline bool outofdate() const {
            return timeStamp < v->timeStamp;
        }
    };
public:
    vector<Vertex> vertices;
    vector<Face> faces;
    int target_num;			// shrink to this number
    priority_queue<Elem> heap;

    real_t getCost(Vertex*, Vertex*) const;

    void updateCost(Vertex*);

    int collapse(Vertex*, Vertex*);		// return the number of faces it simplified

    void doSimplify();

    void writeBack();

public:
    MeshSimplifier(Mesh& mesh, real_t _ratio);

    void simplify();
};


#endif