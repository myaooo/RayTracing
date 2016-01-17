
#include "rtriangle.h"
#include "meshObject.h"

namespace RayTracing {
    // Methods
    // input a ray, and get the intersection info
    IntersectInfoPtr RTriangle::getIntersect(const Ray & ray) const {
        real_t pos;
        IntersectType intersectType;
        real_t u, v;
        if (triangle.intersectTriangle(ray, pos, u, v)) {
            if (Vec3d::dot(ray.getDirection(), triangle.norm) < 0)
                intersectType = INSIDE;
            else
                intersectType = INTERSECTED;
        }
        else
            return nullptr;
        Vec3d normVec = getNorm(u, v);
        IntersectInfo info(make_shared<RTriangle>(*this), ray, pos, normVec, intersectType);
        if (info.materialPtr == nullptr)
            info.materialPtr = this->owner->getTexture()->getMaterial();
        return make_shared<IntersectInfo>(info);
    }

    BBox RTriangle::getBBox() const {
        BBox box;
        box.unite(triangle.source);
        box.unite(triangle.source + triangle.e1);
        box.unite(triangle.source + triangle.e2);
        // offset to ensure box contains triangle(avoid box split)
        box.minVec -= Epsilon * 2;
        box.maxVec += Epsilon * 2;
        return box;
    }

    Vec3d RTriangle::getNorm(real_t u, real_t v) const {
        if (owner->smooth)
            return triangle.norm;
        Vec3d norm_r = getNormFromVertex(0) * (1 - u - v) + getNormFromVertex(1) * u + getNormFromVertex(2) * v;
        norm_r.normalize();
        return norm_r;
    }
    Vec3d RTriangle::getNormFromVertex(int i) const {
        return owner->norms[idxs[i]];
    }

    const TexturePtr & RTriangle::getTexture() const {
        return owner->getTexture();
    }
}