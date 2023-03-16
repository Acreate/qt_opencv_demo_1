#include <QGuiApplication>

#include <iostream>
#include "CvFunction.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram.h"
#include "IntegralImage.h"
#include "contentFinder.h"
#include "colorhistogram.h"
#include "ConverStr.h"

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);

	// 打开 bike55.bmp
	cv::Mat image;
	if ( !cvFunction::readImage("bike55.bmp", image, 0) )
		return -1;
	// 感兴趣区域
	int xo = 97, yo = 112;
	int width = 25, height = 30;
	cv::Rect roiRect = cv::Rect(xo, yo, width, height);
	// 截取
	cv::Mat roi(image, roiRect);

	// 16 元素的直方图
	Histogram1D h;
	h.setNBins(16);
	// 获取截取区域的直方图
	cv::Mat refHistogram = h.getHistogram(roi);
	cvFunction::showMatImg(h.getHistogramImage(roi, 16), "截取区域的直方图显示");
	std::cout << refHistogram << std::endl;

	// 创建一个16层显示面板
	cv::Mat planes;
	convertToBinaryPlanes(image, planes, 16);
	// 计算积分
	IntegralImage<float, 16> intHisto(planes);

	// 测试计算 16 箱子的积分图像直方图
	cv::Vec<float, 16> histogram = intHisto(xo, yo, width, height);
	std::cout << histogram << std::endl;

	cv::Mat im = h.getImageOfHistogram(cv::Mat(histogram), 16);
	cv::imshow("Reference Histogram (2)", im);
	cvFunction::showMatImg(im, "引用的直方图数据显示");

	// 第二张图片中搜索
	cv::Mat secondImage;
	if ( !cvFunction::readImage("bike65.bmp", secondImage, 0) )
		return 0;

	// 先创建 16 层面板图像
	convertToBinaryPlanes(secondImage, planes, 16);
	// 计算其积分
	IntegralImage<float, 16> intHistogram(planes);

	// 用积分图像计算 16 个图像直方图(测试)
	histogram = intHistogram(135, 114, width, height);
	std::cout << histogram << std::endl;

	cv::Mat im2 = h.getImageOfHistogram(cv::Mat(histogram), 16);
	cvFunction::showMatImg(im2, "当前直方图");

	std::cout << "Distance= " << cv::compareHist(refHistogram, histogram, cv::HISTCMP_INTERSECT) << std::endl;

	double maxSimilarity = 0.0;
	int xbest, ybest;
	// 遍历原始图像中女孩位置周围的水平长条 
	for ( int y = 110; y < 120; y++ ) {
		for ( int x = 0; x < secondImage.cols - width; x++ ) {
			// 用积分图像计算 16 个箱子的直方图
			histogram = intHistogram(x, y, width, height);
			// 计算与基准直方图的差距
			double distance = cv::compareHist(refHistogram, histogram, cv::HISTCMP_INTERSECT);
			// 找到最相似直方图的位置
			if ( distance > maxSimilarity ) {
				xbest = x;
				ybest = y;
				maxSimilarity = distance;
			}
			std::cout << "Distance(" << x << "," << y << ")=" << distance << std::endl;
		}
	}

	std::cout << "Best solution= (" << xbest << "," << ybest << ")=" << maxSimilarity << std::endl;
	// 最初的位置绘制
	cv::rectangle(image, cv::Rect(xo, yo, width, height), 0);
	cvFunction::showMatImg(image, "最初的图像");
	cvFunction::showMatImg(secondImage, "最新的图像");

	// 找到的位置绘制
	cv::rectangle(secondImage, cv::Rect(xbest, ybest, width, height), 0);
	// 位置水平框选
	cv::rectangle(secondImage, cv::Rect(0, 110, secondImage.cols, height + 10), 255);
	cvFunction::showMatImg(secondImage, "最新的图像.截取位置");

	const int exec = a.exec();
	return exec;
}