//
//  light.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef light_h
#define light_h

#include "../color.h"
#include "../geometry.h"
#include "../util.h"
#include "SimpleObject.h"

namespace RayTracing{
    // Light
    class Light{
    // http://en.wikipedia.org/wiki/Phong_reflection_model
    public:
        // data field
        // diffuse color and specular color of the light
        Color diffuse, specular;
        // the intensities of diffuse and specular
        real_t DIntensity, SIntensity;
        // method
        // creator
        Light(char *c, real_t strength);
    };
    // Point Light
    class PointLight : public Light{
    public:
        // data field
        Vec3d source;
        // method
        // constructor
        PointLight(Vec3d & s, char * c, real_t strength);

    };

    // Parallel Light
    class ParaLight : public PointLight{
    public:
        // data field
        Vec3d orient;
        // method
        // Constructor
		ParaLight(Vec3d & orient);
        ParaLight(Vec3d & orient, PointLight& pl);
    };

    // Light Obj
    class ObjLight : public Light{
        CSimpleObject obj;
    };
}

#endif /* light_h */
