//
//  meshparser.cpp
//  RayTracing
//
//  Created by Ming Yao on 16/1/14.
//

#include "MeshParser.h"
#include <vector>
#include "scene/meshObject.h"

using namespace std;

namespace RayTracing {

    bool MeshParser::LoadFromObj(Mesh & mesh, const char* fn) const {
        FILE* fp = fopen(fn, "r");
        if (fp == NULL) {
            printf("Error: Loading %s failed.\n", fn);
            return false;
        }
        else {
            if (Parse(mesh, fp)) {
                printf("Loading from %s successfully.\n", fn);
                printf("Vertex Number = %d\n", mesh.vertices.size());
                printf("Triangle Number = %d\n", mesh.faceIdx.size());
                fclose(fp);
                return true;
            }
            else {
                fclose(fp);
                return false;
            }
        }
    }

    bool MeshParser::Parse(Mesh & mesh, FILE* fp) const{

        char buf[256];
        int nVertices, nTriangles;

        nVertices = 0;
        nTriangles = 0;
        mesh.vertices.clear();
        mesh.faceIdx.clear();
        int lineNumber = 0;

        while (fscanf(fp, "%s", buf) != EOF) {
            lineNumber++;
            switch (buf[0]) {
                case '#':				/* comment */
                    /* eat up rest of line */
                    fgets(buf, sizeof(buf), fp);
                    break;
                case 'v':				/* v, vn, vt */
                    switch (buf[1]) {
                        case '\0':			    /* vertex */
                        {
                            Vec3d vP;
                            if (fscanf(fp, "%f %f %f",
                                &vP._p[0],
                                &vP._p[1],
                                &vP._p[2]) == 3) {
                                nVertices++;
                                mesh.vertices.push_back(vP);
                            }
                            else {
                                printf("Error: Wrong Number of Values(Should be 3). at Line %d\n", lineNumber);
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
                    int v, n, t;
                    TriangleIdx vIndices;
                    if (fscanf(fp, "%s", buf) != 1) {
                        printf("Error: Wrong Face at Line %d\n", lineNumber);
                        return false;
                    }

                    /* can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d */
                    if (strstr(buf, "//")) {
                        /* v//n */
                        if (sscanf(buf, "%d//%d", &vIndices[0], &n) == 2 &&
                            fscanf(fp, "%d//%d", &vIndices[1], &n) == 2 &&
                            fscanf(fp, "%d//%d", &vIndices[2], &n) == 2) {
                            nTriangles++;
                            mesh.faceIdx.push_back(vIndices);
                        }
                        else {
                            printf("Error: Wrong Face at Line %d\n", lineNumber);
                            return false;
                        }

                    }
                    else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3) {
                        /* v/t/n */
                        vIndices[0] = v;
                        if (fscanf(fp, "%d/%d/%d", &vIndices[1], &t, &n) == 3 &&
                            fscanf(fp, "%d/%d/%d", &vIndices[2], &t, &n) == 3) {
                            nTriangles++;
                            mesh.faceIdx.push_back(vIndices);
                        }
                        else {
                            printf("Error: Wrong Face at Line %d\n", lineNumber);
                            return false;
                        }
                    }
                    else if (sscanf(buf, "%d/%d", &v, &t) == 2) {
                        /* v/t */
                        vIndices[0] = v;
                        if (fscanf(fp, "%d/%d", &vIndices[1], &t) == 2 &&
                            fscanf(fp, "%d/%d", &vIndices[2], &t) == 2) {
                            nTriangles++;
                            mesh.faceIdx.push_back(vIndices);
                        }
                        else {
                            printf("Error: Wrong Face at Line %d\n", lineNumber);
                            return false;
                        }
                    }
                    else {
                        /* v */
                        if (sscanf(buf, "%d", &vIndices[0]) == 1 &&
                            fscanf(fp, "%d", &vIndices[1]) == 1 &&
                            fscanf(fp, "%d", &vIndices[2]) == 1) {
                            nTriangles++;
                            mesh.faceIdx.push_back(vIndices);
                        }
                        else {
                            printf("Error: Wrong Face at Line %d\n", lineNumber);
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
        return true;
    }

    bool MeshParser::CheckParse(int nVertices, const Mesh & mesh) const{
        for (int i = 0; i < mesh.faceIdx.size(); i++) {
            const TriangleIdx & vIndices = mesh.faceIdx[i];
            for (int j = 0; j < vIndices.size(); j++)
                if (vIndices[j] <= 0 || vIndices[j] > nVertices) {
                    printf("Error: The vertex index of Face %d has exceeded vertex number %d\n", i, nVertices);
                    return false;
                }
        }

        return true;
    }

    bool MeshParser::SaveToObj(const Mesh & mesh, const char* fn) const{
        if (mesh.vertices.empty()) {
            printf("Error: Object is not initialized. %s\n", fn);
            return false;
        }

        FILE* fp = fopen(fn, "w");
        if (fp == NULL) {
            printf("Error: Failed opening %s to write\n", fn);
            return false;
        }

        fprintf(fp, "# %d vertices\n", mesh.vertices.size());
        for (int i = 0; i < mesh.vertices.size(); i++)
            fprintf(fp, "v %f %f %f\n", mesh.vertices[i]._p[0],
            mesh.vertices[i]._p[1],
            mesh.vertices[i]._p[2]);

        fprintf(fp, "# %d triangles\n", mesh.faceIdx.size());
        for (int i = 0; i < mesh.faceIdx.size(); i++)
            fprintf(fp, "f %d %d %d\n", mesh.faceIdx[i][0] + 1,
            mesh.faceIdx[i][1] + 1,
            mesh.faceIdx[i][2] + 1);

        fclose(fp);

        printf("Writing to %s successfully\n", fn);
        return true;

    }
}


