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


namespace RayTracing{
    class Scene{
    private:
        // Type definition
        typedef CSimpleObject Object;
        typedef std::list<Object> ObjVec;
        
        // data field
        ObjVec objvec;
    public:
        unsigned long objnum(){
            return objvec.size();
        }
    };
}

#endif /* scene_h */
