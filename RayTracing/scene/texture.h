//
//  Material.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include "../ray/color.h"
#include "Material.h"
#include <memory>
#include <iostream>

typedef std::shared_ptr shared_ptr;
namespace RayTracing{
    /* Base Class of Texture*/
    class TextureBase{
        virtual shared_ptr<Material> getMaterial() const = 0;
        virtual shared_ptr<Material> getMaterial(real_t x, real_t y) const{
            return nullptr;
        }
        virtual ~TextureBase(){}
    };

    class MonoTexture :public TextureBase {
	private:
		const Material& materialPtr;
	public:
		MonoTexture(const Material& m_ptr) : materialPtr(m_ptr){}

		shared_ptr<Material> getMaterial(real_t, real_t) const override {
			return make_shared<Material>(materialPtr);
		}

		shared_ptr<Material> getMaterial() const override{
            return make_shared<Material>(materialPtr);
        }
    };

}

#endif // !TEXTURE_H
