#include "util.h"
#include "Vec3d.h"
#include <math.h>
#include "float.h"

namespace MyMath{
//////////////////////////////////////////////////////////////////////////
//  Constructors and Deconstructors
    Vec3d::Vec3d(void)
    {
        memset(_p,0,sizeof(real_t)*_len);
    }

    Vec3d::Vec3d(real_t x, real_t y, real_t z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3d::Vec3d(const Vec3d &v)
    {
        memcpy(_p,v._p,sizeof(real_t)*_len);
    }

    Vec3d::~Vec3d(void)
    {

    }

//////////////////////////////////////////////////////////////////////////
// Operators

    Vec3d& Vec3d::operator =( const Vec3d& v)
    {
        memcpy(_p,v._p,sizeof(real_t)*_len);
        return (*this);
    }

    void Vec3d::operator +=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] += v._p[i];
    }
    void Vec3d::operator +=(real_t f)
    {
        for(int i=0;i<_len;i++)
            _p[i] += f;
    }

    void Vec3d::operator -=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= v._p[i];
    }
    void Vec3d::operator -=(real_t f)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= f;
    }

    void Vec3d::operator *=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= v._p[i];
    }
    void Vec3d::operator *=(real_t f)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= f;
    }

    void Vec3d::operator /=(const Vec3d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] /= v._p[i];
    }
    void Vec3d::operator /=(real_t f)
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
    Vec3d Vec3d::operator +(real_t f) const
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
    Vec3d Vec3d::operator -(real_t f) const
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
    Vec3d Vec3d::operator *(real_t f) const
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
    Vec3d Vec3d::operator /(real_t f) const
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
    void Vec3d::normalize()
    {
        real_t fSqr = getNorm();
        if(fSqr>Epsilon)
            (*this) *= 1.0f/fSqr;
    }

    real_t Vec3d::getNormSqr() const
    {
        return _p[0]*_p[0] + _p[1]*_p[1] + _p[2]*_p[2];
    }

    real_t Vec3d::getNorm() const{
        return sqrt(this->getNormSqr());
    }

    const Vec3d Vec3d::maxVec(DBL_MAX,DBL_MAX,DBL_MAX),
                Vec3d::minVec(-DBL_MAX,-DBL_MAX,-DBL_MAX),
                Vec3d::zeroVec(0,0,0);

} // end of namespace MyMath
