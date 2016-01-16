//
//  matrix.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#include "Matrix.h"
#include <random>
#include <cmath>

namespace MyMath{
	///////////////////////
	// Constructors
	Matrix4d::Matrix4d(const Matrix4d & mat){
		for (int i = 0; i < Sixteen; ++i)
				this->data[i] = mat.data[i];
	}
	Matrix4d::Matrix4d(double p){
		for (int i = 0; i < Sixteen; ++i)
			data[i] = p;
	}

	///////////////////////
	// Operators *, +, -, *=, +=, -=
	// Some un-static methods
	inline Matrix4d Matrix4d::operator * (const Matrix4d& M) const{
		Matrix4d mat;
		multiply(mat, *this, M);
		return mat;
	}
//	inline Vec4d Matrix4d::operator * (const Vec4d& V) const{
//		Vec4d vec;
//		multiply(vec, *this, V);
//		return vec;
//	}
	inline Matrix4d Matrix4d::operator - (const Matrix4d& M) const{
		Matrix4d mat;
		for (int i = 0; i < Sixteen; ++i)
			mat.data[i] = this->data[i] - M.data[i];
		return mat;
	}
	inline Matrix4d Matrix4d::operator + (const Matrix4d& M) const{
		Matrix4d mat;
		for (int i = 0; i < Sixteen; ++i)
			mat.data[i] = this->data[i] + M.data[i];
		return mat;
	}
	inline void Matrix4d::operator +=(const Matrix4d& M){
		for (int i = 0; i < Sixteen; ++i)
			this->data[i] += M.data[i];
	}
	inline void Matrix4d::operator -=(const Matrix4d& M){
		for (int i = 0; i < Sixteen; ++i)
			this->data[i] -= M.data[i];
	}

	///////////////////////
	// Methods
	// 2 multiply Methods
	inline void Matrix4d::multiply(Vec4d& vOut, const Matrix4d& M, const Vec4d& V){
		for (int i = 0; i < Four; ++i)
			vOut(i) = M(i,0) * V(0) + M(i,1) * V(1) + M(i,2) * V(2) + M(i,3) * V(3);
	}

	inline void Matrix4d::multiply(Matrix4d& mOut, const Matrix4d& M1, const Matrix4d& M2){
		for (unsigned i = 0; i < Four; ++i)
			for (unsigned j = 0; j < Four;++j)
				mOut.m[i][j] = M1(i, 0) * M2(0, j) + M1(i, 1) * M2(1, j)
				+ M1(i, 2) * M2(2, j) + M1(i, 3) * M2(3, j);
	}

	// Coordinate transform v' = vT*MT
	inline void Matrix4d::transform(Vec3d & result, const Vec3d & vin) const
	{
		for (int i = 0; i < Four-1; ++i){
			result(i) = m[i][0] * vin(0) + m[i][1] * vin(1) + m[i][2] * vin(2) + m[3][0];
		}
	}
	inline void Matrix4d::transform(Vec4d& result, const Vec4d& vin) const
	{
		multiply(result, *this, vin);
	}
	inline void Matrix4d::transformNormal(Vec3d & rs, const Vec3d& vin) const{

	}
	inline void Matrix4d::transposetransformNormal(Vec3d & rs, const Vec3d & vin) const{

	}
	inline void Matrix4d::transposetransform(Vec3d & rs, const Vec3d & vin) const{

	}
	inline void Matrix4d::transposetransform(Vec4d& rs_d, const Vec4d& vin) const{

	}

	void Matrix4d::lookAt(Matrix4d& result, const Vec3d & pos, const Vec3d & center, const Vec3d & up){

	}
	inline void Matrix4d::rotateXM(Matrix4d& result, double angle)
	{
		double c = cos(angle);
		double s = sin(angle);
		eye(result);
		result(1,1) = c;
		result(2, 1) = s;
		result(1, 2) = -s;
		result(2, 2) = c;
	}
	inline void Matrix4d::rotateYM(Matrix4d& result, double angle)
	{
		double c = cos(angle);
		double s = sin(angle);
		eye(result);
		result(0, 0) = c;
		result(2, 0) = s;
		result(0, 2) = -s;
		result(2, 2) = c;
	}
	inline void Matrix4d::rotateZM(Matrix4d& result, double angle)
	{
		double c = cos(angle);
		double s = sin(angle);
		eye(result);
		result(0, 0) = c;
		result(1, 0) = s;
		result(0, 1) = -s;
		result(1, 1) = c;
	}
	void Matrix4d::rotateM(Matrix4d& result, const Vec3d & axis, double rad){
		Vec3d nAxis=axis;
		// First Normalize the vector axis
        nAxis.normalize();
		rotateNormM(result, nAxis, rad);
	}
	void Matrix4d::rotateNormM(Matrix4d& result, const Vec3d & naxis, double rad){
		// Calculate paras
		double c = cos(rad);
		double s = sin(rad);
		double t = 1 - c;
		double kx = naxis(0);
		double ky = naxis(1);
		double kz = naxis(2);

		// Assign values
		result(0, 0) = c + t*kx*kx;
		result(1, 0) = kz*s + t*kx*ky;
		result(2, 0) = -ky*s + t*kx*kz;
		result(3, 0) = 0;

		result(0, 1) = -kz*s + t*kx*ky;
		result(1, 1) = c + t*ky*ky;
		result(2, 1) = kx*s + t*ky*kz;
		result(3, 1) = 0;

		result(0, 2) = ky*s + t*kx*kz;
		result(1, 2) = -kx*s + t*ky*kz;
		result(2, 2) = c + t*kz*kz;
		result(3, 2) = 0;

		result(0, 3) = 0;
		result(1, 3) = 0;
		result(2, 3) = 0;
		result(3, 3) = 1;
	}
	void Matrix4d::rotateM(Matrix4d& result, double xrad, double yrad, double zrad){
		Matrix4d mat1,mat2;
		rotateXM(result, xrad);
		rotateYM(mat1, yrad);
		multiply(mat2, result,mat1);
		rotateZM(mat1, zrad);
		multiply(result, mat1, mat2);
	}
	inline void Matrix4d::scaleM(Matrix4d& result, double sx, double sy, double sz){
		Zero(result);
		result(0, 0) = sx;
		result(1, 1) = sy;
		result(2, 2) = sz;
	}
	inline void Matrix4d::translateM(Matrix4d& result, double tx, double ty, double tz){
		eye(result);
		result(0, 3) = tx;
		result(1, 3) = ty;
		result(2, 3) = tz;
	}

    

}//end MyMath
