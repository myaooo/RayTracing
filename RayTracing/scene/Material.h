//
//  material.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "../ray/color.h"
namespace RayTracing{
    class Material{
        Color color;
		bool Reflect;
		bool Refract;
		bool Lambert;
		bool Environment;

    };
}
#endif // !MATERIAL_H
