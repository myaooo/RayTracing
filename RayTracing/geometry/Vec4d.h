//
//  Vec4d.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#ifndef VEC4D_H
#define VEC4D_H

#include "../util.h"
#include <cassert>
#include <cstring>
#include <cmath>

namespace MyMath{
    class Vec4d{
    public:

        //Constructors
        Vec4d();
        Vec4d(real_t x,real_t y, real_t z, real_t w);
        Vec4d(const Vec4d& v);
        //Deconstructor
        virtual ~Vec4d();
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
        Vec4d& operator = (const Vec4d& v);

        //Operators +=,-=, *=, /=
        void operator +=(const Vec4d& v);
        void operator +=(real_t f);
        void operator -=(const Vec4d& v);
        void operator -=(real_t f);
        void operator *=(const Vec4d& v);
        void operator *=(real_t f);
        void operator /=(const Vec4d& v);
        void operator /=(real_t f);

        //Operators +,-.*,/
        Vec4d operator +(const Vec4d&v) const;
        Vec4d operator +(real_t f) const;
        Vec4d operator -(const Vec4d&v) const;
        Vec4d operator -(real_t f) const;
        Vec4d operator *(const Vec4d&v) const;
        Vec4d operator *(real_t f) const;
        Vec4d operator /(const Vec4d&v) const;
        Vec4d operator /(real_t f) const;

        Vec4d operator -() const;

    public:
        void Normalize();
        real_t L2Norm_Sqr() const;

    public:
        union
        {
            struct
            { real_t _p[4]; };
            struct
            { real_t x,y,z,w; };
            struct
            { real_t r,g,b,a; };
        };
        enum {_len = 4};

    };

}

#endif // !VEC4D_H
