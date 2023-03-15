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
	if ( !cvFunction::readImage("bike55.bmp", image, 0) )
		return -1;
	int xo = 97, yo = 112;
	int width = 25, height = 30;
	cv::Mat roi(image, cv::Rect(xo, yo, width, height));
	cv::Scalar sum = cv::sum(roi);
	std::cout << sum[0] << std::endl;

	// 计算图像积分
	cv::Mat integralImage;
	cv::integral(image, integralImage, CV_32S);
	// 用三个加/减运算得到一个区域的累加值
	int sumInt = integralImage.at<int>(yo + height, xo + width)
		- integralImage.at<int>(yo + height, xo)
		- integralImage.at<int>(yo, xo + width)
		+ integralImage.at<int>(yo, xo);
	std::cout << sumInt << std::endl;

	const int exec = a.exec();
	return exec;
}