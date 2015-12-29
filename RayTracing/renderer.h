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
#include "myMath.h"
#include "color.h"
#include "camera/camera.h"

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

};

#endif // !RENDERER_H
