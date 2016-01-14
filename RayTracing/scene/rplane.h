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
    private:
        Plane plane;
    public:
        // Constructors
        RPlane(){}
        RPlane(const Plane & pl, const TexturePtr & _texture) :
            Renderable(_texture), plane(pl){}
        RPlane(const Vec3d & p, const Vec3d& n, const TexturePtr & _texture) :
            Renderable(_texture), plane(p,n){}
        RPlane(real_t a, real_t b, real_t c, real_t d, const TexturePtr & _texture) :
            Renderable(_texture), plane(a,b,c,d){}
        // Methods
        // input a ray, and get the intersection info
        virtual IntersectInfo getIntersect(const Ray & ray) const override{
            real_t pos;
            IntersectType intersectType = plane.intersect(pos,ray);
            Vec3d intersectPoint = ray.getPoint(pos);
            return IntersectInfo(make_shared<RPlane>(*this),ray,intersectPoint,plane.norm,intersectType);
        }

        virtual BBox getBBox() const override{
            return BBox(Vec3d::minVec(), Vec3d::maxVec());
        }


    };

} // namespace end

#endif //!RPLANE_H
