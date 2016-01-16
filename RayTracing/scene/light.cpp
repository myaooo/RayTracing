//
//  light.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#include "light.h"

namespace RayTracing {

    /*
    * Light
    */
    void Light::setColor(const Color & s) {
        color = s;
    }
    void Light::setIntensity(real_t dS) {
        assert(dS > 0);
        Intensity = dS;
    }
    Color Light::getColor() const {
        return color;
    }
    real_t Light::getIntensity() const {
        return Intensity;
    }

    /*
    * SphereLight
    */
    IntersectInfoPtr SphereLight::getIntersect(const Ray & ray) const {
        return RSphere::getIntersect(ray);
    }

    BBox SphereLight::getBBox() const {
        return RSphere::getBBox();
    }

    Ray SphereLight::genRay(const Vec3d & source) const {
        Vec3d direction = RSphere::getCenter() - source;
        real_t range = direction.getNorm();
        return Ray(source, direction, range);
    }

    /*
    * ParaLight
    */
    ParaLight::ParaLight(const Vec3d & orient, real_t d, const Light & light) :
        RPlane(orient,d), Light(light) {}
    IntersectInfoPtr ParaLight::getIntersect(const Ray & ray) const {
        return RPlane::getIntersect(ray);
    }

    BBox ParaLight::getBBox() const {
        return RPlane::getBBox();
    }

    Ray ParaLight::genRay(const Vec3d & source) const {
        return Ray(source, plane.norm);
    }

}
