#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>
#include <random>
#include "demo006.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	auto image = cvFunction::readImage("boldt.jpg", 1);
	auto imageMerge = cvFunction::readImage("rain.jpg", 1);
	cvFunction::showMatImg(image);
	cvFunction::showMatImg(imageMerge);
	// 和运算
	cv::Mat destImage;
	cv::add(image, imageMerge, destImage);
	cvFunction::showMatImg(destImage);
	cv::addWeighted(image, 0.7, imageMerge, 0.9, 0., destImage);
	cvFunction::showMatImg(destImage);
	// 分割通道
	std::vector<cv::Mat> planes;
	cv::split(image, planes);
	planes[0] += cv::Scalar(-255, 255, 255);
	// 合并通道
	cv::merge(planes, destImage);
	cvFunction::showMatImg(destImage);
	return a.exec();
}