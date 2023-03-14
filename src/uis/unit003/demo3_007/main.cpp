#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"
#include "Colorhistogram.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat baboon01;
	cvFunction::readImage("baboon01.jpg", baboon01);
	cvFunction::showMatImg(baboon01, "第一只狒狒");
	// 狒狒脸部的 ROI
	cv::Rect roiRect(110, 45, 35, 45);
	cv::Mat imageRoi = baboon01(roiRect);
	cvFunction::showMatImg(imageRoi, "第一个狒狒感兴趣的区域");
	cv::Mat drawImage = baboon01.clone();
	cv::rectangle(drawImage, roiRect, cv::Scalar(255, 0, 0));
	cvFunction::showMatImg(drawImage, "第一个狒狒被提取的区域");
	// 狒狒脸部的直方图
	int minSat = 65;
	ColorHistogram hc;
	hc.setSize(8);
	cv::Mat shist = hc.getHueHistogram(imageRoi, minSat);
	// 创建探险对象
	ContentFinder finder;
	// 设置直方图到探险对象当中
	finder.setHistogram(shist);
	cv::Mat hsv;
	cv::cvtColor(baboon01, hsv, CV_BGR2HSV);
	// 切分通道
	std::vector<cv::Mat> channelVector;
	cv::split(hsv, channelVector);
	// 显示单通道
	cv::threshold(channelVector[1], channelVector[1], minSat, 255, cv::THRESH_BINARY);
	cvFunction::showMatImg(channelVector[1], "s 通道显示");

	// 加载另一个狒狒
	cv::Mat baboon02;
	cvFunction::readImage("baboon02.jpg", baboon02);
	cvFunction::showMatImg(baboon02, "第二只狒狒");
	cv::cvtColor(baboon02, hsv, cv::COLOR_BGR2HSV);
	// 得到色调直方图的反向投影
	int ch[1] = {0};
	// 不做阈值化
	finder.setThreshold(-1.0f);
	cv::Mat result;
	result = finder.find(hsv, 0.0f, 180.0f, ch);
	cvFunction::showMatImg(result, "第二只狒狒，第一次返回显示");
	drawImage = baboon02.clone();
	cv::rectangle(drawImage, roiRect, cv::Scalar(0, 0, 255));
	
	cv::TermCriteria criteria(
		cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
		10,// 最多迭代 10 次
		1// 或者移动距离小于 1 个像素
		);
	cv::meanShift(result, roiRect, criteria);
	cv::rectangle(drawImage, roiRect, cv::Scalar(0,255,0));
	cvFunction::showMatImg(drawImage, "查找返回");

	int exec = a.exec();
	return exec;
}