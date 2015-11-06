////  Material.h//  RayTracing////  Created by Ming Yao on 15/10/26.//  Copyright © 2015年 Ming Yao. All rights reserved.//#ifndef MATERIAL_H#define MATERIAL_H#include "color.h"namespace RayTracing{	class Material{		Color color;		//bool Enabled;
		bool Reflect;
		bool Refract;
		bool Lambert;
		bool Environment;

	};}#endif // !MATERIAL_H