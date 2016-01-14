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
        cv::Mat image;
        Camera cam;
    public:
        Renderer(){}
        Renderer(int w, int h);
        void saveImage(string filepath);
        Vec3d getPixel(int x, int y) const;
        static Vec3d getPixel(const cv::Mat & im, int x, int y);

    }; // end of class renderer
}

#endif // !RENDERER_H
