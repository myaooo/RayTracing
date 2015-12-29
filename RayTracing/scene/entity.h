//
//  entity.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

class Entity{

public:
    
public:
    virtual ~Entity(){};

    Entity(){}

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
}
