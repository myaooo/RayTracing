//
//  rtriangle.h
//  RayTracing
//
//  Created by Ming Yao on 16/01/10.
//

#ifndef RTRIANGLE_H
#define RTRIANGLE_H

#include "renderable.h"
#include "../geometry.h"
#include <vector>
#include <array>

namespace RayTracing {
    using namespace std;
    using MyMath::Triangle;
    
    class Mesh;
    // renderable triangle
    class RTriangle : public Renderable {
        typedef MyMath::Vec3d Vertex;
        typedef std::array<int, 3> TriangleIdx;
    public:
        // data field
        Triangle triangle;
        Mesh * owner;
        TriangleIdx idxs;
    public:
        // Constructors
        RTriangle() {}
        RTriangle(const Triangle & s, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), triangle(s) {}
        RTriangle(const Vec3d& a, const Vec3d& b, const Vec3d& c, const TexturePtr & _texture = nullptr) :
            Renderable(_texture), triangle(a, b, c) {}

        RTriangle(const vector<Vertex> & vertices, int a, int b, int c) {
            RTriangle(vertices[a], vertices[b], vertices[c]);
        }


        // Methods
        // input a ray, and get the intersection info
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override {
            real_t pos;
            IntersectType intersectType = triangle.intersect(pos, ray);
            if (intersectType == MISSED) {
                return nullptr;
            }
            IntersectInfo info(make_shared<RTriangle>(*this), ray, pos, triangle.norm, intersectType);
            if (info.materialPtr == nullptr)
                std::cerr << "triangle do not have material!" << std::endl;;
            return make_shared<IntersectInfo>(info);
        }

        virtual BBox getBBox() const override {
            BBox box;
            box.unite(triangle.source);
            box.unite(triangle.source + triangle.e1);
            box.unite(triangle.source + triangle.e2);
            // offset to ensure box contains triangle(avoid box split)
            box.minVec -= Epsilon * 2;
            box.maxVec += Epsilon * 2;
            return box;
        }
    };

}
#endif
