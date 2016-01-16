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
#include "../util.h"
namespace MyMath{
    //BBox is a class that define a geometry concept box, or bounding box.
    // The box is alines with the world coordinate
    class BBox : public Intersectable{
    private:
        // hot tmin, tmax
        mutable real_t _hotTMin, _hotTMax;
    public:
		// data
		Vec3d minVec;
		Vec3d maxVec;
	public:
		// Methods
		// Default Constructors
        BBox(){
			Init();
		}
        // Constructor
        BBox(const Vec3d & _min, const Vec3d & _max) : minVec(_min), maxVec(_max){}
		// Default initialization
		inline void Init(){
            minVec = Vec3d::maxVec;
            maxVec = Vec3d::minVec;
		}
		// Find the dimension that have the max length
		inline int getMaxDimension(){
			real_t xsize = maxVec.x - minVec.x;
			real_t ysize = maxVec.y - minVec.y;
			real_t zsize = maxVec.z - minVec.z;
			if (xsize > ysize){
				if (xsize > zsize)
					return 0;
				else
					return 2;
			}
			else{
				if (ysize > zsize)
					return 1;
				else
					return 2;
			}
		}
        // union another BBox box with this BBox
        inline void Union(const BBox & box){
            for (size_t i = 0; i < 3; i++) {
                minVec[i] = getMin(box.minVec[i], minVec[i]);
                maxVec[i] = getMax(box.maxVec[i], maxVec[i]);
            }
        }
        // union another point
        inline void Union(const Vec3d &v){
            for (size_t i = 0; i < 3; i++) {
                minVec[i] = getMin(v[i], minVec[i]);
                maxVec[i] = getMax(v[i], maxVec[i]);
            }
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
            if (isIntersect(ray)) {
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


	};
}
#endif //!BBOX_H
