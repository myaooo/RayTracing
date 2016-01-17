//
//  bbox.h
//  RayTracing
//
//  Created by getMing Yao on 15/10/26.
//

#ifndef BBOX_H
#define BBOX_H

#include "intersectable.h"
#include "Vec3d.h"
#include "triangle.h"
#include "../util.h"
#include <ostream>

namespace MyMath{
    // SuperPlane is a class that define a geometry super plane, or axis aligned plane
    class SuperPlane {
    public:
        enum Axis { ERROR = -1, AXIS_X = 0, AXIS_Y, AXIS_Z };
        Axis axis;
        real_t position;

        //SuperPlane() : axis(ERROR) {}
        SuperPlane(int a = -1, real_t pos = 0) : axis(static_cast<Axis>(a)), position(pos){}
        real_t getDistance(const Ray & ray) const{
            real_t delta = ray.getSource()[static_cast<int>(axis)] - position;
            return delta * ray.inv_direction[static_cast<int>(axis)];
        }
    };

    // BBox is a class that define a geometry concept box, or bounding box.
    // The box is aligned with the world coordinate
    class BBox : public Intersectable{
    public:
        // hot tmin, tmax
        mutable real_t _hotTMin, _hotTMax;
    
        // data
        Vec3d minVec;
        Vec3d maxVec;
    public:
        // Methods
        // Default Constructors
        BBox() {
            reset();
        }
        // Constructor
        BBox(const Vec3d & _min, const Vec3d & _max) : minVec(_min), maxVec(_max) {}
        // Default initialization
        inline void reset() {
            minVec = Vec3d::maxVec;
            maxVec = Vec3d::minVec;
        }
        // Find the dimension that have the max length
        inline int getMaxDimension() {
            real_t xsize = maxVec.x - minVec.x;
            real_t ysize = maxVec.y - minVec.y;
            real_t zsize = maxVec.z - minVec.z;
            if (xsize > ysize) {
                if (xsize > zsize)
                    return 0;
                else
                    return 2;
            }
            else {
                if (ysize > zsize)
                    return 1;
                else
                    return 2;
            }
        }
        bool hasPoint(const Vec3d & p) {
            return (minVec < p && p < maxVec);
        }
        // union another BBox box with this BBox
        inline void unite(const BBox & box){
            for (size_t i = 0; i < 3; i++) {
                minVec[i] = getMin(box.minVec[i], minVec[i]);
                maxVec[i] = getMax(box.maxVec[i], maxVec[i]);
            }
        }
        // union another point
        inline void unite(const Vec3d &v){
            for (size_t i = 0; i < 3; i++) {
                minVec[i] = getMin(v[i], minVec[i]);
                maxVec[i] = getMax(v[i], maxVec[i]);
            }
        }

        bool split(BBox & boxA, BBox & boxB, const SuperPlane& pl) const {
            boxA = *this;
            boxB = *this;
            if (!isBetween(pl.position, minVec[pl.axis] + Epsilon / 2,
                maxVec[pl.axis] - Epsilon / 2)) return false;
                // in case there is a too small box or a same box
            boxA.maxVec[pl.axis] = pl.position;
            boxB.minVec[pl.axis] = pl.position;
            return true;
        }

        real_t surfaceArea() {
            Vec3d temp = maxVec - minVec;
            return temp[0] * (temp[1] + temp[2]) + temp[1] * temp[2];
        }

        // test intersect function
        // returns true if the ray intersect with the box
        // Woo algorithm
        virtual bool isIntersect(const Ray & r) const override{
            real_t tmin, tmax, tymin, tymax, tzmin, tzmax;
            if (r.getDirection().x >= 0) { // x > 0, the near face is the xmin
                tmin = (minVec.x - r.getSource().x) * r.inv_direction.x;
                tmax = (maxVec.x - r.getSource().x) * r.inv_direction.x;
            }
            else { // x < 0, the near face is the xmax
                tmin = (maxVec.x - r.getSource().x) * r.inv_direction.x;
                tmax = (minVec.x - r.getSource().x) * r.inv_direction.x;
            }
            if (r.getDirection().y >= 0) { // y > 0, the near face is the ymin
                tymin = (minVec.y - r.getSource().y) * r.inv_direction.y;
                tymax = (maxVec.y - r.getSource().y) * r.inv_direction.y;
            }
            else { // y < 0, the near face is the ymax
                tymin = (maxVec.y - r.getSource().y) * r.inv_direction.y;
                tymax = (minVec.y - r.getSource().y) * r.inv_direction.y;
            }
            if ( (tymax < tmin) || (tmax < tymin) ) // not intersecting the box
                return false;
            if (tmin < tymin)
                tmin = tymin;
            if (tymax < tmax)
                tmax = tymax;
            if (r.getDirection().z >= 0) {
                tzmin = (minVec.z - r.getSource().z) * r.inv_direction.z;
                tzmax = (maxVec.z - r.getSource().z) * r.inv_direction.z;
            }
            else {
                tzmin = (maxVec.z - r.getSource().z) * r.inv_direction.z;
                tzmax = (minVec.z - r.getSource().z) * r.inv_direction.z;
            }
            if ( (tmin > tzmax) || (tzmin > tmax) )
                return false;
            if (tzmin > tmin)
                tmin = tzmin;
            if (tzmax < tmax)
                tmax = tzmax;
            _hotTMin = tmin;
            _hotTMax = tmax;
            return ( (tmin < r.range) && (tmax > 0) );
        }

        virtual IntersectType intersect(real_t & intersectPos, const Ray & ray) const override{
            if (!isIntersect(ray)) {
                intersectPos = InfDistance;
                return MISSED;
            }
            else{
                if (_hotTMin < 0) {
                    intersectPos = _hotTMax;
                    return INSIDE;
                }
                else{
                    intersectPos = _hotTMin;
                    return INTERSECTED;
                }
            }
        }

        friend std::ostream & operator << (std::ostream  &o, const BBox & b) {
            o << b.minVec[0] << " " << b.minVec[1] << " " << b.minVec[2] << " ";
            o << b.maxVec[0] << " " << b.maxVec[1] << " " << b.maxVec[2];
            return o;
        }

    };
}
#endif //!BBOX_H
