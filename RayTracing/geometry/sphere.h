//
//  sphere.h
//  RayTracing
//
//  Created by getMing Yao on 15/10/26.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "intersectable.h"
#include "../util.h"
#include "Vec3d.h"

namespace MyMath{
    class Sphere : public Intersectable{
    public:
        Vec3d center;
        real_t radius;
    public:
        Sphere(){}
        Sphere(const Vec3d & c, real_t r) : center(c), radius(r){
            assert(radius > 0);
        }

        virtual bool isIntersect(const Ray & ray) const override{
            real_t intersectPos;
            IntersectType iType = intersect(intersectPos, ray);
            return iType != MISSED;
        }
        virtual IntersectType intersect(real_t & intersectPos, const Ray & ray) const override{
            // calculate params
            Vec3d l = center - ray.getSource();
            real_t lSqr = l.L2Norm_Sqr();
            real_t rSqr = getSqr(radius);
            real_t tp = Vec3d::dot( ray.getDirection(), l );
            // check whether is inside
            if (lSqr < rSqr){ // when l^2 == r^2, regard as outside
                intersectPos = tp + sqrt(rSqr - (lSqr - getSqr(tp)));
                return intersectPos < ray.range ? INSIDE : MISSED; // inside
            }
            // check whether the ray has the possible intersected orient
            if (tp > 0) {
                real_t dSqr = lSqr - getSqr(tp);
                if (dSqr < rSqr) {
                    intersectPos = tp - sqrt(rSqr - dSqr);
                    return intersectPos < ray.range ? INTERSECTED : MISSED;
                }
            }
            intersectPos = InfDistance;
            return MISSED;
        }
    };

}

#endif // !SPHERE_H
