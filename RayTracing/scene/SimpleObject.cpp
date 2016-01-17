
#include "SimpleObject.h"
#include <vector>

using namespace std;

namespace RayTracing
{
    MeshParser::MeshParser(void)
    {
        Mesh.vertices = -1;
        m_nTriangles = -1;
    }

    MeshParser::~MeshParser(void)
    {
        Destroy();
    }

    void MeshParser::Destroy()
    {
        Mesh.vertices = -1;
        m_nTriangles = -1;
        m_pVertexList.clear();
        m_pTriangleList.clear();
    }

    bool MeshParser::LoadFromObj(const char* fn)
    {
        FILE* fp = fopen(fn,"r");
        if(fp==NULL)
        {
            printf("Error: Loading %s failed.\n",fn);
            return false;
        }
        else
        {
            if(Parse(fp))
            {
                printf("Loading from %s successfully.\n",fn);
                printf("Vertex Number = %d\n",Mesh.vertices);
                printf("Triangle Number = %d\n",m_nTriangles);
                fclose(fp);
                return true;
            }
            else
            {
                fclose(fp);
                return false;
            }
        }
    }

    bool MeshParser::Parse(FILE* fp)
    {
        
        char buf[256];
        int nVertices,nTriangles;
        std::vector<Vec3d>          vecVertices;
        std::vector<TriangleIdx >  vecTriangles;

        nVertices = 0;
        nTriangles = 0;
        vecVertices.clear();
        vecTriangles.clear();
        int lineNumber = 0; 

        while(fscanf(fp, "%s", buf) != EOF)
        {
            lineNumber ++;
            switch(buf[0])
            {
            case '#':				/* comment */
                /* eat up rest of line */
                fgets(buf, sizeof(buf), fp);
                break;
            case 'v':				/* v, vn, vt */
                switch(buf[1])
                {
                case '\0':			    /* vertex */
                    {
                        Vec3d vP;
                        if(fscanf(fp, "%lf %lf %lf",
                            &vP._p[0],
                            &vP._p[1],
                            &vP._p[2])==3)
                        {
                            nVertices++;
                            vecVertices.push_back(vP);
                        }
                        else 
                        {
                            printf("Error: Wrong Number of Values(Should be 3). at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    break;
                default:
                    /* eat up rest of line */
	                fgets(buf, sizeof(buf), fp);
                    break;
                }
                break;

            case 'f':				/* face */
                {
                    int v,n,t;
                    TriangleIdx vIndices;
                    if(fscanf(fp, "%s", buf)!=1)
                    {
                        printf("Error: Wrong Face at Line %d\n",lineNumber);
                        return false;
                    }
                    
                    /* can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d */
                    if (strstr(buf, "//"))
                    {
                        /* v//n */
                        if( sscanf(buf, "%d//%d", &vIndices[0],&n) ==2  &&
                            fscanf(fp, "%d//%d", &vIndices[1], &n) ==2  &&
                            fscanf(fp, "%d//%d", &vIndices[2], &n) ==2)
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }

                    }
                    else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3)
                    {
                        /* v/t/n */
                        vIndices[0] = v;
                        if( fscanf(fp, "%d/%d/%d", &vIndices[1], &t, &n) ==3 &&
                            fscanf(fp, "%d/%d/%d", &vIndices[2], &t, &n) ==3 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    else if (sscanf(buf, "%d/%d", &v, &t) == 2)
                    {
                        /* v/t */
                        vIndices[0] = v;
                        if( fscanf(fp, "%d/%d", &vIndices[1], &t) ==2 &&
                            fscanf(fp, "%d/%d", &vIndices[2], &t) ==2 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    else
                    {
                        /* v */
                        if( sscanf(buf, "%d", &vIndices[0]) ==1 && 
                            fscanf(fp, "%d", &vIndices[1])  ==1 &&
                            fscanf(fp, "%d", &vIndices[2])  ==1 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }

                }

                break;

            default:
                /* eat up rest of line */
                fgets(buf, sizeof(buf), fp);
                break;
            }
        }
        
        if(CheckParse(int(vecVertices.size()),vecTriangles))
        {
            Destroy();
            
            Mesh.vertices = int(vecVertices.size());
            m_nTriangles = int(vecTriangles.size());
            m_pVertexList = vector<Vec3d>(Mesh.vertices);
            m_pTriangleList = vector<TriangleIdx>(m_nTriangles);

            for(int i=0;i<Mesh.vertices;i++)
                m_pVertexList[i] = vecVertices[i];
            for(int i=0;i<m_nTriangles;i++)
            {
                for(int j=0;j<3;j++)
                m_pTriangleList[i][j] = vecTriangles[i][j] - 1;
            }

            return true;
        }
        else
            return false;
    }

    bool MeshParser::CheckParse(int nVertices,std::vector<TriangleIdx > & vecTriangles)
    {
        for(int i=0;i<vecTriangles.size();i++)
        {
            TriangleIdx & vIndices = vecTriangles[i];
            for(int j=0;j<vIndices.size();j++)
                if(vIndices[j]<=0||vIndices[j]>nVertices)
                {
                    printf("Error: The vertex index of Face %d has exceeded vertex number %d\n",i,nVertices);
                    return false;
                }
        }

        return true;
    }

    bool MeshParser::SaveToObj(const char* fn)
    {
        if(!IsLoaded())
        {
            printf("Error: Object is not initialized. %s\n",fn);
            return false;
        }
        
        FILE* fp = fopen(fn,"w");
        if(fp==NULL)
        {
            printf("Error: Failed opening %s to write\n",fn);
            return false;
        }

        fprintf(fp,"# %d vertices\n",Mesh.vertices);
        for(int i=0;i<Mesh.vertices;i++)
            fprintf(fp,"v %f %f %f\n",  m_pVertexList[i]._p[0],
                                        m_pVertexList[i]._p[1],
                                        m_pVertexList[i]._p[2]);

        fprintf(fp,"# %d triangles\n",m_nTriangles);
        for(int i=0;i<m_nTriangles;i++)
            fprintf(fp,"f %d %d %d\n",  m_pTriangleList[i][0] + 1,
                                        m_pTriangleList[i][1] + 1,
                                        m_pTriangleList[i][2] + 1);

        fclose(fp);
        
        printf("Writing to %s successfully\n",fn);
        return true;

    }
}


