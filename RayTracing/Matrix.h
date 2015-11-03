//
//  Num.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//
#ifndef MATRIX_H
#define MATRIX_H

#include "Vecnd.h"

namespace MyMath{
	typedef Vecnd<3> Vec3d;
	typedef Vecnd<4> Vec4d;
	class Matrix4d{
	public:
		// data field
		union{
			double value[16];
			double data[4][4];
			struct{
				double _11, _12, _13, _14,
					_21, _22, _23, _24,
					_31, _32, _33, _34,
					_41, _42, _43, _44;
			};
		};

	public:
		//Constructors
		Matrix4d(const Matrix4d & m);
		Matrix4d(double p);

		//Operators

		//Other Method

		inline void Transform(Vec3d & rs_d, const Vec3d& vIn) const;
		inline void Transform(Vec4d& rs_d, const Vec4d& vIn) const;
		inline void TransformNormal(Vec3d & rs, const Vec3d& vIn) const;
		inline void TransposeTransformNormal(Vec3d & rs, const Vec3d & vIn) const;
		inline void TransposeTransform(Vec3d & rs, const Vec3d & vIn) const;
		inline void TransposeTransform(Vec4d& rs_d, const Vec4d& vIn) const;

		// Static Method
		static inline void CreateIdentityMatrix(Matrix4d& mOut);
		static inline void CreateRandomMatrix(Matrix4d& mOut);
		static void LookAt(Matrix4d& rs, const Vec3d & pos, const Vec3d & center, const Vec3d & up);
		static inline void RotationX(Matrix4d& rs, float angle);
		static inline void RotationY(Matrix4d& rs, float angle);
		static inline void RotationZ(Matrix4d& rs, float angle);
		static void Rotation(Matrix4d& rs, const Vec3d & axis, float angle);
		static void Rotation(Matrix4d& rs, float yaw, float pitch, float roll);
		static inline void Scale(Matrix4d& rs, float sx, float sy, float sz);
		static inline void Translation(Matrix4d& rs, float tx, float ty, float tz);

		static inline void MultiplyFPU(Matrix4d&mOut, const Matrix4d& M1, const Matrix4d& M2);
		static inline void Multiply(Matrix4d&mOut, const Matrix4d& M1, const Matrix4d& M2);
		float Inverse3D(Matrix4d& mOut_d) const;
		float InverseFPU(Matrix4d&mOut_d) const;
		inline float Inverse(Matrix4d&mOut_d) const;
	};

}

#endif