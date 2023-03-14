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
	ContentFinder finder;
	cv::Mat color, color2, imageRoi, shist, lab, result1, result2;

	cvFunction::readImage("waves.jpg", color);
	cv::Rect roiRect(0, 0, 100, 45);
	imageRoi = color(roiRect);

	//cvFunction::showMatImg(color, "waves.jpg 图像");
	//cvFunction::showMatImg(imageRoi, "截取区域图像");

	hc.setSize(256);
	shist = hc.getHistogram(imageRoi);
	finder.setHistogram(shist);
	finder.setThreshold(0.05f);

	cv::cvtColor(color, lab, cv::COLOR_BGR2Lab);
	int ch[2] = {1, 2};
	result1 = finder.find(lab, 0, 256.0f, ch);
	cvFunction::showMatImg(imageRoi, "被截取区域在 waves.jpg (lab 格式) 图像查找返回");

	cvFunction::readImage("dog.jpg", color2);
	//cvFunction::showMatImg(color2, "dog.jpg 图像");
	cv::cvtColor(color2, lab, cv::COLOR_BGR2Lab);
	result2 = finder.find(lab, 0, 256.0, ch);
	cv::rectangle(color, roiRect, cv::Scalar(0, 0, 0));

	cvFunction::showMatImg(imageRoi, "被截取区域在 dog.jpg (lab 格式) 图像查找返回");
	cvFunction::showMatImg(color, "被截取区域在 waves.jpg 图像位置描述");

	int exec = a.exec();
	return exec;
}