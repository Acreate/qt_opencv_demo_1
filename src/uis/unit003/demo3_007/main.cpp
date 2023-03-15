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
	// 二值化输出图像
	cv::Mat thresholded;
	cv::threshold(image, thresholded,
		70,// 阈值
		255,// 最大阈值
		cv::THRESH_BINARY);// 二值化类型
	cvFunction::showMatImg(thresholded, "二值化 group.jpg");
	thresholded = 255 - thresholded;
	cvFunction::showMatImg(thresholded, "255 - thresholded");

	int exec = a.exec();

	return exec;
}