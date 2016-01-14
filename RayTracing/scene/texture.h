//
//  Material.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include "../color.h"
#include "Material.h"
#include <memory>
#include <iostream>

namespace RayTracing{
    using std::make_shared;
    typedef std::shared_ptr<Material> MaterialPtr;
    /* Base Class of Texture*/
    class TextureBase{
    public:
        virtual MaterialPtr getMaterial() const = 0;
        virtual MaterialPtr getMaterial(real_t x, real_t y) const{
            return nullptr;
        }
        virtual ~TextureBase(){}
    };

    class MonoTexture :public TextureBase {
	private:
		const Material& material;
	public:
		MonoTexture(const Material& m) : material(m){}

		MaterialPtr getMaterial(real_t, real_t) const override {
			return make_shared<Material>(material);
		}

		MaterialPtr getMaterial() const override{
            return make_shared<Material>(material);
        }
    };

}

#endif // !TEXTURE_H
