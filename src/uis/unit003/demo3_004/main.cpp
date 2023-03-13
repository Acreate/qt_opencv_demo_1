#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

#include "ColorHistogram.h"
#include "CvFunction.h"
#include "Histogram.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat image = cv::imread("bench1.jpg", cv::IMREAD_UNCHANGED);
	if ( !image.data )
		return 0;
	cvFunction::showMatImg(image);
	ColorHistogram coh;
	int channels = image.channels();
	cv::Mat histogram = coh.getHistogram(image);
	cvFunction::showMatImg(histogram);
	histogram = coh.getNormalHistogram(image);
	cv::Mat outResult;
	histogram.convertTo(outResult, CV_8U, -1, 255);
	bool showMatImg = cvFunction::showMatImg(outResult);

	return a.exec();
}