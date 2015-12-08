////  Geometry.h//  RayTracing////  Created by Ming Yao on 15/10/26.//#ifndef GEOMETRY_H#define GEOMETRY_H#include "myMath.h"#include "Num.h"namespace MyMath{	typedef Vecnd<3> Vec3d;	// BBox is a class that define a geometry concept box, or bounding box.	class BBox{	public:
		// data
		union
		{
			struct
			{
				double xMin, yMin, zMin, xMax, yMax, zMax;
			};
			struct
			{
				Vec3d minvec, maxvec;
			};
		};	public:		// Methods		// Default Constructors		BBox(){			Init();		}		// Default initialization		inline void Init(){			xMin = yMin = zMin = DBL_MAX;
			xMax = yMax = zMax = -DBL_MAX;		}		// Find the dimension that have the max length		inline int MaxDimension()
		{
			double xsize = xMax - xMin;
			double ysize = yMax - yMin;
			double zsize = zMax - zMin;
			if (xsize > ysize)
			{
				if (xsize > zsize)
					return 0;
				else
					return 2;
			}
			else
			{
				if (ysize > zsize)
					return 1;
				else
					return 2;
			}
		}
		// union another BBox box with this BBox
		inline void Union(const BBox & box)
		{
			xMin = Min(box.xMin, xMin);
			yMin = Min(box.yMin, yMin);
			zMin = Min(box.zMin, zMin);

			xMax = Max(box.xMax, xMax);
			yMax = Max(box.yMax, yMax);
			zMax = Max(box.zMax, zMax);
		}
		// union another point3d or vec3d
		inline void Union(const Vec3d &v)
		{
			xMin = Min(v(0), xMin);
			yMin = Min(v(1), yMin);
			zMin = Min(v(2), zMin);

			xMax = Max(v(0), xMax);
			yMax = Max(v(1), yMax);
			zMax = Max(v(2), zMax);
		}
	};

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
		}	};*/	// Beam is a class that define a geometry concept beam	// Beam contains a source and a direction	class Beam{	public:		// data field		Vec3d source;		Vec3d direction;	public:		// Constructor		Beam(){}		Beam(Vec3d & s, Vec3d& dir) : source(s), direction(dir){}		Beam(const Beam & b){			this->source = b.source;			this->direction = b.direction;		}	};}#endif