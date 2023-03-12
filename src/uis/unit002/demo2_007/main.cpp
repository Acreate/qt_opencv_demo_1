#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>
#include <random>
#include "demo007.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	auto image = cvFunction::readImage("boldt.jpg", 1);
	cv::Mat destImage;
	cvFunction::showMatImg(image);
	unit002::demo002_007::wave(image, destImage);
	cvFunction::showMatImg(destImage);
	unit002::demo002_007::filp(image, destImage);
	cvFunction::showMatImg(destImage);
	return a.exec();
}