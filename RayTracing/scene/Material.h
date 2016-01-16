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

#define M_SPECULAR_L 0.1
#define M_SPECULAR_M 0.3
#define M_SPECULAR_H 0.6
#define M_SPECULAR_MIRROR 1
#define M_TRANS_GLASS 0.95
#define M_TRANS_M 0.5
#define M_DIFFUSE_L 0.1
#define M_DIFFUSE 0.8
#define M_SHIN_SMOOTH 30
#define M_SHIN_LOW 15
#define M_AMBIENT_L 0.2
#define M_AMBIENT_M 0.5
#define M_AMBIENT_H 0.8
#define M_REFRACTIVITY 1.2
namespace RayTracing{
    // http://en.wikipedia.org/wiki/Phong_reflection_model
    class Material{
    public:
        // phong parameters
        Color diffuse;
        Color specular;
        Color refract;
        real_t ambient;
        real_t shininess;

        // refractivity
        real_t refractivity;

    public:
        // Constructor
        Material(){}
        Material( const Color & diff, const Color & spec, const Color & refr,
                real_t ambt, real_t shin, real_t rfty = 1) :
                diffuse(diff), specular(spec), refract(refr), ambient(ambt),
                shininess(shin), refractivity(rfty){}
        static const Color TRANSPARENT, SPECULATE_MIRROR, SPECULATE_NORMAL;
        static const Material BLACK, RED, WHITE, BLUE, GREEN, GLASS, MIRROR, YELLOW,
            WHITE_MIRROR, BLACK_MIRROR;

    };
}
#endif // !MATERIAL_H
