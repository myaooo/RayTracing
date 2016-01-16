//
//  light.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#include "light.h"

namespace RayTRacing{

    /*
    * Light
    */
    void Light::setDiffuse(const Color & d){
        diffuse = d;
    }
    void Light::setSpecular(const Color & s){
        specular = s;
    }
    void Light::setDIntensity(real_t dS){
        assert(dS > 0);
        DIntensity = dS;
    }
    void Light::setSIntensity(real_t sS){
        assert(sS > 0);
        SIntensity = sS;
    }
    Color Light::getDiffuse() const{
        return diffuse;
    }
    Color Light::getSpecular() const{
        return specular;
    }
    real_t Light::getDIntensity() const{
        return DIntensity;
    }
    real_t Light::getSIntensity() const{
        return SIntensity;
    }

    /*
    * SphereLight
    */
    virtual IntersectInfoPtr SphereLight::getIntersect(const Ray & ray) const {
        return RSphere::getIntersect(ray);
    }

    virtual BBox SphereLight::getBBox() const {
        return RSphere::getBBox();
    }

    virtual Ray SphereLight::genRay(const Vec3d & source) const {
        Vec3d direction = RSphere::getCenter() - source;
        real_t range = direction.getNorm();
        return Ray(source,direction,range);
    }

    /*
    * ParaLight
    */
    virtual IntersectInfoPtr ParaLight::getIntersect(const Ray & ray) const {
        return RSphere::getIntersect(ray);
    }

    virtual BBox ParaLight::getBBox() const {
        return RSphere::getBBox();
    }

    virtual Ray ParaLight::genRay(const Vec3d & source) const {
        Vec3d direction = RSphere::getCenter() - source;
        real_t range = direction.getNorm();
        return Ray(source,direction,range);
    }

}
