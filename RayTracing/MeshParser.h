//
//  meshparser.h
//  RayTracing
//
//  Created by Ming Yao on 16/1/14.
//

#ifndef MESHPARSER_H
#define MESHPARSER_H

#include "geometry.h"
#include <vector>
#include <array>
#include "scene/meshObject.h"
namespace RayTracing {
    using namespace MyMath;

    class MeshParser {
        typedef std::array<int, 3> TriangleIdx;
    public:
        MeshParser(void) {}
        ~MeshParser(void) {}

    public:
        bool IsLoaded(const Mesh & m) const{ return !m.vertices.empty(); }
        bool LoadFromObj(Mesh & m, const char* fn) const;
        bool SaveToObj(const Mesh & m, const char* fn) const;

    protected:
        bool Parse(Mesh & m, FILE* fp) const;
        bool CheckParse(int nVertices, const Mesh & mesh)const;

    protected:

    };

}

#endif // MESHPARSER_H