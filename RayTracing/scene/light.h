//
//  light.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef light_h
#define light_h

#include "../ray/color.h"
#include "../geometry/Vec3d.h"
#include "SimpleObject.h"

namespace RayTracing{
    //typedef MyMath::Vec3d Vec3d;
    // Light
    class Light{
    public:
        // data field
        Color color;
        double strength;
        // method
        // creator
        Light(char *c, double strength);
    };
    // Point Light
    class PointLight : public Light{
    public:
        // data field
        Vec3d source;
        // method
        // constructor
        PointLight(Vec3d & s, char * c, double strength);
        
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
