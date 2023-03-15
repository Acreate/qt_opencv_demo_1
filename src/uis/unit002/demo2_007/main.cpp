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
	cv::Mat image, destImage;
	if ( !cvFunction::readImage("boldt.jpg", image, 1) )
		return -1;
	cvFunction::showMatImg(image);
	unit002::demo002_007::wave(image, destImage);
	cvFunction::showMatImg(destImage);
	unit002::demo002_007::filp(image, destImage);
	cvFunction::showMatImg(destImage);
	return a.exec();
}