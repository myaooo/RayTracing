#pragma once
#include "../geometry.h"
#include <vector>
#include <array>
#include "meshObject.h"
namespace RayTracing
{
    using namespace MyMath;

    class CSimpleObject
    {
    public:
		typedef array<int, 3> TriangleIdx;
        CSimpleObject(void);
        ~CSimpleObject(void);
        
    public:
        bool IsLoaded() { return !m_pVertexList.empty();}

        void Destroy();
        bool LoadFromObj(const char* fn);
        bool SaveToObj(const char* fn);
        static bool LoadFromObj(Mesh & m, const char* fn);
        static bool saveObj(Mesh & m, const char* fn);
        
    protected:
        bool Parse(FILE* fp);
        bool CheckParse(int nVertices,std::vector<TriangleIdx> & vecTriangles);

    protected:

        int             m_nVertices;
        int             m_nTriangles;
        vector<Vec3d> m_pVertexList;
        vector<TriangleIdx>	m_pTriangleList;
    };

}
