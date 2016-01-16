//
//  scene.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef scene_h
#define scene_h

#include <list>
#include "SimpleObject.h"
#include "../color.h"
#include "renderable.h"
#include "rplane.h"
#include "light.h"

namespace RayTracing{
	#define ENVIRONMENT_FACTOR 0.005
    class Scene{
    private:
        // Type definition
        typedef std::list<RenderablePtr> ObjectList;
        typedef std::list<LightPtr> LightList;
        // data field
        ObjectList objects;
        LightList lights;
    public:
        // public variables
        bool enableTree = false;
        bool configed = false;
        Color ambient = Color::BLACK;
        // de-constructor
        ~Scene(){
            objects.clear();
            lights.clear();
        }

        unsigned long objnum() const{
            return objects.size();
        }

        unsigned long lightnum() const{
            return lights.size();
        }

        void addLight( const Light & light);

        void addObject( const RenderablePtr & renderablePtr);

        IntersectInfoPtr getObjectIntersect(const Ray & ray) const;

        IntersectInfoPtr getLightIntersect(const Ray & ray) const;

        bool hasObjectIntersect(const Ray & ray) const;
        bool hasLightIntersect(const Ray & ray) const

        bool buildTree();

        void config();
    };
}

#endif /* scene_h */
