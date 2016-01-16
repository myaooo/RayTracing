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
        real_t range;
    public:
        Ray(){}
        Ray(const Vec3d & s, const Vec3d & d, real_t dist = MAXRAYLENGTH) :
            source(s), direction(d), range(dist){
            direction.normalize();
            inv_direction = Vec3d(1/d.x, 1/d.y, 1/d.z);
            for (size_t i = 0; i < 3; i++) {
                sign[i] = (inv_direction[i] < 0);
            }
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
        // get Direction
        const Vec3d & getDirection() const{
            return direction;
        }
        // set Source
        void setSource(const Vec3d & s){
            source = s;
        }
        // set Direction
        void setDirection(const Vec3d & d){
            direction = d;
            direction.normalize();
            inv_direction = Vec3d(1/d.x, 1/d.y, 1/d.z);
            for (size_t i = 0; i < 3; i++) {
                sign[i] = (inv_direction[i] < 0);
            }
        }
        // set the range of the ray (max length)
        void setRange(real_t r){
            assert(r>0);
            range = r;
        }

        void offsetSource(real_t delta) {
            source += direction * delta;
            range -= delta;
        }
    };
}


#endif /* ray_h */
