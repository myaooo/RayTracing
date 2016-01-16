//
//  Matrix.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#ifndef MATRIX_H
#define MATRIX_H

#include "Vec3d.h"
#include "Vec4d.h"

namespace MyMath{
	class Matrix4d{
	public:
		// data field
		union{
			double data[16];
			double m[4][4];
			struct{
				double _11, _12, _13, _14,
					_21, _22, _23, _24,
					_31, _32, _33, _34,
					_41, _42, _43, _44;
			};
		};
		static const unsigned Sixteen = 16;
		static const unsigned Four = 4;
	public:
		//Constructors
		Matrix4d(const Matrix4d & m);
		Matrix4d(double p);
		Matrix4d(){}

		// Operator
		inline double& operator () (unsigned x, unsigned y){
			assert(x < Four && y < Four);
			return m[x][y];
		}
		inline const double& operator()(unsigned x, unsigned y)const{
			assert(x < Four && y < Four);
			return m[x][y];
		}
		inline Matrix4d operator * (const Matrix4d& M) const;
        //inline Vec4d operator * (const Vec4d& M) const;
		inline Matrix4d operator - (const Matrix4d& M) const;
		inline Matrix4d operator + (const Matrix4d& M) const;
		inline void operator +=(const Matrix4d& M);
		inline void operator -=(const Matrix4d& M);

		// Static Method
		//Create random Matrix
        static inline void zero(Matrix4d& m);
        static inline void eye(Matrix4d& m);
		static inline void random(Matrix4d& m);
		static void lookAt(Matrix4d& result, const Vec3d & pos, const Vec3d & center, const Vec3d & up);
		static inline void rotateXM(Matrix4d& result, double rad);
		static inline void rotateYM(Matrix4d& result, double rad);
		static inline void rotateZM(Matrix4d& result, double rad);
		static void rotateM(Matrix4d& result, const Vec3d & axis, double rad);
		static void rotateNormM(Matrix4d& result, const Vec3d & naxis, double rad);
		static void rotateM(Matrix4d& result, double xrad, double yrad, double zrad);
		//Create scale transform Matrix
		static inline void scaleM(Matrix4d& result, double sx, double sy, double sz);
		//Create translate transform Matrix
		static inline void translateM(Matrix4d& result, double tx, double ty, double tz);

		// Matrix calculation methods
		// For a better speed performance, here we use a value transfer function
		// instead of return a duplicated variable
		// Static Methods
		static inline void multiply(Matrix4d& mOut, const Matrix4d& M1, const Matrix4d& M2);
        static inline void multiply(Vec4d& vOut, const Matrix4d& M1, const Vec4d& V2);

		double inverse3D(Matrix4d& mOut_d) const;
		double inverseFPU(Matrix4d& mOut_d) const;
		inline double inverse(Matrix4d& mOut_d) const;

		//Other Method
		inline void transform(Vec3d & result, const Vec3d& invec) const;
        inline void transform(Vec4d& result, const Vec4d& invec) const;
		inline void transformNormal(Vec3d & result, const Vec3d& invec) const;
		inline void transposetransformNormal(Vec3d & result, const Vec3d & invec) const;
		inline void transposetransform(Vec3d & result, const Vec3d & invec) const;
        inline void transposetransform(Vec4d& result, const Vec4d& invec) const;

	};
    // Static Method
	inline void Matrix4d::random(Matrix4d& m){
		for (int i = 0; i < Sixteen; ++i)
			m.data[i] = rand() / (double)RAND_MAX;
	}

    inline void Matrix4d::zero(Matrix4d& m){
        for (int i = 0; i < Sixteen; ++i)
            m.data[i] = 0;
    }
    inline void Matrix4d::eye(Matrix4d& m){
        zero(m);
        for (int i = 0; i < Four; ++i)
            m(i, i) = 1;
    }

}

#endif
