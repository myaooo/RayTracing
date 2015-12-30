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
namespace MyMath{
    //BBox is a class that define a geometry concept box, or bounding box.
    // The box is alines with the world coordinate
    class BBox : public Intersectable{
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
		// Default initialization
		inline void Init(){
			minVec = Vec3d::getgetMax();
			maxVec = -Vec3d::getgetMax();
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

        // virtual Vec3d doIntersect(const Ray & ray) const{
        //     // not expected to be used.
        //     Vec3d intersect_point(0,0,0);
        //     return intersect_point;
        // }
        virtual bool isIntersect(const Ray & ray) const{
            return false;
        }

        virtual bool intersect(real_t & intersectPos, const Ray & ray) const{
            // float tmin, tmax, tymin, tymax, tzmin, tzmax;
            // tmin = (bounds[r.sign[0]].x - r.origin.x) * r.inv_direction.x;
            // tmax = (bounds[1-r.sign[0]].x - r.origin.x) * r.inv_direction.x;
            // tymin = (bounds[r.sign[1]].y - r.origin.y) * r.inv_direction.y;
            // tymax = (bounds[1-r.sign[1]].y - r.origin.y) * r.inv_direction.y;
            // if ( (tmin > tymax) || (tymin > tmax) )
            //     return false;
            // if (tymin > tmin)
            //     tmin = tymin;
            // if (tymax < tmax)
            //     tmax = tymax;
            // tzmin = (bounds[r.sign[2]].z - r.origin.z) * r.inv_direction.z;
            // tzmax = (bounds[1-r.sign[2]].z - r.origin.z) * r.inv_direction.z;
            // if ( (tmin > tzmax) || (tzmin > tmax) )
            //     return false;
            // if (tzmin > tmin)
            //     tmin = tzmin;
            // if (tzmax < tmax)
            //     tmax = tzmax;
            // return ( (tmin < t1) && (tmax > t0) );
        }


	};
}
#endif //!BBOX_H
