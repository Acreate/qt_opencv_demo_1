#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	// 获取输入
	cv::Mat image;
	if ( !cvFunction::readImage("group.jpg", image) )
		return 0;
	cvFunction::showMatImg(image, "显示常规图片");
	// 一维直方图
	Histogram1D h;
	// 均衡化图片
	cv::Mat eq = h.equalize(image);
	cvFunction::showMatImg(eq, "均衡化 group.jpg");
	cvFunction::showMatImg(h.getHistogramImage(eq), "均衡化 group.jpg，在被直方图");

	int exec = a.exec();

	return exec;
}