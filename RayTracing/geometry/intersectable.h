//
//  intersectable.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "../geometry/myMath.h"
#include "ray.h"

namespace RayTracing{
    class Intersectable{
    public:
        // get the point vec3d where ray intersect this object
        //virtual Vec3d doIntersect(const Ray & ray) const = 0;
        virtual bool isIntersect(const Ray & ray) const = 0;
        virtual bool intersect(real_t & intersectPos, const Ray & ray) const = 0;
    };
};

#endif
