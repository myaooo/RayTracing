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

    // base class of all renderable objects
    class Renderable {
    private:
        TexturePtr texture = nullptr;
    public:
        virtual ~Renderable(){};

        Renderable(){}

        Renderable(const TexturePtr & _texture) : texture(_texture) {}

        // set the texture of the objects to a new texture
        void setTexture(const TexturePtr & _texture){
            texture = _texture;
        }

        // get the texture of the rederable object as a constant
        const TexturePtr & getTexture() const{
            return texture;
        }

        // input a ray, and get the intersection info
        virtual IntersectInfo getIntersect(const Ray & ray) const = 0;

        virtual BBox getBBox() const = 0;
    };

    // base class that stores intersection information
    struct IntersectInfo{
    public:
        RenderablePtr renderablePtr; // a pointer to the renderable object
        const Ray & inRay; // in ray
        Vec3d intersectPoint; // intersect point
        Vec3d norm; // the norm vector of the surface
        IntersectType intersectType; // intersect type
        MaterialPtr materialPtr; //  a pointer to the material
        real_t cosi; // the cos value between -inray direction and norm
    public:
        // constructor
        //IntersectInfo(){}
        IntersectInfo(const RenderablePtr & rptr, const Ray & inr,
            const Vec3d & intp, const Vec3d & n, const IntersectType & inttype) :
            renderablePtr(rptr), inRay(inr), intersectPoint(intp),
            norm(n), intersectType(inttype) {

                materialPtr = renderablePtr->getTexture()->getMaterial();
                cosi = -Vec3d::dot(inRay.getDirection(),norm);
            }

        // get the reflective ray
        Ray getReflectRay(){
            Vec3d reflectDirect = inRay.getDirection() + norm * 2 * cosi;
            return Ray(intersectPoint, reflectDirect);
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
            return Ray(intersectPoint, refractDirect);
        }
    };
}

#endif //!RENDERABLE_H
