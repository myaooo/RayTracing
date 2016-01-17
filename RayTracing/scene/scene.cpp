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
        // travel one by one
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
        if (hasTree || !enableTree) return false;
        // build tree
        hasTree = true;
        list<RenderablePtr> infinite_obj;
        for (auto itr = objects.begin(); itr != objects.end();) {
            if ((*itr)->isinfinite()) {
                infinite_obj.push_back(*itr);
                objects.erase(itr++);
            }
            else
                ++itr;
        }

        auto finite_tree = shared_ptr<KdTree>(new KdTree(objects));
        objects = move(infinite_obj);
        if (finite_tree && finite_tree->root != nullptr) objects.emplace_back(finite_tree);
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
        buildTree();
        configed = true;
    }
}
