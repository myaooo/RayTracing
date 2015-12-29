//
//  raytracer.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef raytracer_h
#define raytracer_h

#include "camera/camera.h"

namespace RayTracing{
    class RayTracer{
    public:
        Camera cam;
        Scene * scenePtr;
    public:
        RayTracer(){}
        RayTracer(Camera c, const Scene * s) : cam(c), scenePtr(s){}
        void RayTrace();
    };
}

#endif /* raytracer_h */
