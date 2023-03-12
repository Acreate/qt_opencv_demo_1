#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>
#include <random>

#include "Colordetector.h"
#include "demo001.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	ColorDetector cdetect;
	auto image = cvFunction::readImage("boldt.jpg", 1);

	cdetect.setTargetColor(230, 190, 130);
	cv::Mat result = cdetect.process(image);
	cvFunction::showMatImg(image);
	cvFunction::showMatImg(result);
	result = image.clone();
	cv::floodFill(result,// 输入/输出图像 
		cv::Point(100, 50),// 起始点
		cv::Scalar(255, 255, 255),// 填充颜色
		(cv::Rect *)0,// 填充区域的边界矩形
		cv::Scalar(35, 35, 35),// 偏差的最小/最大阈值
		cv::Scalar(35, 35, 35),// 正差阈值，两个阈值通常相等
		cv::FLOODFILL_FIXED_RANGE);// 与起始点像素比较
		
	cvFunction::showMatImg(result);
	return a.exec();
}