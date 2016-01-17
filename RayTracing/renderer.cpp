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
    using namespace cv;
    typedef MyMath::Vec3d Vec3d;

    Renderer::Renderer(int w, int h, const Camera & c) : 
        width(w), height(h), camera(c) {
        init();
    }

    Renderer::Renderer(int w, int h) : width(w), height(h), camera({-100, 0, 0}) {
        init();
    }

    Renderer::~Renderer() {
        tracer.~RayTracer();
        scene->~Scene();
    }

    void Renderer::saveImage(string filename) const{
        imwrite(filename, imageBuffer);
    }

    void Renderer::init() { 
        if (scene ==nullptr)
        {
            scene = shared_ptr<Scene>(new Scene());
        }
        tracer = RayTracer(camera, scene);
        imageBuffer = Mat(width, height, CV_8UC3, Scalar(0, 0, 0));
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

    void Renderer::addLight(const LightPtr & light) {
        this->scene->addLight(light);
    }
    void Renderer::addObject(const RenderablePtr & renderable) {
        this->scene->addObject(renderable);
    }

    real_t Renderer::renderAll() {
        Clock c = Clock();
        cout << " start rendering...\n";
        int percent = 0;
        for (int i = 0; i < width; i++)
        {
            if (percent *width < (double)(i) * 20) {
                percent++;
                cout <<"rendering..."<< percent * 5 << "%" << endl;
            }
            for (int j = 0; j < height;j++)
            {
                Color c = tracer.doTrace((double)(i - centerX) / centerX, (double)(j - centerY) / centerY);
                write(c, i, j);
            }
        }
        return c.getTime();
    }

    void Renderer::showImage() const {
        imshow("renderer", imageBuffer);
        waitKey(0);
    }

    void Renderer::write(const Color & c, int x, int y) const{
        imageBuffer.ptr<uchar>(y)[x * 3] = c.b * 255;
        imageBuffer.ptr<uchar>(y)[x * 3 + 1] = c.g * 255;
        imageBuffer.ptr<uchar>(y)[x * 3 + 2] = c.r * 255;
    }

//     void Renderer::buildTree(bool tree) {
//         this->scene->enableTree = tree;
//         this->scene->buildTree();
//     }

}// end of namespace RayTracing
