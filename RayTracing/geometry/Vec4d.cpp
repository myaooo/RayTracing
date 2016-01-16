//
//  Vec4d.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#include "../util.h"
#include "Vec4d.h"
#include <math.h>

namespace MyMath{
//////////////////////////////////////////////////////////////////////////
//  Constructors and Deconstructors
    Vec4d::Vec4d(void){
        memset(_p,0,sizeof(real_t)*_len);
    }

    Vec4d::Vec4d(real_t x, real_t y, real_t z, real_t w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vec4d::Vec4d(const Vec4d &v){
        memcpy(_p,v._p,sizeof(real_t)*_len);
    }

    Vec4d::~Vec4d(void){

    }

//////////////////////////////////////////////////////////////////////////
// Operators

    Vec4d& Vec4d::operator =( const Vec4d& v)
    {
        memcpy(_p,v._p,sizeof(real_t)*_len);
        return (*this);
    }

    void Vec4d::operator +=(const Vec4d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] += v._p[i];
    }
    void Vec4d::operator +=(real_t f)
    {
        for(int i=0;i<_len;i++)
            _p[i] += f;
    }

    void Vec4d::operator -=(const Vec4d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= v._p[i];
    }
    void Vec4d::operator -=(real_t f)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= f;
    }

    void Vec4d::operator *=(const Vec4d& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= v._p[i];
    }
    void Vec4d::operator *=(real_t f){
        for(int i=0;i<_len;i++)
            _p[i] *= f;
    }

    void Vec4d::operator /=(const Vec4d& v){
        for(int i=0;i<_len;i++)
            _p[i] /= v._p[i];
    }
    void Vec4d::operator /=(real_t f){
        for(int i=0;i<_len;i++)
            _p[i] /= f;
    }

    Vec4d Vec4d::operator +(const Vec4d&v) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + v[i];
        return res;
    }
    Vec4d Vec4d::operator +(real_t f) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + f;
        return res;
    }

    Vec4d Vec4d::operator -(const Vec4d&v) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - v[i];
        return res;
    }
    Vec4d Vec4d::operator -(real_t f) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - f;
        return res;
    }

    Vec4d Vec4d::operator *(const Vec4d&v) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * v[i];
        return res;
    }

    Vec4d Vec4d::operator *(real_t f) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * f;
        return res;
    }

    Vec4d Vec4d::operator /(const Vec4d&v) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / v[i];
        return res;
    }

    Vec4d Vec4d::operator /(real_t f) const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / f;
        return res;
    }

    Vec4d Vec4d::operator - () const{
        Vec4d res;
        for(int i=0;i<_len;i++)
            res[i] = -(*this)[i];
        return res;
    }

//////////////////////////////////////////////////////////////////////////
// Other Methods
    void Vec4d::Normalize(){
        if(_p[3] < 1e-6)
            (*this) *= 1.0f/_p[3];
    }

    real_t Vec4d::L2Norm_Sqr() const
    {
        return _p[0]*_p[0] + _p[1]*_p[1] + _p[2]*_p[2];
    }

}
