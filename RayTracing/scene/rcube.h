//
//  rbox.h
//  RayTracing
//
//  Created by Ming Yao on 16/1/14.
//

#ifndef RCUBE_H
#define RCUBE_H
#include "renderable.h"
#include "../geometry.h"

namespace RayTracing {
    using MyMath::BBox;
    // renderable box
    class RCUBE : public Renderable {
    public:
        // data field
        Vec3d axis = Vec3d(0, 0, 1);
        BBox box;
    public:
        // Constructors
        RCUBE() {}
        RCUBE(const BBox & s, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), box(s) {}
        RCUBE(const Vec3d & _min, const Vec3d & _max, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), box(_min, _max) {}

        // Methods
        // input a ray, and get the intersection info
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override {
            real_t pos;
            IntersectType intersectType = box.intersect(pos, ray);
            if (intersectType == MISSED) {
                return nullptr;
            }
            //calculate norm
            Vec3d norm = Vec3d::zeroVec;
            Vec3d intersectPoint = ray.getPoint(pos);
            for (int i = 0; i < 3; ++i) {
                if (abs(intersectPoint[i] - box.minVec[i]) < Epsilon) {
                    norm[i] = -1;
                    break;
                }
                if (abs(intersectPoint[i] - box.maxVec[i]) < Epsilon) {
                    norm[i] = 1;
                    break;
                }
            }
            IntersectInfo info(make_shared<RCUBE>(*this), ray, pos, norm, intersectType);
            return make_shared<IntersectInfo>(info);
        }

        virtual BBox getBBox() const override {
            BBox anotherBox = box;
            // offset
            anotherBox.minVec -= Epsilon;
            anotherBox.maxVec += Epsilon;
            return anotherBox;
        }

    };

} // namespace end

#endif //!RCUBE_H
