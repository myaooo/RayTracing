//
//  intersectable.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "myMath.h"
#include "ray.h"

namespace MyMath{

    // intersection type
    // INSIDE - the ray in travelling from inside to outside of an object
    // OUTSIDE - the ray is travelling in the air
    enum IntersectType{ MISSED = 0, INTERSECTED = 1, INSIDE = 2};

    // base class of all intersectable geometry objects
    class Intersectable{
    public:
        // check whether the ray intersect with the geometry
        virtual bool isIntersect(const Ray & ray) const = 0;
        // do intersection between the ray and the geometry
        // stores the intersecting position in intersectPos
        virtual IntersectType intersect(real_t & intersectPos, const Ray & ray) const = 0;
    };


};

#endif
