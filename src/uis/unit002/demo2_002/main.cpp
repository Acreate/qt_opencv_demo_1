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
	auto image = cvFunction::readImage("boldt.jpg", 1);
	// 调用函数以添加噪声
	unit002::demo002_002::salt(image, 3000);
	unit002::demo002_002::colorReduce(image);
	cvFunction::showMatImg(image);
	
	return a.exec();
}