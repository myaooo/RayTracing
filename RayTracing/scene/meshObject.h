//
//  meshObject.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include <string>
#include "rtriangle.h"
#include "kdtree.h"
#include "texture.h"

class MeshSimplifier;
namespace RayTracing {
    
    class Mesh : public Renderable {
        typedef MyMath::Vec3d Vertex;
        typedef std::array<int, 3> TriangleIdx;
    public:
        // config
        bool smooth = true;
        bool mapped = false;
        bool enableTree = true;
        // data fields
        vector<Vertex> vertices;
        vector<Vec3d> norms;
        vector<shared_ptr<RTriangle>> faces;
        vector<TriangleIdx> faceIdx;
        KdTreePtr tree;
        BBox boundBox;
    public:
        Mesh() {}

        Mesh(const Mesh& r) :Renderable(r.getTexture()) {
            smooth = r.smooth;
            mapped = r.mapped;
            enableTree = r.enableTree;
            vertices = r.vertices;
            faces = r.faces;
            faceIdx = r.faceIdx;
            boundBox.minVec = r.boundBox.minVec;
            boundBox.maxVec = r.boundBox.maxVec;
            tree = r.tree;
            for (auto & k : faces) k->owner = this;
        }

        Mesh(const char* fname, const Vec3d& _pivot,
            real_t _zsize, const TexturePtr & _texture = nullptr);

#define isValid(x) (x) < (int)vertices.size()
        void addVertex(const Vec3d& p) {
            vertices.emplace_back(p);
            boundBox.unite(p);
        }

        void addFaceIdx(int a, int b, int c) {
            assert(isValid(getMax(a, getMax(b, c))));
            faceIdx.emplace_back(array < int, 3 > {{a, b, c}});
        }

        void addTriangle(const TriangleIdx & t) {
            addTriangle(t[0], t[1], t[2]);
        }

        void transform(const Vec3d & offset, real_t scale);

        void config();

        //void simplify(real_t ratio);

        void clear() {
            vertices.clear();
            faces.clear();
            faceIdx.clear();
            boundBox = BBox();
            tree = nullptr;
        }

        IntersectInfoPtr getIntersect(const Ray& ray) const override;

        BBox getBBox() const override {
            return BBox(boundBox.minVec, boundBox.maxVec);
        }

    protected:
        void addTriangle(int a, int b, int c);
    };

    struct NormSum {
        Vec3d sum = Vec3d::zeroVec;
        int count = 0;
        void add(const Vec3d& v) {
            sum = sum + v; 
            count++; 
        }
    };
}
#endif