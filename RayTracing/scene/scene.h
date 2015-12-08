//
//  scene.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//  Copyright © 2015年 Ming Yao. All rights reserved.
//

#ifndef scene_h
#define scene_h

#include <list>
#include "SimpleObject.h"
#include "color.h"
#include "Material.h"

namespace RayTracing{
	class Object : public CSimpleObject{
	public:
		Material* material;
	};
    class Scene{
    private:
        // Type definition
        typedef std::list<Object> ObjectList;
        
        // data field
        ObjectList objects;
    public:
        unsigned long objnum(){
            return objects.size();
        }
    };
}

#endif /* scene_h */
