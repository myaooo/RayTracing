//
//  raytracer.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#include <stdio.h>
#include "raytracer.h"

namespace RayTracing{
    Color RayTracer::doTrace(const Ray & ray) const{
        return traceRay(ray, 0);
    }
    // Phong reflection model
    // https://en.wikipedia.org/wiki/Phong_reflection_model
    Color RayTracer::traceRay(const Ray & ray, int depth = 0) const{
        if (depth > maxTraceDepth)
            return BGColor;
        Color cAmbient, cLocal, cReflect, cRefract;
        IntersectInfoPtr firstIntersect = getIntersectInfo(ray);
        cAmbient = scenePtr->ambient * firstIntersect->materialPtr->ambient;
        // diffuse + specular
        Color cDiffuse = phong_local(intersect_info, ray);

	// // Beer-Lambert's Law
	// ray.dist += intersect_info.inter_dist;
	// now_col = now_col * pow(M_E, -ray.dist * AIR_BEER_DENSITY);
    //
	// m_assert(fabs(ray.dir.sqr() - 1) < EPS);
    //
	// // reflection
	// Color now_refl = reflection(intersect_info, ray, depth);
	// // transmission
	// Color now_transm = transmission(intersect_info, ray, depth);
	// return Phong::blend(now_amb, now_col, now_refl, now_transm);
    }

    IntersectInfoPtr RayTracer::getIntersectInfo(const Ray & ray, bool includeLight) const{
        IntersectInfoPtr infoPtr = scenePtr->getObjectIntersect(ray);
        if (includeLight) {
            IntersectInfoPtr lightInfoPtr = scenePtr->getLightIntersect(ray);
            if (lightInfoPtr != nullptr && lightInfoPtr->intersectPos < infoPtr->intersectPos){
                return lightInfoPtr;
            }
        }
        return infoPtr;
    }

    Color RayTracer::getLocalPhong(const IntersectInfoPtr & infoPtr) const {
        Color localColor;
        for (auto light : lights) {
            Ray ray = light->genRay(infoPtr->getIntersectPoint());
            if (scenePtr->hasObjectIntersect(ray)) {
                continue;
            }
        }
    }
}
