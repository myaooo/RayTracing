//
//  plane.h
//  RayTracing
//
//  Created by getMing Yao on 15/10/26.
//

#ifndef PLANE_H
#define PLANE_H

#include "intersectable.h"
#include "Vec3d.h"
#define dot(x,y) (Vec3d::dot((x),(y)))
namespace MyMath{
    //Plane is a class that define a geometry concept box, or bounding box.
    // The box is alines with the world coordinate
    class Plane : public Intersectable{
    public:
        // data
        Vec3d normVec;
        real_t d;
    public:
        // Methods
        // Default Constructors
        Plane(){}
        // Default initialization
        Plane(const Vec3d& n, real_t offset, bool isNorm = false) : normVec(n), d(offset){
            if (!isNorm) {
                normVec.normalize();
            }
        }
        // Construct from a point and norm
        Plane(const Vec3d & p, const Vec3d& n, bool isNorm = false) : normVec(n){
            if (!isNorm)
                normVec.normalize();
            d = -dot(p, normVec);
        }
        // Construct with ax+by+cz+d=0;
        Plane(real_t a, real_t b, real_t c, real_t _d) {
            normVec = Vec3d(a, b, c);
            normVec.normalize();
            d = _d;
        }

        real_t distance(const Vec3d & p) const{
            return dot(normVec, p)+d;
        }

        // virtual Vec3d doIntersect(const Ray & ray) const{
        //     Vec3d source = ray.getSource();
        //     Vec3d direction = ray.getDirection();
        //     real_t t = -(d+dot(normVec,source))/(dot(normVec,direction));
        //     Vec3d intersect_point = source + t*direction;
        //     return intersect_point;
        // }

        virtual bool isIntersect(const Ray & ray) const{
            return true;
        }
        virtual bool intersect(real_t & intersectPos, const Ray & ray){
            Vec3d source = ray.getSource();
            Vec3d direction = ray.getDirection();
            intersectPos = -(d+dot(normVec,source))/(dot(normVec,direction));
            return true;
        }
    };
#undef dot
}
#endif //!PLANE_H
