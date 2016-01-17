//
//  kdtree.cpp
//  RayTracing
//
//  Created by Ming Yao on 16/1/14.
//

#include "kdtree.h"
#include "../util.h"
#include <algorithm>
#include <future>

#ifndef MYDEBUG
/*#define MYDEBUG*/
#endif

namespace RayTracing {

    // #include "lib/debugutils.hh"
    // #include "lib/Timer.hh"
    IntersectInfoPtr KdTree::Node::getIntersect(const Ray& ray) const {
        
        IntersectInfoPtr infoPtr = nullptr;
        if (this->isLeaf()) { // this node is a leaf node
            // find first obj
            real_t minDistance = InfDistance;
            for (const auto & object : *objects) {
                auto tmpInfo = object->getIntersect(ray);
                if (tmpInfo != nullptr) {
                    if (tmpInfo->intersectPos < minDistance) { //update
                        minDistance = tmpInfo->intersectPos;
                        infoPtr = move(tmpInfo);
                    }
                }
            }
            return infoPtr;
        }

        // test this one
//         Node * curNear = ray.getSource()[plane.axis] < plane.position ? leftChild : rightChild;
//         Node * curFar = curNear == leftChild ? rightChild : leftChild;
//         real_t dist = this->plane.getDistance(ray);
//         if ((dist > max +Epsilon*2 || dist < -Epsilon*2) && curNear!=nullptr) {
//             return curNear->getIntersect(ray, min, max);
//         }
//         else if (dist < min -Epsilon*2 && curFar != nullptr)
//         {
//             return curFar->getIntersect(ray, min, max);
//         }
//         else {
//             if (curNear != nullptr) {
//                 infoPtr = curNear->getIntersect(ray, min, dist+Epsilon);
//                 if (infoPtr != nullptr) return infoPtr;
//             }
//             if (curFar != nullptr)
//                 return curFar->getIntersect(ray, dist-Epsilon, max);
//             return nullptr;
//         }
        // this node is a non-leaf node
        // we only needs to find the nearest intersecting object
        // when find an intersecting object, return the intersect info

        Node * cur;
            real_t intersectPos;
            this->box.intersect(intersectPos, ray);
            if (ray.getPoint(intersectPos)[plane.axis] < plane.position) {
                // at the left side of the plane
                cur = leftChild;
            }
            else cur = rightChild; // near side
            real_t temp;
            if (cur != nullptr && cur->box.intersect(temp,ray) != MISSED) {
                infoPtr = cur->getIntersect(ray);
                if (infoPtr!=nullptr){
                    if (!cur->isLeaf()){
                        return infoPtr;
                    }
                    Vec3d intersectPoint = infoPtr->getIntersectPoint();
                    if (cur->box.hasPoint(intersectPoint))
                        return infoPtr;
                }
            }
    
            cur = cur == leftChild ? rightChild : leftChild;
            if (cur != nullptr && cur->box.intersect(temp, ray) != MISSED) {
                infoPtr = cur->getIntersect(ray);
                if (infoPtr != nullptr) {
                    if (!cur->isLeaf()) {
                        return infoPtr;
                    }
                    Vec3d intersectPoint = infoPtr->getIntersectPoint();
                    if (cur->box.hasPoint(intersectPoint))
                        return infoPtr;
                }
            }
            return nullptr;
         
        }

    KdTree::KdTree(const list<RenderablePtr>& _objects, unsigned d, unsigned m) {
        maxDepth = d;
        maxSize = m;
        list<RenderableNode*> objectList;
        for (auto & obj : _objects) {
            BBox box = obj->getBBox();
            objectList.emplace_back(new RenderableNode(obj, box));
            boundBox.unite(box);
        }
        Clock c = Clock();
        root = build(objectList, boundBox, 0);
        for (auto objptr : objectList)
            delete objptr;
        printf("Build tree spends %f seconds\n", c.getTime());
    }

    KdTree::~KdTree() { 
        delete root; 
    }

    IntersectInfoPtr KdTree::getIntersect(const Ray& ray) const {
        if (!root) return nullptr;		// empty kd-tree
        real_t pos;
        if ((root->box.intersect(pos,ray)) == MISSED)
            return nullptr;
        return root->getIntersect(ray);
    }

    BBox KdTree::getBBox() const {
        return this->boundBox;
    }

    SuperPlane KdTree::cut(const list<RenderableNode*>& objs, int depth) const {
        SuperPlane result(depth % 3, 0);
        vector<real_t> sorter;
        for (auto objptr : objs)
            sorter.push_back(objptr->box.minVec[result.axis]);

        nth_element(sorter.begin(), sorter.begin() + sorter.size() / 2, sorter.end());
        result.position = sorter[sorter.size() / 2] + Epsilon;
        return result;
    }

    KdTree::Node* KdTree::build(const list<RenderableNode*>& objs, const BBox& box, int depth) {
        cout << box << endl;
        if (enableSAH)
        {
            return SAHBuild(objs, box, depth);
        }
        return simpleBuild(objs, box, depth);
        
    }


    KdTree::Node* KdTree::simpleBuild(const list<RenderableNode*>& objs, const BBox& box, int depth) {

        if (objs.size() == 0 || depth > maxDepth) return nullptr;

        Node* newNode = new Node(box);

        int nobj = objs.size();
        if (nobj <= maxSize) {
            for (const auto & objptr : objs) newNode->addObject(objptr->object);
#ifdef MYDEBUG
            cout << "Nodesize:" << objs.size() << endl;
#endif
            return newNode;
        }
        SuperPlane best_pl;
        //real_t minCost = DBL_MAX;
        BBox boxa, boxb;

        best_pl = cut(objs, depth);

        if(!(box.split(boxa,boxb,best_pl))){

            for (auto objptr : objs) newNode->addObject(objptr->object);
#ifdef MYDEBUG
            cout << "Nodesize:" << objs.size() << endl;
#endif
            return newNode;		// pl is outside box, cannot go further
        }
        newNode->plane = best_pl;

        list<RenderableNode*> objl, objr;
        for (auto obj : objs) {
            if (obj->box.maxVec[best_pl.axis] >= best_pl.position - 2 * Epsilon)
                objr.push_back(obj);
            if (obj->box.minVec[best_pl.axis] <= best_pl.position + 2 * Epsilon)
                objl.push_back(obj);
        }

        newNode->leftChild = simpleBuild(objl, boxa, depth + 1);
        newNode->rightChild = simpleBuild(objr, boxb, depth + 1);
        // might fail to build children
        if (newNode->isLeaf()) {		// add obj to isLeaf node
            for (auto objptr : objs) newNode->addObject(objptr->object);
#ifdef MYDEBUG
            cout << "Nodesize:" << objs.size() << endl;
#endif
        }
        return newNode;
        
    }
    KdTree::Node* KdTree::SAHBuild(const list<RenderableNode*>& objs, const BBox& box, int depth) {

        if (objs.size() == 0 || depth > maxDepth) return nullptr;

        Node* newNode = new Node(box);

        int nobj = objs.size();
        if (nobj <= maxSize) {
            for (auto objptr : objs) newNode->addObject(objptr->object);
#ifdef MYDEBUG
            cout << "Nodesize:" << objs.size() << endl;
#endif
            return newNode;
        }
        SuperPlane best_pl;
        real_t minCost = DBL_MAX;
        // algorithm 2 (SAH kdtree)
        // "On building fast kd-trees for ray tracing, and on doing that in O (N log N)"
        // Wald, Ingo and Havran, Vlastimil
        // O(n log^2(n)) build

        typedef pair<real_t, bool> PDB;
        auto gen_cand_list = [&objs](int dim) {
            vector<PDB> cand_list;
            for (auto objptr : objs)
                cand_list.emplace_back(objptr->box.minVec[dim] - 2*Epsilon, true),
                cand_list.emplace_back(objptr->box.maxVec[dim] + 2*Epsilon, false);
            sort(cand_list.begin(), cand_list.end());
            return cand_list;
        };

        future<vector<PDB>> task[3];
        const int THREAD_DEPTH_THRES = 1;
        bool parallel = depth < THREAD_DEPTH_THRES;
        if (parallel)
            for (int dim = 0; dim < 3; ++dim)
                task[dim] = async(launch::async, bind(gen_cand_list, dim));

        for (int dim = 0; dim < 3; ++dim) {
            // true: min, false: max
            vector<PDB> cand_list =
                parallel ? task[dim].get() : gen_cand_list(dim);

            int lcnt = 0, rcnt = nobj;
            auto ptr = cand_list.begin();

            do {
                SuperPlane pl(dim, ptr->first);
                try {
                    BBox a, b;
                    box.split(a, b, pl);
                    real_t cost = a.surfaceArea() * lcnt + b.surfaceArea() * rcnt;
                    if (lcnt == 0 || rcnt == 0 || (lcnt + rcnt == nobj - 1 && rcnt == 1))
                        cost *= 0.8;		// this is a hack
                    if (cost < minCost) {
                        minCost = cost;
                        best_pl = pl;
                    }
                }
                catch (...) {}

                if (ptr->second) lcnt++; else rcnt--;

                auto old = ptr++;
                while (ptr != cand_list.end() && ptr->first - old->first < Epsilon) {
                    if (ptr->second) lcnt++;
                    else rcnt--;
                    old = ptr++;
                }
            } while (ptr != cand_list.end());
        }

        if (best_pl.axis == SuperPlane::ERROR) { // didn't find best_pl
            for (auto objptr : objs) newNode->addObject(objptr->object);
#ifdef MYDEBUG
            cout << "Nodesize:" << objs.size() << endl;
#endif
            return newNode;
            
        }

        BBox boxa, boxb;
        // fount the best cutting plane
        newNode->plane = best_pl;
        box.split(boxa, boxb, best_pl);
        list<RenderableNode*> objl, objr;
        for (auto obj : objs) {
            if (obj->box.maxVec[best_pl.axis] >= best_pl.position) objr.push_back(obj);
            if (obj->box.minVec[best_pl.axis] <= best_pl.position) objl.push_back(obj);
        }
        // end of algorithm 2
        
        newNode->leftChild = SAHBuild(objl, boxa, depth + 1);
        newNode->rightChild = SAHBuild(objr, boxb, depth + 1);
        // might fail to build children
        if (newNode->isLeaf()) {	// add obj to isLeaf node
            for (auto objptr : objs) newNode->addObject(objptr->object);
#ifdef MYDEBUG
            cout << "Nodesize:" << objs.size() << endl;
#endif
        }
        return newNode;
    }
}
