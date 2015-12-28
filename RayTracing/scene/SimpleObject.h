#pragma once
#include "../geometry/Vec3d.h"
#include <vector>

namespace RayTracing
{
    //typedef MyMath::Vec3d<3> Vec3d;
	// A definition of array
	// Later used to store triangle list
    template <typename T, int N> class Array 
    {
    public:
        enum {_len = N};
        typedef T t_Val; 
    public:
        T& operator[] (int i)
        {
            assert(i>=0&&i<N);
            return _p[i];
        }
        const T& operator[] (int i) const 
        {
            assert(i>=0&&i<N);
            return _p[i];
        }

    protected:
        T _p[N];
    }; // end of class Array
	

    class CSimpleObject
    {
    public:
		typedef Array<int, 3> Triangleidx;
        CSimpleObject(void);
        ~CSimpleObject(void);
        
    public:
        bool IsLoaded() { return m_pVertexList!=NULL;}

        void Destroy();
        bool LoadFromObj(const char* fn);
        bool SaveToObj(const char* fn);
        
    protected:
        bool Parse(FILE* fp);
        bool CheckParse(int nVertices,std::vector<Array<int,3> > & vecTriangles);

    protected:

        int             m_nVertices;
        int             m_nTriangles;
        Vec3d*          m_pVertexList;
        Triangleidx*	m_pTriangleList;
    };

}
