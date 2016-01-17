//
//  rsphere.h
//  RayTracing
//
//  Created by Ming Yao on 16/1/14.
//

#ifndef RSPEHERE_H
#define RSPEHERE_H
#include "renderable.h"
#include "../geometry.h"

namespace RayTracing{
    using MyMath::Sphere;
    // renderable sphere
    class RSphere : public Renderable{
    public:
        // data field
        Vec3d axis = Vec3d(0,0,1);
        Sphere sphere;
    public:
        // Constructors
        RSphere(){}
        RSphere(const Sphere & s, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), sphere(s){}
        RSphere(const Vec3d & c, real_t r, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), sphere(c,r){}

        // Methods
        // input a ray, and get the intersection info
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override{
            real_t pos;
            IntersectType intersectType = sphere.intersect(pos,ray);
            if (intersectType == MISSED) {
                return nullptr;
            }
            Vec3d norm = ray.getPoint(pos)-sphere.center;
            norm.normalize();
            IntersectInfo info(make_shared<RSphere>(*this),ray,pos,norm,intersectType);
            getMaterial(info);
            return make_shared<IntersectInfo>(info);
        }

        virtual BBox getBBox() const override{
            return BBox(sphere.center-sphere.radius, sphere.center+sphere.radius);
        }

        Vec3d getCenter() const{
            return sphere.center;
        }

        real_t getRadius() const{
            return sphere.radius;
        }

        void setCenter(const Vec3d & vec){
            sphere.center = vec;
        }

        void setRadius(real_t r){
            assert(r>0);
            sphere.radius = r;
        }
    protected:
        void RSphere::getMaterial(IntersectInfo & info) const {
            //assert(fabs(sphere.axis.sqr() - 1) < EPS);
            Vec3d norm = info.norm;
            Vec3d projxy = Vec3d(norm.x, norm.y, 0),
                projyz = Vec3d(0, norm.y, norm.z);
            real_t arg1 = acos(Vec3d::dot(projxy,axis)),		// 0 to pi
                arg2 = acos(Vec3d::dot(projyz,axis));
            info.materialPtr = this->getTexture()->getMaterial(arg1 * sphere.radius, arg2 * sphere.radius);
            return;
        }

    };

} // namespace end

#endif //!RSPEHERE_H
