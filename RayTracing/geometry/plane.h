//
//  plane.h
//  RayTracing
//
//  Created by getMing Yao on 15/10/26.
//

#ifndef PLANE_H
#define PLANE_H

#include "intersectable.h"
#include "../util.h"
#include "Vec3d.h"
#define DOT(x,y) (Vec3d::dot((x),(y)))
namespace MyMath{
    //Plane is a class that define a geometry concept box, or bounding box.
    // The box is alines with the world coordinate
    class Plane : public Intersectable{
    public:
        // data
        Vec3d norm;
        real_t d;
    public:
        // Methods
        // Default Constructors
        Plane(){}
        // Default initialization
        Plane(const Vec3d& n, real_t offset, bool isNorm = false) : norm(n), d(offset){
            if (!isNorm) {
                norm.normalize();
            }
        }
        // Construct from a point and norm
        Plane(const Vec3d & p, const Vec3d& n, bool isNorm = false) : norm(n){
            if (!isNorm)
                norm.normalize();
            d = -DOT(p, norm);
        }
        // Construct with ax+by+cz+d=0;
        Plane(real_t a, real_t b, real_t c, real_t _d) {
            norm = Vec3d(a, b, c);
            norm.normalize();
            d = _d;
        }

        real_t distance(const Vec3d & p) const{
            return DOT(norm, p)+d;
        }

        virtual bool isIntersect(const Ray & ray) const override{
            if (DOT(ray.getDirection(),norm) < Epsilon) {
                return false;
            }
            return true;
        }
        virtual IntersectType intersect(real_t & intersectPos, const Ray & ray) const override{
            if (!this->isIntersect(ray)) {
                intersectPos = InfDistance;
                return MISSED;
            }
            Vec3d source = ray.getSource();
            Vec3d direction = ray.getDirection();
            intersectPos = -(this->d+DOT(norm,source))/(DOT(norm,direction));
            return intersectPos < 0 ? INSIDE : INTERSECTED;
        }
    };
#undef DOT
}
#endif //!PLANE_H
