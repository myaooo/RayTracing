//
//  renderable.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#ifndef RENDERABLE_H
#define RENDERABLE_H
#include "texture.h"
#include "../geometry.h"
#include <memory>
#include <cmath>
#include "../util.h"

using std::shared_ptr;
using std::make_shared;

namespace RayTracing{
    using namespace MyMath;

    class Renderable;
    struct IntersectInfo;
    typedef shared_ptr<TextureBase> TexturePtr;
    typedef shared_ptr<Ray> RayPtr;
    typedef shared_ptr<Renderable> RenderablePtr;
    typedef shared_ptr<IntersectInfo> IntersectInfoPtr;

    // base class of all renderable objects
    class Renderable {
    private:
        TexturePtr texture;
    public:
        virtual ~Renderable(){};

        Renderable(const TexturePtr & _texture = nullptr) : texture(_texture) {}

        // set the texture of the objects to a new texture
        void setTexture(const TexturePtr & _texture){
            texture = _texture;
        }

        // get the texture of the rederable object as a constant
        const TexturePtr & getTexture() const{
            return texture;
        }

        // input a ray, and get the intersection info
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const = 0;

        virtual BBox getBBox() const = 0;
    };

    // base class that stores intersection information
    struct IntersectInfo{
    public:
        RenderablePtr renderablePtr = nullptr; // a pointer to the renderable object
        Ray inRay; // in ray
        real_t intersectPos = InfDistance;
        Vec3d norm = Vec3d::zeroVec; // the norm vector of the surface
        IntersectType intersectType = MISSED; // intersect type
        MaterialPtr materialPtr = nullptr; //  a pointer to the material
        real_t cosi = 0; // the cos value between -inray direction and norm
    public:
        // constructor
        IntersectInfo(){}
        IntersectInfo(const RenderablePtr & rptr, const Ray & inr,
            real_t pos, const Vec3d & n, const IntersectType & inttype) :
            renderablePtr(rptr), inRay(inr), intersectPos(pos),
            norm(n), intersectType(inttype) {

                materialPtr = renderablePtr->getTexture()->getMaterial();
                cosi = -Vec3d::dot(inRay.getDirection(),norm);
            }

        // get the reflective ray
        Ray getReflectRay(){
            Vec3d reflectDirect = inRay.getDirection() + norm * 2 * cosi;
            Ray ray(inRay.getPoint(intersectPos), reflectDirect);
            ray.offsetSource(Epsilon);
            return ray;
        }

        // get the refractive ray
        Ray getRefractRay(){
            real_t refractivity = materialPtr->refractivity;
            if (intersectType == INTERSECTED) {
                refractivity = 1/refractivity;
            }
            real_t cost = sqrt(1 - getSqr(refractivity) * (1 - getSqr(cosi)));
            Vec3d refractDirect = inRay.getDirection() * refractivity
                + norm * (cost - refractivity * cosi);
            Ray ray(inRay.getPoint(intersectPos), refractDirect);
            ray.offsetSource(Epsilon);
            return ray;
        }
        // get Intersect Point
        Vec3d getIntersectPoint(){
            return inRay.getPoint(intersectPos);
        }

        bool isReflectable() {
            return materialPtr->specular.getNormSqr() < Epsilon;
        }

        bool isRefractable() {
            return materialPtr->refract.getNormSqr() < Epsilon;
        }
    };
}

#endif //!RENDERABLE_H
