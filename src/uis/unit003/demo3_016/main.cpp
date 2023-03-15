#include <QGuiApplication>

#include <iostream>
#include "CvFunction.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram.h"
#include "contentFinder.h"
#include "colorhistogram.h"
#include "Integral.h"

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


	// histogram of 16 bins
	Histogram1D h;
	h.setNBins(16);
	// compute histogram over image roi 
	cv::Mat refHistogram = h.getHistogram(roi);

	cvFunction::showMatImg(h.getHistogramImage(roi, 16), "Reference Histogram");
	std::cout << refHistogram << std::endl;

	// first create 16-plane binary image
	cv::Mat planes;
	convertToBinaryPlanes(image, planes, 16);
	// then compute integral image
	IntegralImage<float, 16> intHisto(planes);


	// for testing compute a histogram of 16 bins with integral image
	cv::Vec<float, 16> histogram = intHisto(xo, yo, width, height);
	std::cout << histogram << std::endl;

	cv::Mat im = h.getImageOfHistogram(cv::Mat(histogram), 16);
	cvFunction::showMatImg(im, "Reference Histogram (2)");

	// search in second image
	cv::Mat secondImage;
	if ( !cvFunction::readImage("bike65.bmp", secondImage, 0) )
		return -1;

	// first create 16-plane binary image
	convertToBinaryPlanes(secondImage, planes, 16);
	// then compute integral image
	IntegralImage<float, 16> intHistogram(planes);

	// compute histogram of 16 bins with integral image (testing)
	histogram = intHistogram(135, 114, width, height);
	std::cout << histogram << std::endl;

	cv::Mat im2 = h.getImageOfHistogram(cv::Mat(histogram), 16);
	cvFunction::showMatImg(im2, "Histogram");

	std::cout << "Distance= " << cv::compareHist(refHistogram, histogram, cv::HISTCMP_INTERSECT) << std::endl;

	double maxSimilarity = 0.0;
	int xbest, ybest;
	// loop over a horizontal strip around girl location in initial image
	for ( int y = 110; y < 120; y++ ) {
		for ( int x = 0; x < secondImage.cols - width; x++ ) {
			// compute histogram of 16 bins using integral image
			histogram = intHistogram(x, y, width, height);
			// compute distance with reference histogram
			double distance = cv::compareHist(refHistogram, histogram, cv::HISTCMP_INTERSECT);
			// find position of most similar histogram
			if ( distance > maxSimilarity ) {
				xbest = x;
				ybest = y;
				maxSimilarity = distance;
			}
			std::cout << "Distance(" << x << "," << y << ")=" << distance << std::endl;
		}
	}

	std::cout << "Best solution= (" << xbest << "," << ybest << ")=" << maxSimilarity << std::endl;

	// draw a rectangle around target object
	cv::rectangle(image, cv::Rect(xo, yo, width, height), 0);
	cvFunction::showMatImg(image, "Initial Image");

	cvFunction::showMatImg(secondImage, "New Image");

	// draw rectangle at best location
	cv::rectangle(secondImage, cv::Rect(xbest, ybest, width, height), 0);
	// draw rectangle around search area
	cv::rectangle(secondImage, cv::Rect(0, 110, secondImage.cols, height + 10), 255);
	cvFunction::showMatImg(secondImage, "Object location");

	const int exec = a.exec();
	return exec;
}