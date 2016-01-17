//
//  kdtree.h
//  RayTracing
//
//  Created by Ming Yao on 16/1/14.
//

#ifndef KDTREE_H
#define KDTREE_H

#include "renderable.h"
#include "../geometry.h"
#include <list>

namespace RayTracing {
#define DEFAULT_TREE_DEPTH 100
#define DEFAULT_NODE_SIZE 10
    using namespace std;
    class KdTree;
    typedef shared_ptr<KdTree> KdTreePtr;
    class KdTree : public Renderable {
    public:
        // inner struct Node
        struct Node {
        public:
            // data fields
            BBox box;
            Node* leftChild;
            Node* rightChild;
            SuperPlane plane;
            list<RenderablePtr>* objects; // for leaf node

        public:
            // constructor
            Node(const BBox& _box, Node* lc = nullptr, Node* rc = nullptr) :
                box(_box), leftChild(lc), rightChild(rc), objects(nullptr), plane() {}
            // destructor
            ~Node() {
                delete leftChild;
                delete rightChild;
                if (isLeaf()) objects->~list<RenderablePtr>();
            }
            bool isLeaf() const {
                return leftChild == nullptr && rightChild == nullptr;
            }

            void addObject(const RenderablePtr& obj) {
                if (objects == nullptr)
                    objects = new list<RenderablePtr>();
                objects->push_back(obj);
            }

            IntersectInfoPtr getIntersect(const Ray& ray) const;

        };

        // inner struct RenderableNode
        struct RenderableNode {
        public:
            RenderablePtr object;
            BBox box;
            RenderableNode(const RenderablePtr& _obj, const BBox& _box) :
                object(_obj), box(_box) {}
        };

    public:
        // data fields
        // root node
        Node* root;
        BBox boundBox;
        unsigned maxDepth;
        unsigned maxSize;
        bool enableSAH = true;
        //Vec3d bound_min = Vec3d::maxVec, bound_max = -Vec3d::maxVec;

    public:
        // constructor
        KdTree(const list<RenderablePtr>& objs, unsigned d = DEFAULT_TREE_DEPTH, 
            unsigned m = DEFAULT_NODE_SIZE);
        // destructor
        ~KdTree();
        // override getIntersect function
        IntersectInfoPtr getIntersect(const Ray& ray) const override;
        // override get BBox function
        BBox getBBox() const override;
    protected:
        // protected methods:
        Node* build(const list<RenderableNode*>& objs, const BBox& box, int depth);
        Node* simpleBuild(const list<RenderableNode*>& objs, const BBox& box, int depth);
        Node* SAHBuild(const list<RenderableNode*>& objs, const BBox& box, int depth);
        SuperPlane cut(const list<RenderableNode*>& objs, int depth) const;

    };

}

#endif // !KDTREE_H