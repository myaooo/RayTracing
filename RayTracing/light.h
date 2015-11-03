//
//  light.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef light_h
#define light_h

#include "color.h"
#include "point3d.h"
#include "Vec3d.h"
#include "SimpleObject.h"

namespace RayTracing{
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
        Point3d source;
        // method
        // constructor
        PointLight(Point3d & s, char * c, double strength);
        
    };
    
    // Parallel Light
    class ParaLight : public PointLight{
    public:
        // data field
        Vec3d orient;
        // method
        // Constructor
        ParaLight(Vec3d & orient)
        ParaLight(Vec3d & orient, PointLight& pl);
    };
    
    // Light Obj
    class ObjLight : public Light{
        CSimpleObject obj;
    };
}

#endif /* light_h */
