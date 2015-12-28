//
//  color.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/29.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef color_h
#define color_h

//#include "Vec3f.h"
//color mode
#define RGB 3
#define RGBA 4
class Color{
private:
    union{
        struct{
            float r, g, b, a;
        };
    };
};

#endif /* color_h */
