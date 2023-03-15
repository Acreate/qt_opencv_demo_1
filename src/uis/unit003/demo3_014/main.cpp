#include <QGuiApplication>

#include <iostream>
#include "CvFunction.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram.h"
#include "contentFinder.h"
#include "colorhistogram.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat image;
	if ( !cvFunction::readImage("baboon01.jpg", image) )
		return -1;
	cv::Mat imageRIO;
	cv::Rect rect(110, 45, 35, 45);
	cv::rectangle(image, rect, cv::Scalar(255, 0, 0));
	cvFunction::showMatImg(image, "狒狒1");
	
	imageRIO = image(rect);
	ColorHistogram hc;
	cv::Mat colorhist;
	int minSat = 65;
	// 获取截取区域的直方图
	colorhist = hc.getHueHistogram(imageRIO, minSat);
	ContentFinder finder;
	// 设置直方图
	finder.setHistogram(colorhist);
	cv::Mat image2;
	if ( !cvFunction::readImage("baboon02.jpg", image2) )
		return -1;
	cv::Mat hsv;
	cv::cvtColor(image2, hsv, cv::COLOR_BGR2HSV);
	int ch[1] = {0};
	// 不做阈值
	finder.setThreshold(-1);
	// 在 baboon02.jpg(hsv 格式)当中的 0 通道查找直方图，并且返回投影（直方图在 baboon02.jpg(hsv 格式) 中的投影）
	cv::Mat result = finder.find(hsv, 0, 180, ch);
	// 迭代描述器(描述迭代终止)
	cv::TermCriteria criteria(
		// 最大迭代数
		cv::TermCriteria::MAX_ITER |
		// 中心的偏移值小于某个限值
		cv::TermCriteria::EPS,
		10,// 迭代 10 次
		1// 或者中心移动距离小于 1 个像素
		);
	// 开始迭代查找投影在源中的位置
	// 返回迭代查找到的内容，该内容由 rect 描述
	// 输入数据必须是投影
	cv::meanShift(result, rect, criteria);
	cv::rectangle(image2, rect, cv::Scalar(255, 0, 0));
	cvFunction::showMatImg(image2, "狒狒2");
	const int exec = a.exec();
	return exec;
}