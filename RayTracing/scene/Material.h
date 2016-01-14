//
//  material.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "../color.h"
#include "../util.h"
namespace RayTracing{
    // http://en.wikipedia.org/wiki/Phong_reflection_model
    class Material{
    public:
        // phong parameters
        Color diffuse;
        Color specular;
        real_t ambient;
        real_t shininess;

        // transparency
        real_t transparency;
        // refractivity
        real_t refractivity;

    public:
        // Constructor
        Material(){}
        Material( const Color & diff, const Color & spec,
                real_t ambt, real_t shin, real_t tran ) :
                diffuse(diff), specular(spec), ambient(ambt),
                shininess(shin), transparency(tran) {}

    };
}
#endif // !MATERIAL_H
