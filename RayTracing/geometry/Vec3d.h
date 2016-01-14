//
//  vec3d.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#ifndef VEC3D_H
#define VEC3D_H
#include "../util.h"
#include <cassert>
#include <cstring>
#include <cmath>

#define ABS(a) ((a) > 0 ? (a) : -(a))
#define isEqual(a, b) (ABS(a-b) < Epsilon)

namespace MyMath{
    class Vec3d{
    public:
        //Constructors
        Vec3d();
        Vec3d(real_t x,real_t y, real_t z);
        Vec3d(const Vec3d& v);
        //Deconstructor
        virtual ~Vec3d();
    public:
        //Operators

        //Operator []
        inline real_t& operator [](int index)
        {
            assert(index>=0&&index<3);
            return _p[index];
        }
        inline const real_t& operator [](int index) const
        {
            assert(index>=0&&index<3);
            return _p[index];
        }

        //Operator ()
        inline real_t& operator ()(int index)
        {
            assert(index>=0&&index<3);
            return _p[index];
        }
        inline const real_t& operator ()(int index) const
        {
            assert(index>=0&&index<3);
            return _p[index];
        }

        //Operator =
        Vec3d& operator = (const Vec3d& v);

        //Operators +=,-=, *=, /=
        void operator +=(const Vec3d& v);
        void operator +=(real_t f);
        void operator -=(const Vec3d& v);
        void operator -=(real_t f);
        void operator *=(const Vec3d& v);
        void operator *=(real_t f);
        void operator /=(const Vec3d& v);
        void operator /=(real_t f);

        //Operators +,-.*,/
        Vec3d operator +(const Vec3d&v) const;
        Vec3d operator +(real_t f) const;
        Vec3d operator -(const Vec3d&v) const;
        Vec3d operator -(real_t f) const;
        Vec3d operator *(const Vec3d&v) const;
        Vec3d operator *(real_t f) const;
        Vec3d operator /(const Vec3d&v) const;
        Vec3d operator /(real_t f) const;

        Vec3d operator -() const;

    public:
        void normalize();
        real_t L2Norm_Sqr() const;
        real_t getNorm() const;
        // get the cross product of vec3d a and vec3d b
        static inline Vec3d cross(const Vec3d & a, const Vec3d & b);
        static inline real_t dot(const Vec3d & a, const Vec3d & b);
        static inline Vec3d maxVec();
        static inline Vec3d minVec();
        static inline Vec3d zeroVec();
        bool operator == (const Vec3d & a){
            return (isEqual(this->x,a.x) && isEqual(this->y, a.y) && isEqual(this->z,a.z));
        }

        bool operator != (const Vec3d & a){
            return !(this->operator == (a));
        }

    public:
        union
        {
            struct
            { real_t _p[3]; };
            struct
            { real_t x,y,z; };
            struct
            { real_t r,g,b; };
        };
        enum {_len = 3};

    }; // end of vec3d

    inline Vec3d Vec3d::cross(const Vec3d & a, const Vec3d & b){
        return Vec3d(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
    }

    inline real_t Vec3d::dot(const Vec3d & a, const Vec3d & b){
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    inline Vec3d Vec3d::maxVec(){
        return Vec3d(DBL_MAX,DBL_MAX,DBL_MAX);
    }
    inline Vec3d Vec3d::minVec(){
        return -Vec3d(DBL_MAX,DBL_MAX,DBL_MAX);
    }
    inline Vec3d Vec3d::zeroVec(){
        return Vec3d(0,0,0);
    }

}
#endif // !VEC3D_H
