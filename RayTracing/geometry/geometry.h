//
//  Geometry.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "myMath.h"

namespace MyMath{
//Vec3d

	/*inline void TransformBBox(BBox & bboxOut, const Matrix4d & mat, const BBox & bboxIn)
	{
		Vec3d v, v_t;
		bboxOut.Init();
		for (int i = 0; i < 8; i++)
		{
			if (i & 1)
				v(0) = bboxIn.xMax;
			else
				v(0) = bboxIn.xMin;
			if (i & 2)
				v(1) = bboxIn.yMax;
			else
				v(1) = bboxIn.yMin;
			if (i & 4)
				v(2) = bboxIn.zMax;
			else
				v(2) = bboxIn.zMin;
			mat.Transform(v_t, v);
			bboxOut.Union(v_t);
		}
	};*/
	// Beam is a class that define a geometry concept beam
	// Beam contains a source and a direction
	class Beam{
	public:
		// data field
		Vec3d source;
		Vec3d direction;
	public:
		// Constructor
		Beam(){}
		Beam(Vec3d & s, Vec3d& dir) : source(s), direction(dir){}
		Beam(const Beam & b){
			this->source = b.source;
			this->direction = b.direction;
		}
	};
}

#endif
