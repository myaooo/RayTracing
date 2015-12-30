//
//  ray.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef ray_h
#define ray_h

#include "Vec3d.h"
#include "util.h"

namespace RayTracing{
    class Ray{
    private:
        Vec3d source;
        Vec3d direction;
    public:
        Vec3d direction;
        bool sign[3];
    public:
        Ray(const Vec3d & s, const Vec3d & d) : source(s), direction(d){
            direction.normalize();
            inv_direction = Vec3d(1/d.x(), 1/d.y(), 1/d.z());
            for (size_t i = 0; i < 3; i++) {
                sign[i] = (inv_direction[i] < 0);
            }
        };
        Vec3d getPoint(real_t ratio) const{
            return Vec3d(source + ratio * direction);
        }
        Vec3d & getSource(){
            return source;
        }
        Vec3d & getDirection(){
            return direction;
        }
        Vec3d getSource() const {
            return source;
        }
        Vec3d getDirection() const{
            return direction;
        }
        void setSource(const Vec3d & s){
            source = s;
        }
        void setDirection(const Vec3d & d){
            direction = d;
            direction.normalize();
            inv_direction = Vec3d(1/d.x(), 1/d.y(), 1/d.z());
            for (size_t i = 0; i < 3; i++) {
                sign[i] = (inv_direction[i] < 0);
            }
        }
        void normalizeDirection(){
            direction.normalize();
        }
    };
}


#endif /* ray_h */
