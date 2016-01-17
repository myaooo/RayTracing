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
#include "rplane.h"
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
        // Color
        Color color;
        // the intensities of diffuse and specular
        real_t Intensity;
        // method
        // constructor
        Light(const Color & d, real_t s) : Renderable(), color(d), Intensity(s){}
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override{
            std::cerr<<"Should not call this function @Light, getIntersectInfo.\n"<<std::endl;
            return nullptr;
        }
        virtual BBox getBBox() const override{
            std::cerr<<"Should not call this function @Light, getBBox.\n"<<std::endl;
            return BBox();
        }
        virtual ~Light(){
            Renderable::~Renderable();
        }

        // generate a ray targeting to the sourcePoint
        virtual Ray genRay(const Vec3d & sourcePoint) const = 0;

        void setColor(const Color & s);
        void setIntensity(real_t sS);
        Color getColor() const;
        real_t getIntensity() const;

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
        SphereLight(const Sphere & s, const Color & c, real_t i) :
            Light(c,i), RSphere(s) {}
        // Methods
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override;
        virtual BBox getBBox() const override;
        virtual Ray genRay(const Vec3d & source) const override;
        virtual ~SphereLight() {
            Light::~Light();
            RSphere::~RSphere();
        }

    };

    // Parallel Light
    class ParaLight : public Light, public RPlane{
    public:
        // method
        // Constructor
		// ParaLight(const Vec3d & orient);
        ParaLight(const Vec3d & orient, real_t d, const Light & light);

        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override;
        virtual BBox getBBox() const override;
        virtual Ray genRay(const Vec3d & source) const override;

    };

    // Light Obj
    /*class ObjLight : public Light{
        CSimpleObject obj;
    };
    */
}

#endif /* light_h */
