#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat readImage = cv::imread("waves.jpg");
	cvFunction::showMatImg(readImage);
	std::string string = QString("行 : %1, 列 : %2").arg(readImage.rows).arg(readImage.cols).toLocal8Bit().toStdString();
	std::cout << string << std::endl;
	std::cout.flush();
	return a.exec();
}