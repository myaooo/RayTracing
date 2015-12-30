//
//  renderable.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#ifndef RENDERABLE_H
#define RENDERABLE_H
#include "texture.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;

namespace RayTracing{

    class Renderable {
	private:
		shared_ptr<Texture> texture = nullptr;

	public:
		virtual ~Renderable(){};

		Renderable(){ }

		Renderable(const shared_ptr<Texture>& _texture):
			texture(_texture) { }

		virtual bool infinity() const
		{ return false; }

		virtual bool have_inside() const
		{ return true; }

		void set_texture(const shared_ptr<Texture>& _texture)
		{ texture = _texture; }

		const shared_ptr<Texture>& get_texture() const
		{ return texture; }

		virtual shared_ptr<Trace> get_trace(const Ray& ray, real_t max_dist) const = 0;
		// judge visibility and return ptr if visible

		shared_ptr<Trace> get_trace(const Ray& ray) const
		{ return get_trace(ray, -1); }

		virtual AABB get_aabb() const = 0;
    };
}；

#endif //!RENDERABLE_H
