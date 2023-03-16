#include <QGuiApplication>

#include <iostream>
#include "CvFunction.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram.h"
#include "contentFinder.h"
#include "colorhistogram.h"
#include "ImageComparator.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat image;
	if ( !cvFunction::readImage("waves.jpg", image) )
		return -1;
	cvFunction::showMatImg(image, "比较图像 1");
	ImageComparator c;
	c.setReferenceImage(image);
	cv::Mat input;
	if ( ! cvFunction::readImage("dog.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs dog").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	if ( !cvFunction::readImage("marais.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs marais").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	if ( !cvFunction::readImage("bear.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs bear").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	if ( !cvFunction::readImage("beach.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs beach").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	if ( !cvFunction::readImage("polar.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs polar").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	if ( !cvFunction::readImage("moose.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs moose").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	if ( !cvFunction::readImage("lake.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs lake").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	if ( !cvFunction::readImage("fundy.jpg", input) )
		return -1;
	std::cout << QString("%1 waves vs fundy").arg(c.compare(input)).toLocal8Bit().toStdString() << std::endl;
	
	const int exec = a.exec();
	return exec;
}