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


	cv::Mat image = cv::imread("book.jpg", 0);
	if ( !cvFunction::readImage("book.jpg", image, 0) )
		return -1;
	cvFunction::showMatImg(image, "原始图片");
	cv::transpose(image, image);
	cvFunction::showMatImg(image, "转置图片");
	cv::flip(image, image, 0);
	cvFunction::showMatImg(image, "翻转图片");


	// using a fixed threshold 
	cv::Mat binaryFixed;
	cv::threshold(image, binaryFixed, 70, 255, cv::THRESH_BINARY);
	cvFunction::showMatImg(binaryFixed, "threshold 二值化");

	cv::Mat binaryAdaptive;
	// 邻域尺寸
	int blockSize = 21;
	// 像素将与 (mean-threshold)进行比较
	int threshold = 10;

	// 记录时间
	int64 time;
	time = cv::getTickCount();
	cv::adaptiveThreshold(image,// 输入图像
		binaryAdaptive,// output binary image
		255,// max value for output
		cv::ADAPTIVE_THRESH_MEAN_C,// adaptive method
		cv::THRESH_BINARY,// threshold type
		blockSize,// size of the block
		threshold);// threshold used
	time = cv::getTickCount() - time;
	std::cout << "time (adaptiveThreshold)= " << time << std::endl;
	cvFunction::showMatImg(binaryAdaptive, "自适应二值化(adaptiveThreshold实现)");

	// 计算图像积分
	IntegralImage<int, 1> integral(image);

	// 测试积分返回
	std::cout << "sum=" << integral(18, 45, 30, 50) << std::endl;
	cv::Mat test(image, cv::Rect(18, 45, 30, 50));
	cv::Scalar t = cv::sum(test);
	std::cout << "sum test=" << t[0] << std::endl;
	cvFunction::showMatImg(test, "测试积分图像");

	cv::Mat binary = image.clone();
	time = cv::getTickCount();
	// 获取行
	int nl = binary.rows;
	// 获取列
	int nc = binary.cols;

	// 积分图像目标
	cv::Mat iimage;
	cv::integral(image, iimage,CV_32S);

	int halfSize = blockSize / 2;
	// 遍历所有行
	for ( int j = halfSize; j < nl - halfSize - 1; j++ ) {
		// 获取当前行的元素指针
		uchar *data = binary.ptr<uchar>(j);
		int *idata1 = iimage.ptr<int>(j - halfSize);
		int *idata2 = iimage.ptr<int>(j + halfSize + 1);
		// 遍历所有元素
		for ( int i = halfSize; i < nc - halfSize - 1; i++ ) {
			int i1 = i + halfSize + 1;
			int i2 = i - halfSize;
			// 计算和
			int sum = (idata2[i1] - idata2[i2] - idata1[i1] + idata1[i2]) / (blockSize * blockSize);
			// 应用自适应
			if ( data[i] < (sum - threshold) )
				data[i] = 0;
			else
				data[i] = 255;
		}
	}

	// 加上边框
	for ( int j = 0; j < halfSize; j++ ) {
		uchar *data = binary.ptr<uchar>(j);
		for ( int i = 0; i < binary.cols; i++ ) 
			data[i] = 255;
	}
	for ( int j = binary.rows - halfSize - 1; j < binary.rows; j++ ) {
		uchar *data = binary.ptr<uchar>(j);
		for ( int i = 0; i < binary.cols; i++ ) 
			data[i] = 255;
	}
	for ( int j = halfSize; j < nl - halfSize - 1; j++ ) {
		uchar *data = binary.ptr<uchar>(j);
		for ( int i = 0; i < halfSize; i++ ) 
			data[i] = 255;
		for ( int i = binary.cols - halfSize - 1; i < binary.cols; i++ ) 
			data[i] = 255;
	}

	time = cv::getTickCount() - time;
	std::cout << "time integral= " << time << std::endl;
	cvFunction::showMatImg(binary, "自适应二值化(手动积分图像实现)");

	// 滤波实现
	time = cv::getTickCount();
	cv::Mat filtered;
	cv::Mat binaryFiltered;
	// 计算矩形区域像素内的平均值
	cv::boxFilter(image, filtered,CV_8U, cv::Size(blockSize, blockSize));
	// 检查元素是否大于 mean + threshold
	binaryFiltered = image >= (filtered - threshold);
	time = cv::getTickCount() - time;
	std::cout << "time filtered= " << time << std::endl;
	cvFunction::showMatImg(binaryFiltered, "自适应图像(过滤实现)");
	const int exec = a.exec();
	return exec;
}