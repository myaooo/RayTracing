//
//  raytracer.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef raytracer_h
#define raytracer_h

#include "geometry.h"
#include "color.h"
#include "camera/camera.h"
#include <cassert>
#include <cmath>

namespace RayTracing{
    #define DEFAULT_TRACE_DEPTH 15
    #define DISSIPATION 0.03
    #define getDissipator(dist) (exp(-(dist)*DISSIPATION))
    typedef std::shared_ptr<Scene> ScenePtr;
    class RayTracer{
    public:
        // data fields
        Camera cam;
        ScenePtr scenePtr;
        int maxTraceDepth;
        Color BGColor;
        //bool enableTree;
    public:
        RayTracer(){}
        RayTracer(const Camera & c,  const ScenePtr & s = NULL,
            int depth = DEFAULT_TRACE_DEPTH, const Color & back = Color::BLACK) :
            cam(c), scenePtr(s), maxTraceDepth(depth), BGColor(back){}
        void setCamera(const Camera & c){
            cam = c;
        }
        void setScene(const ScenePtr & s){
            scenePtr = s;
            scenePtr->config();
        }
        void setMaxTraceDepth(int depth){
            assert(depth > 1);
            int maxTraceDepth = depth;
        }
        // find the mindistance intersection and return Intersection Info pointer
        IntersectInfoPtr getIntersectInfo(const Ray & ray, bool includeLight = false) const;

        // the entrance of trace function
        virtual Color doTrace(const Ray & ray) const;

        virtual Color doTrace(real_t x, real_t y) const;

    protected:
        virtual Color traceRay(const Ray & ray, int depth) const;

        Color getLocalPhong(const IntersectInfoPtr & infoPtr) const;

    };



}

#endif /* raytracer_h */
