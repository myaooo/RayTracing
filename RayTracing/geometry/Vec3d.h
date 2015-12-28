#ifndef VEC3D_H
#define VEC3D_H
#include <cassert>
#include <cstring>

    class Vec3d
    {
    public:

        //Constructors
        Vec3d();
        Vec3d(double x,double y, double z);
        Vec3d(const Vec3d& v);
        //Deconstructor
        virtual ~Vec3d();
    public:
        //Operators

        //Operator []
        inline double& operator [](int index)
        {
            assert(index>=0&&index<3);
            return _p[index];
        }
        inline const double& operator [](int index) const
        {
            assert(index>=0&&index<3);
            return _p[index];
        }

        //Operator ()
        inline double& operator ()(int index)
        {
            assert(index>=0&&index<3);
            return _p[index];
        }
        inline const double& operator ()(int index) const
        {
            assert(index>=0&&index<3);
            return _p[index];
        }

        //Operator =
        Vec3d& operator = (const Vec3d& v);

        //Operators +=,-=, *=, /=
        void operator +=(const Vec3d& v);
        void operator +=(double f);
        void operator -=(const Vec3d& v);
        void operator -=(double f);
        void operator *=(const Vec3d& v);
        void operator *=(double f);
        void operator /=(const Vec3d& v);
        void operator /=(double f);

        //Operators +,-.*,/
        Vec3d operator +(const Vec3d&v) const;
        Vec3d operator +(double f) const;
        Vec3d operator -(const Vec3d&v) const;
        Vec3d operator -(double f) const;
        Vec3d operator *(const Vec3d&v) const;
        Vec3d operator *(double f) const;
        Vec3d operator /(const Vec3d&v) const;
        Vec3d operator /(double f) const;

        Vec3d operator -() const;

    public:
        void Normalize();
        double L2Norm_Sqr() const;

    public:
        union
        {
            struct
            { double _p[3]; };
            struct
            { double x,y,z; };
            struct
            { double r,g,b; };
        };
        enum {_len = 3};

    };

#endif
