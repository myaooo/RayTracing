//
//  light.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef light_h
#define light_h

#include "../color.h"
#include "../geometry.h"
#include "../util.h"
#include "renderable.h"
#include "rsphere.h"
#include "SimpleObject.h"
#include <memory>
#include <cassert>
#include <iostream>

namespace RayTracing{
    class Light;
    typedef std::shared_ptr<Light> LightPtr;
    // Light
    class Light : public Renderable{
    // http://en.wikipedia.org/wiki/Phong_reflection_model
    public:
        // data field
        // diffuse color and specular color of the light
        Color diffuse, specular;
        // the intensities of diffuse and specular
        real_t DIntensity, SIntensity;
        // method
        // constructor
        Light(const Color & d, const Color & s, real_t dStrength, real_t sStrength) :
            Renderable(), diffuse(d), specular(s),
            DIntensity(dStrength), SIntensity(sStrength){}
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override{
            std::cerr<<"Should not call this function @Light, getIntersectInfo.\n"<<std::endl;
        }
        virtual BBox getBBox() const override{
            std::cerr<<"Should not call this function @Light, getBBox.\n"<<std::endl;
        }

        // generate a ray targeting to the sourcePoint
        virtual Ray genRay(const Vec3d & sourcePoint) const = 0;

        void setDiffuse(const Color & d);
        void setSpecular(const Color & s);
        void setDIntensity(real_t dS);
        void setSIntensity(real_t sS);
        Color getDiffuse() const;
        Color getSpecular() const;
        real_t getDIntensity() const;
        real_t getSIntensity() const;

    };
    // Sphere Light
    // when the radius of the sphere is very small, we can regard it as a point light
    class SphereLight : public Light, public RSphere{
    public:
        // data field
        // method
        // constructor
        SphereLight(const Sphere & s, const Light & light) :
            Light(light), RSphere(s){}

        // Methods
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override;
        virtual BBox getBBox() const override;
        virtual Ray genRay(const Vec3d & source) const override;

    };

    // Parallel Light
    class ParaLight : public Light{
    public:
        // data field
        Vec3d orient;
        // method
        // Constructor
		// ParaLight(const Vec3d & orient);
        ParaLight(const Vec3d & orient, const Light & light);

        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override;
        virtual BBox getBBox() const override;
        virtual Ray genRay(const Vec3d & source) const override;

    };

    // Light Obj
    class ObjLight : public Light{
        CSimpleObject obj;
    };
}

#endif /* light_h */
