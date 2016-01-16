//
//  renderer.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#include <opencv2/opencv.hpp>
#include "renderer.h"
#include "util.h"

namespace RayTracing {
    //using namespace cv;
    typedef MyMath::Vec3d Vec3d;

    Renderer::Renderer(int w, int h, const Camera & c) : width(w), height(h), camera(c) {
        init();
    }

    Renderer::Renderer(int w, int h) : width(w), height(h), camera({-100, 0, 0}) {
        init();
    }

    Renderer::~Renderer() {
    }

    void Renderer::saveImage(string filename){
        //imwrite(filename, imageBuffer);
    }

    void Renderer::init() {
        tracer = RayTracer(camera, &scene);
        imageBuffer = Matrix<Color>(width, height);
        centerX = width / 2;
        centerY = height / 2;
    }

    Vec3d Renderer::getPixel(int x, int y) const{
        Vec3d pixel;
        const uchar * yptr = imageBuffer.ptr(y);
        pixel.r = yptr[3*x+2]/COLORRANGE;
        pixel.g = yptr[3*x+1]/COLORRANGE;
        pixel.b = yptr[3*x]/COLORRANGE;
        return pixel;
    }

    Vec3d Renderer::getPixel(const cv::Mat & im, int x, int y){
        Vec3d pixel;
        const uchar * yptr = im.ptr(y);
        pixel.r = yptr[3*x+2]/COLORRANGE;
        pixel.g = yptr[3*x+1]/COLORRANGE;
        pixel.b = yptr[3*x]/COLORRANGE;
        return pixel;
    }

    void Renderer::addLight(const Light & light) {
        scene.addLight(std::make_shared<Light>(light));
    }
    void Renderer::addObject(const RenderablePtr & renderable) {
        scene.addObject(renderable);
    }

    real_t Renderer::renderAll() {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height;j++)
            {
                imageBuffer(i, j) = tracer.doTrace((double)(i - centerX) / centerX, (double)(j - centerY) / centerY);
            }
        }
    }

    void normalizeColor() {

    }

    void Renderer::write(const Color & c, int x, int y) {
        imageBuffer.ptr<uchar>(y)[x * 3] = c.b * 255;
        imageBuffer.ptr<uchar>(y)[x * 3 + 1] = c.g * 255;
        imageBuffer.ptr<uchar>(y)[x * 3 + 2] = c.r * 255;
    }

}// end of namespace RayTracing
