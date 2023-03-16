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
	if ( !cvFunction::readImage("waves.jpg", image) )
		return 0;

	// 定义感兴趣区域
	cv::Mat imageROI;
	cv::Rect rectROI = cv::Rect(216, 33, 24, 30);
	// 获取天空部分
	imageROI = image(rectROI);
	// 显示原图像引用
	cv::Scalar color = cv::Scalar(0, 255, 255);
	cv::Mat showImage = image.clone();
	cv::rectangle(showImage, rectROI, color, 2);
	// 显示感兴趣区域
	cvFunction::showMatImg(showImage, "描述引用区域");
	// 显示感兴趣区域
	cvFunction::showMatImg(imageROI, "引用区域");
	cvFunction::writeImage("引用.jpg", imageROI);
	// 1 维直方图
	Histogram1D h;
	cv::Mat hist = h.getHistogram(imageROI);
	cv::Mat histogramImage = h.getHistogramImage(imageROI);
	cvFunction::showMatImg(histogramImage, "引用区域直方图");

	// 创建探险对象
	ContentFinder finder;

	// 设置直方图到探险对象当中
	finder.setHistogram(hist);
	finder.setThreshold(-1.0f);

	// 获取背景
	cv::Mat result1;
	result1 = finder.find(image);

	// 显示投影
	cv::Mat tmp;
	result1.convertTo(tmp,CV_8U, -1.0, 255.0);
	cvFunction::showMatImg(tmp, "投影返回");

	int exec = a.exec();

	return exec;
}