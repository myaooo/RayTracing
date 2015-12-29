//
//  renderer.cpp
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#include <opencv2/opencv.hpp>
#include "renderer.h"
#include "util.h"

using namespace cv;

Renderer::Renderer(int w, int h) : width(w), height(h) : image(w,h,CV_8UC3,Scalar(0,0,0)){}

void Renderer::saveImage(string filepath){

}

Vec3d Renderer::getPixel(int x, int y) const{
    Vec3d pixel;
    uchar * yptr = image.ptr(y);
    pixel.r = yptr[3*x+2]/COLORRANGE;
    pixel.g = yptr[3*x+1]/COLORRANGE;
    pixel.b = yptr[3*x]/COLORRANGE;
    return pixel;
}

static Vec3d getPixel(const cv::Mat & im, int x, int y){
    Vec3d pixel;
    uchar * yptr = im.ptr(y);
    pixel.r = yptr[3*x+2]/COLORRANGE;
    pixel.g = yptr[3*x+1]/COLORRANGE;
    pixel.b = yptr[3*x]/COLORRANGE;
    return pixel;
}
