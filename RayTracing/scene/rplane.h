//
//  rplane.h
//  RayTracing
//
//  Created by Ming Yao on 16/1/14.
//

#ifndef RPLANE_H
#define RPLANE_H
#include "renderable.h"
#include "../geometry.h"

namespace RayTracing{
    typedef MyMath::Plane Plane;
    // renderable plane
    class RPlane : public Renderable{
    public:
        Plane plane;
        Vec3d center;
        Vec3d horiVec;
    public:
        // Constructors
        RPlane(){}
        RPlane(const Plane & pl, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), plane(pl){
            setCenter();
        }
        RPlane(const Vec3d & p, const Vec3d& n, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), plane(p,n){
            setCenter();
        }
        RPlane(const Vec3d & n, real_t d, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), plane(n,d) {
            setCenter();
        }
        RPlane(real_t a, real_t b, real_t c, real_t d, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), plane(a,b,c,d){
            setCenter();
        }
        // Methods
        // input a ray, and get the intersection info
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override{
            real_t pos;
            IntersectType intersectType = plane.intersect(pos,ray);
            if (intersectType == MISSED) {
                return nullptr;
            }
            IntersectInfo info(make_shared<RPlane>(*this), ray, pos, plane.norm, intersectType);
            info.materialPtr = this->getMaterial(info.getIntersectPoint());
            return make_shared<IntersectInfo>(info);
        }

        virtual BBox getBBox() const override{
            return BBox(Vec3d::minVec, Vec3d::maxVec);
        }

        virtual bool isinfinite() const override {
            return true;
        }

    protected:
        void setCenter() {
            center = plane.norm * plane.d;
            if ((fabs(plane.norm.y) > Epsilon) || (fabs(plane.norm.x) > Epsilon)) {
                horiVec = Vec3d(-plane.norm.y, plane.norm.x, 0);
            }
            else {
                horiVec = Vec3d(-plane.norm.z, 0, plane.norm.x);
            }
            horiVec.normalize();
        }

        MaterialPtr getMaterial(const Vec3d & intersectPoint) const{
            Vec3d diff = intersectPoint - center;
            real_t x = Vec3d::dot(diff, horiVec);
            real_t y = Vec3d::dot(diff,Vec3d::cross(horiVec,plane.norm));
            return this->getTexture()->getMaterial(x, y);
        }

    };

} // namespace end

#endif //!RPLANE_H
