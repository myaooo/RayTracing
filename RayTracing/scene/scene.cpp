//
//  scene.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#include <stdio.h>
#include "scene.h"
#include "../util.h"
#include <list>
#include <memory>
#include <iostream>

using std::make_shared;
namespace RayTracing{
    void Scene::addLight( const LightPtr & lightPtr){
        configed = false;
        lights.push_back(lightPtr);
    }

    void Scene::addObject( const RenderablePtr & renderablePtr){
        configed = false;
        objects.push_back(renderablePtr);
    }

    IntersectInfoPtr Scene::getObjectIntersect(const Ray & ray) const{
        if (enableTree == false) { // not using kd tree, travel one by one
            IntersectInfoPtr infoPtr = nullptr;
            real_t minDistance = InfDistance;
            for (const auto & object : objects) {
                IntersectInfoPtr infoPtrTemp = object->getIntersect(ray);
                if (infoPtrTemp == nullptr) { // missed
                    continue;
                }
                if (infoPtrTemp->intersectPos < minDistance) { // update minDistance
                    minDistance = infoPtrTemp->intersectPos;
                    infoPtr = move(infoPtrTemp);
                }
            }
            return infoPtr;
        }
        else{ // using kd tree
            /* code to be filled */
            return nullptr;
        }
    }

    IntersectInfoPtr Scene::getLightIntersect(const Ray & ray) const{
        IntersectInfoPtr infoPtr = nullptr;
        real_t minDistance = InfDistance;
        for (const auto & light : lights) {
            IntersectInfoPtr infoPtrTemp = light->getIntersect(ray);
            if (infoPtrTemp == nullptr) { // missed
                continue;
            }
            if (infoPtrTemp->intersectPos < minDistance) {
                minDistance = infoPtrTemp->intersectPos;
                infoPtr = move(infoPtrTemp);
            }
        }
        return infoPtr;
    }

    bool Scene::hasObjectIntersect(const Ray & ray) const{
        for (const auto & object : objects) {
            auto temp = object->getIntersect(ray);
            if (temp != nullptr) return true;
        }
        return false;
    }

    bool Scene::hasLightIntersect(const Ray & ray) const{
        for (const auto & light : lights) {
            auto temp = light->getIntersect(ray);
            if (temp != nullptr) return true;
        }
        return false;
    }

    bool Scene::buildTree(){
        return true;
    }

    void Scene::config(){
        if (configed) return;
        if (lights.size() < 1){
            std::cerr<<"no lights!"<<std::endl;
        }
        for (auto light : lights)
            ambient += light->color * light->getIntensity();
        ambient *= ENVIRONMENT_FACTOR;
        configed = true;
    }
}
