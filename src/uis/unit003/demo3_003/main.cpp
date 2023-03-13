#include <iostream>
#include <QGuiApplication>

#include "CvFunction.h"
#include "Histogram.h"
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main( int argc, char *argv[] ) {

	QGuiApplication a(argc, argv);
	cv::Mat image = cv::imread("group.jpg", 0);
	if( image.empty() )
		return -1;
	cvFunction::showMatImg(image);
	Histogram1D h;
	cv::Mat histogram = h.getHistogram(image);
	cvFunction::showMatImg(histogram);
	cv::Mat histogramImage = h.getHistogramImage(image);
	cvFunction::showMatImg(histogramImage);
	cv::Mat thresholded;
	cv::threshold(image, thresholded, 70, 255, cv::THRESH_BINARY);
	cvFunction::showMatImg(thresholded);
	return a.exec();
}