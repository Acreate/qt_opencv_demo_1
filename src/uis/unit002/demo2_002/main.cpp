#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>
#include <random>
#include "demo002.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat image;
	if ( !cvFunction::readImage("boldt.jpg", image, 1) )
		return -1;
	// 调用函数以添加噪声
	unit002::demo002_002::salt(image, 3000);
	unit002::demo002_002::colorReduce(image);
	cvFunction::showMatImg(image);

	return a.exec();
}