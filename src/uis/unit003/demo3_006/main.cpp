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
	cv::Mat color;
	cvFunction::readImage("waves.jpg", color);
	cv::Rect roiRect(0, 0, 100, 45);
	cv::Mat imageRoi = color(roiRect);
	hc.setSize(8);
	cv::Mat shist = hc.getHistogram(imageRoi);
	// 创建探险对象
	ContentFinder finder;
	// 设置直方图到探险对象当中
	finder.setHistogram(shist);
	finder.setThreshold(0.05f);
	// 获取背景
	cv::Mat result;
	result = finder.find(color);
	cv::Mat clone = color.clone();
	cv::Scalar borderColor(0, 0, 255);
	cv::rectangle(clone, roiRect, borderColor);
	cvFunction::showMatImg(result, "查找返回");
	cvFunction::showMatImg(clone, "显示目标");
	cvFunction::showMatImg(imageRoi, "运算内容");

	int exec = a.exec();


	return exec;
}