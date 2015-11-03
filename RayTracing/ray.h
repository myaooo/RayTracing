//
//  ray.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef ray_h
#define ray_h

#include "MyMath.h"
#include "point3d.h"

namespace RayTracing{
	typedef MyMath::Vec3d Vec3d;
    class Ray{
    public:
        Point3d source;
        Vec3d direction;
        
    public:
        Ray(Point3d & p, Vec3d d);
        
    };
}


#endif /* ray_h */
