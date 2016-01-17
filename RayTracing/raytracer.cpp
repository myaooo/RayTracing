//
//  raytracer.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#include <stdio.h>
#include "raytracer.h"
#include <cmath>

namespace RayTracing{

    Color RayTracer::doTrace(real_t x, real_t y) const {
        Ray ray = cam.genRay(x, y);
        return doTrace(ray);
    }

    Color RayTracer::doTrace(const Ray & ray) const{
        Color c= traceRay(ray, 0);
        c.normalizeColor();
        return c;
    }
    // Phong reflection model
    // https://en.wikipedia.org/wiki/Phong_reflection_model
    Color RayTracer::traceRay(const Ray & ray, int depth = 0) const{
        if (depth > maxTraceDepth)
            return BGColor;
        Color cLocal, cReflect = Color::BLACK, cRefract = Color::BLACK;
        IntersectInfoPtr infoPtr = getIntersectInfo(ray);
        if (infoPtr == nullptr) return BGColor;
        // local phong color : diffuse + specular +ambient
        cLocal = getLocalPhong(infoPtr);
        if (!(infoPtr->intersectType == INSIDE) && infoPtr->isReflectable())
        {
            cReflect = traceRay(infoPtr->getReflectRay(), depth + 1);
            // Phong blending
            Vec3d localDiffuse = (infoPtr->materialPtr->diffuse) * (-Vec3d::dot(infoPtr->norm, infoPtr->inRay.getDirection()));
            Vec3d localSpecular = infoPtr->materialPtr->specular; // dot(r,v) = 1
            cReflect *= (localDiffuse + localSpecular);
        }
        if (infoPtr->isRefractable()) {
            cRefract = traceRay(infoPtr->getRefractRay(), depth + 1);
            cRefract *= infoPtr->materialPtr->refract;
        }

        //blend color
        Color blend = cLocal + cReflect + cRefract;
        blend *= getDissipator(infoPtr->intersectPos);
        return blend;
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

    // get the local Phong color
    Color RayTracer::getLocalPhong(const IntersectInfoPtr & infoPtr) const {
        Color localColor;
        for (auto light : scenePtr->lights) {
            Color temp = Color::BLACK;
            Ray ray = light->genRay(infoPtr->getIntersectPoint());
            ray.offsetSource(2*Epsilon);
            if (scenePtr->hasObjectIntersect(ray)) {
                continue;
            }
            Vec3d lightDirection = ray.getDirection();
            real_t DLocalStrength = Vec3d::dot(lightDirection, infoPtr->norm);
            real_t SLocalStrength = -Vec3d::dot(lightDirection.getMirror(infoPtr->norm),infoPtr->inRay.getDirection());
            // diffuse
            if (0 < DLocalStrength) {
                temp += (infoPtr->materialPtr->diffuse) * (light->getColor()) * (DLocalStrength);
            }
            // specular
            if (0 < SLocalStrength) {
                SLocalStrength = pow(SLocalStrength, infoPtr->materialPtr->shininess);
                temp += (infoPtr->materialPtr->specular) * (light->getColor()) * (SLocalStrength);
            }
            real_t dissipator = getDissipator(ray.range);
            temp *= dissipator * light->getIntensity();
            localColor += temp;
        }
        // ambient
        localColor += scenePtr->ambient * infoPtr->materialPtr->ambient;
        return localColor;
    }
} // end of namespace RayTracing
