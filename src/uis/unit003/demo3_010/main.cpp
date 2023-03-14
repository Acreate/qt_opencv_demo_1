#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"
#include "Colorhistogram.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat image;
	// 灰度图，多通道无法正常在计算直方图之后字节输出
	cvFunction::readImage("waves.jpg", image, 0);
	cvFunction::showMatImg(image, "加载图像");
	cv::Rect roiRect(216, 33, 24, 30);
	cv::Mat imageRoi = image(roiRect);
	cvFunction::showMatImg(imageRoi, "截取区域");
	// 1 维直方图
	Histogram1D h;
	cv::Mat hist = h.getHistogram(imageRoi);
	cvFunction::showMatImg(hist, "截取区域直方图");

	// 创建探险对象
	ContentFinder finder;
	// 设置直方图到探险对象当中
	finder.setHistogram(hist);
	finder.setThreshold(0.05f);
	// 获取背景
	cv::Mat result1;
	result1 = finder.find(image);
	cv::Mat tmp;

	// 转为单通道
	result1.convertTo(tmp, CV_8U, -1, 255);

	cvFunction::showMatImg(tmp, "截取区域直方图");
	finder.setThreshold(0.12f);
	result1 = finder.find(image);
	cv::rectangle(image, roiRect, cv::Scalar(0, 0, 255));
	cvFunction::showMatImg(image, "描述被截取的图像");
	
	int exec = a.exec();
	return exec;
}