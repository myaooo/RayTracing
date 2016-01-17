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
//#include "meshObject.h"
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

        RTriangle(const vector<Vertex> & vertices, int a, int b, int c) :
            triangle(vertices[a], vertices[b], vertices[c]){}


        // Methods
        // input a ray, and get the intersection info
        virtual IntersectInfoPtr getIntersect(const Ray & ray) const override;
        virtual BBox getBBox() const override;

        virtual const TexturePtr & getTexture() const override;

    protected:
        Vec3d getNorm(real_t u, real_t v) const;
        Vec3d getNormFromVertex(int i) const;
        
    };

}
#endif
