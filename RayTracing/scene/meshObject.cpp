//
//  meshObject.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//


#include <string>
#include "rtriangle.h"
#include "kdtree.h"
#include "texture.h"
#include "meshObject.h"
#include "../MeshParser.h"
#include <algorithm>

namespace RayTracing {

    using namespace std;

    Mesh::Mesh(const char* fname, const Vec3d& m, real_t scl, const TexturePtr& _texture) :
        Renderable(_texture) {
        MeshParser parser;
        parser.LoadFromObj(*this, fname);
        cout << "verticesNum = " << vertices.size() << ", faceNum = " << faceIdx.size() << endl;
        transform(m,scl);
    }

    void Mesh::transform(const Vec3d & offset, real_t scale) {
        Vec3d sum;
        for (auto &k : vertices) sum = sum + k;
        Vec3d center = sum / vertices.size();

        for (Vertex& v : vertices)
            v = offset + (v - center) * scale;

        boundBox.minVec = offset + (boundBox.minVec -center) * scale;
        boundBox.maxVec = offset + (boundBox.maxVec -center) * scale;
    }

    void Mesh::finish() {		// build tree, calculate smooth norm
        if (smooth) {		// calculate vtx norm
            if (faceIdx.size() < 30) {
                printf("Number of faces is too small, cannot use smooth!\n");
                smooth = false;
            }
            else {
                int verticesNum = vertices.size();

                

                NormSum* norm_sum = new NormSum[verticesNum];
                for (auto & t : faceIdx) {
                    int a = t[0], b = t[1], c = t[2];
                    Vec3d tmp_norm = Triangle(vertices[a], vertices[b], vertices[c]).norm;
                    // norms might be in opposite direction ? obj gives vertexes in correct order
                    norm_sum[a].add(tmp_norm);
                    norm_sum[b].add(tmp_norm);
                    norm_sum[c].add(tmp_norm);
                }
                for (int k = 0; k < verticesNum; k++)
                    norms[k] = norm_sum[k].sum / norm_sum[k].cnt;
                delete[] norm_sum;
            }
        }

        for (auto &ids : faceIdx) addTriangle(ids);
        if (enableTree)
            tree = shared_ptr<KdTree>(new KdTree(list<RenderablePtr>(faces.begin(), faces.end())));
    }

    IntersectInfoPtr Mesh::getIntersect(const Ray& ray) const {
        if (enableTree)
            return tree->getIntersect(ray);

        IntersectInfoPtr info = nullptr;
        real_t minDistance = InfDistance;

        for (auto & face : faces) {
            auto tmp = face->getIntersect(ray);
            if (tmp!= nullptr && tmp->intersectPos < minDistance) {
                minDistance = tmp->intersectPos;
                info = tmp;
            }
        }
        return info;
    }


}

