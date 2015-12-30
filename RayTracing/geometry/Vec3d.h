#ifndef VEC3D_H
#define VEC3D_H
#include "../util.h"
#include <cassert>
#include <cstring>

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
    static inline Vec3d max();
    static inline Vec3d min();

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

};

#endif
