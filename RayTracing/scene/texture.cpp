
#include "texture.h"
#include "Material.h"
namespace RayTracing {
    const GridTexture
        GridTexture::BLACK_WHITE_MIRROR(Material::BLACK_MIRROR, Material::WHITE_MIRROR, 1),
        GridTexture::BLACK_WHITE(Material::BLACK, Material::WHITE,1);
}