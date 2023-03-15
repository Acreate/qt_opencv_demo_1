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
	cvFunction::writeImage("groupBW.jpg", image);
	cvFunction::showMatImg(image, "显示常规图片");
	// 一维直方图
	Histogram1D h;
	cv::Mat histo = h.getHistogram(image);
	// 输出所有元素的占用
	for ( int i = 0; i < 256; i++ )
		std::cout << QString("颜色值 %1 ，个数为 %2").arg(i).arg(histo.at<float>(i)).toLocal8Bit().toStdString() << std::endl;
	cv::Mat hi = h.getHistogramImage(image);
	cvFunction::showMatImg(hi, "图片显示 group.jpg 直方图");
	cv::line(hi, cv::Point(70, 0), cv::Point(70, 255), cv::Scalar(128));
	cvFunction::showMatImg(hi, "图片显示 group.jpg 直方图");
	
	int exec = a.exec();

	return exec;
}