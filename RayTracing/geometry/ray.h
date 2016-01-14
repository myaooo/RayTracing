//
//  ray.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef ray_h
#define ray_h

#include "Vec3d.h"
#include "../util.h"
#define MAXRAYLENGTH 1000000
namespace MyMath{
    class Ray{
    private:
        Vec3d source;
        Vec3d direction;
    public:
        Vec3d inv_direction;
        bool sign[3];
        real_t t1;
    public:
        Ray(const Vec3d & s, const Vec3d & d) : source(s), direction(d){
            direction.normalize();
            inv_direction = Vec3d(1/d.x, 1/d.y, 1/d.z);
            for (size_t i = 0; i < 3; i++) {
                sign[i] = (inv_direction[i] < 0);
            }
            t1 = MAXRAYLENGTH;
        };
        Vec3d getPoint(real_t ratio) const{
            return Vec3d(source + direction * ratio);
        }
        Vec3d & getSource(){
            return source;
        }
        Vec3d & getDirection(){
            return direction;
        }
        const Vec3d & getSource() const {
            return source;
        }
        const Vec3d & getDirection() const{
            return direction;
        }
        void setSource(const Vec3d & s){
            source = s;
        }
        void setDirection(const Vec3d & d){
            direction = d;
            direction.normalize();
            inv_direction = Vec3d(1/d.x, 1/d.y, 1/d.z);
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
