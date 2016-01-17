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

    class GridTexture : public TextureBase {
    private:
        int size;
        const Material &pty1, &pty2;
    public:
        GridTexture(const Material& m_pty1, const Material& m_pty2, int _size) :
            size(_size), pty1(m_pty1), pty2(m_pty2) {}

        MaterialPtr getMaterial(real_t x, real_t y) const override {
            bool a1 = (((int)x / size) & 1) == 0;
            if (x < 0) a1 = !a1;
            bool a2 = (((int)y / size) & 1) == 0;
            if (y < 0) a2 = !a2;
            if (a1 ^ a2) return make_shared<Material>(pty1);
            else return make_shared<Material>(pty2);
        }

        MaterialPtr getMaterial() const override {
            return nullptr;
        }

        static const GridTexture BLACK_WHITE_MIRROR, BLACK_WHITE;
    };
}

#endif // !TEXTURE_H
