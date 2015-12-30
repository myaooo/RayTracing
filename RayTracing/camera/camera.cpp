//
//  camera.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#include <cmath>
#include <iostream>
#include "camera.h"
#include "../geometry/myMath.h"
#include "../geometry/ray.h"
#include "util.h"

namespace RayTracing{
    // /* ViewPlane */
    // ViewPlane::Viewplane(const Vec3d & upR, const Vec3d & upL, const Vec3d & downR) :
    // upRight(upR), upLeft(upL), downRight(downR){}
    // /*Generate Pixel in viewPlane*/
    // Vec3d ViewPlane::getPix(real_t x, real_t y) const{
    //     Vec3d pix = (1-x-y)*upRight + x*upLeft + y*downRight;
    //     return pix;
    // }

    /*Camera*/
    // constructor
    Camera::Camera(
        const Vec3d& pos,
        const Vec3d& foc,
        real_t h_a,
        real_t v_a,
        real_t dist) :
        position(pos),
        focus(foc),
        hAngle(h_a),
        vAngle(v_a),
        distance(dist){
        init();
    }

    void Camera::init(){
        Matrix4d::Zero(transformMatrix);
        // initalize view center
        Vec3d orient = (foc-pos).normalize();
        viewCenter = position + orient * distance;
        // initialzie horiVec and vertVec
        if ((fabs(orient.y) > Epsilon) || (fabs(orient.x) > Epsilon)){
            horiVec = Vec3d(-orient.y, orient.x, 0);
        }
        else{
            horiVec = Vec3d(-orient.z, 0, orient.x);
        }
        vertVec = Vec3d::cross(horiVec, orient);
        vertVec.normalize();
        horiVec.normalize();
        vertVec *= distance * tan(vAngle/2);
        horiVec *= distance * tan(hAngle/2);
    }
    void Camera::rotate(real_t radius){

    }
    void Camera::orbit(real_t radius){

    }

    void Camera::shift(const Vec3d & direct){

    }

    void Camera::zoom(real_t ratio){

    }
    // generate Ray (x \in [-1,1], y \in [-1,1])
    Ray Camera::genRay(real_t x, real_t y) const{
        if (x < -1 || x > 1) {
            std::cerr<<"x: wrong range!\n";
        }
        if (y < -1 || y > 1) {
            std::cerr<<"y: wrong range!\n";
        }
        Vec3d dest = viewCenter + x * horiVec + y * vertVec;
        Vec3d direct = dest - position;
        return Ray(position, direct);
    }
}
