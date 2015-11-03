//
//  camera.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "Vec3d.h"
#include "opencv2/opencv.hpp"

namespace  RayTracing {
    
    class Viewplane{
    public:
        Vec3d UpRightPoint;
        Vec3d vec_a;
        Vec3d vec_d;
        
        Viewplane(Vec3d & p, Vec3d & a, Vec3d & b);
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
        double f;
    };
}

#endif /* camera_h */
