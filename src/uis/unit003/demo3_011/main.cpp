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
	cv::Mat color, imageRoi;
	cvFunction::readImage("waves.jpg", color);
	cvFunction::showMatImg(color, "waves.jpg 图像");
	cv::Rect roiRect(0, 0, 100, 45);
	imageRoi = color(roiRect);
	cvFunction::showMatImg(imageRoi, "截取区域图像");
	// 最大元素为 8
	hc.setSize(8);
	cv::Mat shist = hc.getHistogram(imageRoi);
	ContentFinder finder;
	finder.setHistogram(shist);
	finder.setThreshold(0.05f);
	cv::Mat result1 = finder.find(color);
	cvFunction::showMatImg(result1, "在 waves.jpg 中查找的图像 0.05f(5%) 返回");
	
	// 加载第二个查找的图片源
	cv::Mat color2;
	cvFunction::readImage("dog.jpg", color2);
	cvFunction::showMatImg(color2, "dog.jpg 图像");
	cv::Mat result2 = finder.find(color2);
	cvFunction::showMatImg(result2, "在 dog.jpg 中查找的图像 0.05f(5%) 返回");
	// 最大像素为 256
	hc.setSize(256);
	cv::Mat tmp;
	shist.convertTo(tmp,CV_8U, -1.0, 255.0);
	cvFunction::showMatImg(tmp, "查找对象的直方数据显示");
	cv::rectangle(color, roiRect, cv::Scalar(0, 0, 255));
	cvFunction::showMatImg(color, "描述被截取的图像");
	int exec = a.exec();
	return exec;
}