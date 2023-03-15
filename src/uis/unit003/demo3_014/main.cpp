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
	imageRIO = image(rect);
	ColorHistogram hc;
	cv::Mat colorhist;
	int minSat = 65;
	colorhist = hc.getHueHistogram(imageRIO, minSat);
	ContentFinder finder;
	finder.setHistogram(colorhist);
	cv::Mat image2;
	if ( !cvFunction::readImage("baboon02.jpg", image2) )
		return -1;
	cv::Mat hsv;
	cv::cvtColor(image2, hsv, cv::COLOR_BGR2HSV);
	int ch[1] = {0};
	finder.setThreshold(-1);
	cv::Mat result = finder.find(hsv, 0, 180, ch);
	cv::rectangle(image, rect, cv::Scalar(255, 0, 0));
	cvFunction::showMatImg(image, "狒狒1");
	cv::TermCriteria criteria(
		cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
		10,
		1
		);
	cv::meanShift(result, rect, criteria);
	cv::rectangle(image2, rect, cv::Scalar(255, 0, 0));
	cvFunction::showMatImg(image2, "狒狒2");
	const int exec = a.exec();
	return exec;
}