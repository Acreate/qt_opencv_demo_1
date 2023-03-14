#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"
#include "Colorhistogram.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	ColorHistogram hc;
	cv::Mat color, imageRoi, shist, color2, result1, result2;
	ContentFinder finder;
	cvFunction::readImage("waves.jpg", color);
	cvFunction::showMatImg(color, "waves.jpg 图像");
	cv::Rect roiRect(0, 0, 100, 45);
	imageRoi = color(roiRect);
	cvFunction::showMatImg(imageRoi, "截取区域图像");
	finder.setThreshold(0.05f);
	int ch[2] = {0, 2};
	// 使用 色调 去匹配
	// 最大 180 像素值
	hc.setSize(180);
	shist = hc.getHueHistogram(imageRoi);
	finder.setHistogram(shist);
	cv::Mat hsv;
	cv::cvtColor(color, hsv, cv::COLOR_BGR2HSV);
	result1 = finder.find(hsv, 0.0f, 180.0f, ch);
	cvFunction::showMatImg(result1, "被截取区域在 waves.jpg(HSV 格式) 图像位置描述(0 通道)");
	cvFunction::readImage("dog.jpg", color2);
	cv::cvtColor(color2, hsv, cv::COLOR_BGR2HSV);
	result2 = finder.find(hsv, 0.0f, 180.0f, ch);
	cvFunction::showMatImg(result2, "被截取区域在 dog.jpg(HSV 格式) 图像位置描述(0 通道)");

	int exec = a.exec();
	return exec;
}