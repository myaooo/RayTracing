//
//  camera.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef camera_h
#define camera_h

#include "../geometry/Vec3d.h"
#include "../scene/scene.h"

namespace  RayTracing {
    //typedef MyMath::Vec3d Vec3d;
    class Viewplane{
    public:
        Vec3d upRight;
        Vec3d upLeft;
        Vec3d downRight;

        Viewplane(Vec3d & upR, Vec3d & upL, Vec3d & downR);
        /*Generate Pixel in viewPlane*/
        Vec3d getPix(real_t x, real_t y) const;
    };

    class Camera{
    private:
        // Position of the camera
        Vec3d position;
        // orientation of the camera
        Vec3d orient;
        // horizontal visual angle
        double h_angle;
        // vertical visual angle
        double v_angle;
        // The distance between the camera and the view plane
        double distance;
    public:
        Camera(){}
        Camera(const Vec3d& pos, const Vec3d& ori, double h_a, double v_a, double dist) :
        position(pos), orient(ori), h_angle(h_a), v_angle(v_a), distance(dist){}
        void setPosition(const Vec3d & pos){
            position = pos;
        }
        void setOrientation(const Vec3d & ori){
            orient = ori;
        }
        // generate Ray
        Ray genRay(real_t x, real_t y) const;



    };
}

#endif /* camera_h */
