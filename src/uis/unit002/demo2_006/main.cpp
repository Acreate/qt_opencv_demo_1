﻿#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>
#include <random>
#include "demo006.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	auto image = cvFunction::readImage("boldt.jpg", 1);
	// 调用函数以添加噪声
	cv::Mat outImage1 = image.clone();
	unit002::demo002_006::salt(outImage1, 3000);
	cv::Mat outImage2;
	unit002::demo002_006::colorReduce(image, outImage2);
	cv::Mat outImage3;
	unit002::demo002_006::sharpen(image, outImage3);
	cv::Mat outImage4;
	unit002::demo002_006::sharpen2D(image, outImage4);
	cvFunction::showMatImg(image, "image");
	cvFunction::showMatImg(outImage1, "outImage1");
	cvFunction::showMatImg(outImage2, "outImage2");
	cvFunction::showMatImg(outImage3, "outImage3");
	cvFunction::showMatImg(outImage4, "outImage4");

	return a.exec();
}