//
//  material.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#include "material.h"
#include "../color.h"
#include "../util.h"
namespace RayTracing {

    const Color
        Material::TRANSPARENT(Color::WHITE*M_TRANS_GLASS),
        Material::SPECULATE_MIRROR(Color::WHITE*M_SPECULAR_MIRROR),
        Material::SPECULATE_NORMAL(Color::WHITE*M_SPECULAR_M);

    const Material
        Material::WHITE(Color::WHITE * M_DIFFUSE, Color::NONE, Color::NONE, M_AMBIENT_M, M_SHIN_LOW),
        Material::BLACK(Color::BLACK * M_DIFFUSE, Color::NONE, Color::NONE, M_AMBIENT_M, M_SHIN_LOW),
        Material::RED(Color::RED * M_DIFFUSE, Color::NONE, Color::NONE, M_AMBIENT_M, M_SHIN_LOW),
        Material::BLUE(Color::BLUE * M_DIFFUSE, Color::NONE, Color::NONE, M_AMBIENT_M, M_SHIN_LOW),
        Material::YELLOW(Color::YELLOW * M_DIFFUSE, Color::NONE, Color::NONE, M_AMBIENT_M, M_SHIN_LOW),
        Material::GREEN(Color::GREEN * M_DIFFUSE, Color::NONE, Color::NONE, M_AMBIENT_M, M_SHIN_LOW),
        Material::GLASS(Color::WHITE * M_DIFFUSE_L, SPECULATE_MIRROR, TRANSPARENT, M_AMBIENT_L, M_SHIN_SMOOTH),
        Material::MIRROR(Color::WHITE* M_DIFFUSE_L, SPECULATE_MIRROR, Color::NONE, M_AMBIENT_L, M_SHIN_SMOOTH),
        Material::WHITE_MIRROR(Color::WHITE * M_DIFFUSE_L, SPECULATE_MIRROR, Color::NONE, M_AMBIENT_M, M_SHIN_LOW),
        Material::BLACK_MIRROR(Color::BLACK * M_DIFFUSE_L, SPECULATE_MIRROR, Color::NONE, M_AMBIENT_M, M_SHIN_LOW);
}