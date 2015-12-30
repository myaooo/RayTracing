//
//  camera.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef camera_h
#define camera_h

#include "../geometry/myMath.h"
#include "../scene/scene.h"
#include "util.h"

namespace  RayTracing {
    // Class ViewPlane
    // class Viewplane{
    // public:
    //     Vec3d upRight;
    //     Vec3d upLeft;
    //     Vec3d downRight;
    //
    //     Viewplane(const Vec3d & upR, const Vec3d & upL, const Vec3d & downR);
    //     /*Generate Pixel in viewPlane*/
    //     Vec3d getPix(real_t x, real_t y) const;
    // };

    #define HORIZONTAL_RAD = (60*PI/180)
    #define VERTICAL_RAD = (60*PI/180)

    class Camera{
    private:
        // Position of the camera
        Vec3d position;
        // focus point of the camera
        Vec3d focus;
        // view center
        Vec3d viewCenter;
        // horizontal direction
        Vec3d horiVec;
        // vertical direction
        Vec3d vertVec;
        // horizontal visual angle
        real_t hAngle;
        // vertical visual angle
        real_t vAngle;
        // The distance between the camera and the view plane
        real_t distance;
        // Transform Matrix
        Matrix4d transformMatrix;

    public:
        Camera(){}
        Camera(const Vec3d& pos, const Vec3d& foc,
            real_t h_a = HORIZONTAL_RAD, real_t v_a = VERTICAL_RAD, real_t dist = 10);
        void init();
        void setPosition(const Vec3d & pos){
            position = pos;
        }
        void setFocus(const Vec3d & foc){
            focus = foc;
        }
        void rotate(real_t degree);
        void orbit(real_t degree);
        void zoom(real_t ratio);
        void shift(const Vec3d & direct);
        // generate Ray
        Ray genRay(real_t x, real_t y) const;

    };
}

#endif /* camera_h */
