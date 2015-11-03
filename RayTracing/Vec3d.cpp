#include "Vec3d.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

namespace RayTracing
{

//////////////////////////////////////////////////////////////////////////
//  Constructors and Deconstructors
    Vec3d::Vec3d(void)
    {
        memset(_p,0,sizeof(double)*_len);
    }
    
    Vec3d::Vec3d(double x, double y, double z)
    {
        this->_p[0] = x;
        this->_p[1] = y;
        this->_p[2] = z;
    }

    Vec3d::Vec3d(const Vec3d &v)
    {
        memcpy(_p,v._p,sizeof(double)*_len);
    }

    Vec3d::~Vec3d(void)
    {

    }

//////////////////////////////////////////////////////////////////////////
// Operators

    Vec3d& Vec3d::operator =( const Vec3d& v)
    {
        memcpy(_p,v._p,sizeof(double)*_len);        
        return (*this);
    }

    void Vec3d::operator +=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] += v._p[i];
    }
    void Vec3d::operator +=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] += f;
    }

    void Vec3d::operator -=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= v._p[i];
    }
    void Vec3d::operator -=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= f;
    }

    void Vec3d::operator *=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= v._p[i];
    }
    void Vec3d::operator *=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= f;
    }

    void Vec3d::operator /=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] /= v._p[i];
    }
    void Vec3d::operator /=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] /= f;
    }

    Vec3d Vec3d::operator +(const Vec3d&v) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + v[i];
        return res;
    }
    Vec3d Vec3d::operator +(double f) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + f;
        return res;
    }

    Vec3d Vec3d::operator -(const Vec3d&v) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - v[i];
        return res;
    }
    Vec3d Vec3d::operator -(double f) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - f;
        return res;
    }

    Vec3d Vec3d::operator *(const Vec3d&v) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * v[i];
        return res;
    }
    Vec3d Vec3d::operator *(double f) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * f;
        return res;
    }

    Vec3d Vec3d::operator /(const Vec3d&v) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / v[i];
        return res;
    }
    Vec3d Vec3d::operator /(double f) const
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / f;
        return res;
    }

    Vec3d Vec3d::operator - () const 
    {
        Vec3d res;
        for(int i=0;i<_len;i++)
            res[i] = -(*this)[i];
        return res;
    }

//////////////////////////////////////////////////////////////////////////
// Other Methods
    void Vec3d::Normalize()
    {
        double fSqr = L2Norm_Sqr();
        if(fSqr>1e-6)
            (*this) *= 1.0f/sqrt(fSqr);
    }

    double Vec3d::L2Norm_Sqr()
    {
        return _p[0]*_p[0] + _p[1]*_p[1] + _p[2]*_p[2];
    }
}


