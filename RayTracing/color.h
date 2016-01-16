//
//  color.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/29.
//

#ifndef color_h
#define color_h

#include "geometry.h"
#include "util.h"
#include <iostream>
#include <cmath>
namespace RayTracing{
using namespace MyMath;
class Color : public Vec3d{
private:
    //Vec3d _data;
public:
    Color(){}
    Color(real_t r, real_t g, real_t b) : Vec3d(r,g,b){}
    Color(const Vec3d & cdata) : Vec3d(cdata){}
    Color(const Color & color) : Vec3d(color){}
    bool black() const
    { return fabs(r) < Epsilon && fabs(g) < Epsilon && fabs(b) < Epsilon; }

    bool valid() const {
        return (isBetween(r, 0, 1 + Epsilon)
                && isBetween(g, 0, 1 + Epsilon)
                && isBetween(b, 0, 1 + Epsilon));
    }

    Color operator + (const Color & c) const{
        return Color(this->Vec3d::operator + (c));
    }

    Color& operator += (const Color & c){
        this->Vec3d::operator += (c);
        return *this;
    }

    Color & operator = (const Color & c){
        this->Vec3d::operator = (c);
        return *this;
    }

    Color operator - (const Color & c) const{
        return Color(this->Vec3d::operator - (c));
    }

    Color& operator -= (const Color & c){
        this->Vec3d::operator -=(c);
        return *this;
    }

    Color operator * (real_t p) const{
        return Color(this->Vec3d::operator *(p));
    }

    Color& operator *= (real_t p){
        this->Vec3d::operator *= (p);
        return *this;
    }

    Color operator * (const Color& c) const{
        return Color(this->Vec3d::operator * (c));
    }

    Color& operator *= (const Color& c){
        this->Vec3d::operator *= (c);
        return *this;
    }

    Color operator / (real_t p) const{
        return *this * (1.0 / p);
    }

    Color normalize(){
        real_t maxi = getMax(r,getMax(g,b));
        this->Vec3d::operator /= (maxi);
        return *this;
    }



   friend std::ostream & operator << (std::ostream &os, const Color& c)
   { return os << c.r << " " << c.g << " " << c.b;}

   static const Color WHITE, BLACK, RED, BLUE, GREEN, YELLOW, MAGNETA, CYAN;

};

}
#endif /* color_h */
