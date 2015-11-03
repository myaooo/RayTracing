//
//  point3d.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef point3d_h
#define point3d_h

#include "Vecnd.h"
#include "color.h"

namespace RayTracing{
    typedef MyMath::Vec3d Point3d;
    
    class Point_with_color : public Point3d{
    public:
        Color color;
        void SetColor(char * c, unsigned type = 3){
            color.reserve(type);
            for(int i = 0; i < type; ++i){
                color[i] = c[i];
            }
        }
    };
}

#endif /* point3d_h */
