//
//  triangle.h
//  RayTracing
//
//  Created by Ming Yao on 16/01/10.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "intersectable.h"

namespace MyMath {
    class Triangle : public Intersectable {
    public:
        // data
        Vec3d source, e1, e2;
        Vec3d norm;
    public:
        Triangle() {}
        Triangle(const Vec3d& a, const Vec3d& b, const Vec3d& c) :
            source(a), e1(b - a), e2(c - a), norm(Vec3d::cross(e1,e2)) {
            norm.normalize();
        }

        Vec3d operator () (int i) const {
            if (!i) return source + e1;
            else return source + e2;
        }

        bool isIntersect(const Ray & ray) const override {
            real_t t, u, v;
            return intersectTriangle(ray, t, u, v);
        }

        IntersectType intersect(real_t & pos, const Ray & ray) const override {
            real_t u, v;
            if (intersectTriangle(ray, pos, u, v)) {
                if (Vec3d::dot(ray.getDirection(), norm) < 0)
                    return INSIDE;
                return INTERSECTED;
            }
            return MISSED;
        }

    public:
        // Determine whether a ray intersect with a triangle
        // motivated by http://www.cnblogs.com/graphics/archive/2010/08/09/1795348.html
        bool intersectTriangle(const Ray & ray, real_t& t, real_t& u, real_t& v) const{
            // P
            Vec3d P = Vec3d::cross(ray.getDirection(),e2);
            // determinant
            real_t det = Vec3d::dot(e1,P);
            // keep det > 0, modify T accordingly
            Vec3d T;
            if (det > 0) {
                T = ray.getSource()- source;
            }
            else {
                T = source - ray.getSource();
                det = -det;
            }

            // If determinant is near zero, ray lies in plane of triangle
            if (det < Epsilon)
                return false;

            // Calculate u and make sure u <= 1
            u = Vec3d::dot(T,P);
            if (u < Epsilon || u > det)
                return false;

            // Q
            Vec3d Q = Vec3d::cross(T,e1);

            // Calculate v and make sure u + v <= 1
            v = Vec3d::dot(ray.getDirection(),Q);
            if (v < Epsilon || u + v > det)
                return false;

            // Calculate t and scale parameters and make sure t is at the right range
            t = Vec3d::dot(e2, Q);
            real_t fInvDet = 1.0f / det;
            t *= fInvDet;
            if (t < Epsilon || ray.range < t)
                return false;

            // Calculate  ray intersects triangle
            u *= fInvDet;
            v *= fInvDet;

            return true;
        }
    };
}

#endif