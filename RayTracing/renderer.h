//
//  renderer.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <opencv2/opencv.hpp>
#include "geometry.h"
#include "color.h"
#include "scene/scene.h"
#include "raytracer.h"
#include "camera/camera.h"

namespace RayTracing{
    using std::string;
    class Renderer{
    private:
        int width;
        int height;
        int centerX;
        int centerY;
        mutable MyMath::Matrix<Color> imageBuffer;
        Camera camera;
        RayTracer tracer;
        Scene scene;
    public:
        Renderer(){}
        Renderer(int w, int h, const Camera & cam);
        Renderer(int w, int h);
        ~Renderer();
        void saveImage(string filepath);
        Vec3d getPixel(int x, int y) const;
        static Vec3d getPixel(const cv::Mat & im, int x, int y);
        real_t renderAll();
        void addLight(const Light & light);
        void addObject(const RenderablePtr & renderable);

    protected:
        void init();
        void write(const Color & c, int x, int y);

    }; // end of class renderer
}

#endif // !RENDERER_H
