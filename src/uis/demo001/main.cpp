#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>

int main( int argc, char *argv[] ) {
	QCoreApplication a(argc, argv);
	cv::Mat readImage = cv::imread("waves.jpg");
	std::cout << "rows : " << readImage.rows << ", " << "col : " << readImage.cols;
	cvFunction::showMatImg(readImage);
	return a.exec();
}