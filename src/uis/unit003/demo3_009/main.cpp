#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	// 获取输入
	cv::Mat image;
	if ( !cvFunction::readImage("group.jpg", image) )
		return 0;
	cvFunction::showMatImg(image, "显示常规图片");
	// 一维直方图
	Histogram1D h;
	
	// 截取像素
	cv::Mat str= h.stretch(image,0.01f);
	cvFunction::showMatImg(str, "被截取 0.01f(1%) 的 group.jpg 图像");
	cvFunction::showMatImg(h.getHistogramImage(str), "被截取 0.01f(1%) 的 group.jpg 图像的直方图");

	// 创建一个映射表
	cv::Mat lut(1,256,CV_8U);
	// 创建映射，对应是相反元素
	for (int i=0; i<256; i++) 
		lut.at<uchar>(i)= 255-i;
	cvFunction::showMatImg(h.applyLookUp(image,lut), "被映射的 group.jpg 图像");

	const int exec = a.exec();

	return exec;
}