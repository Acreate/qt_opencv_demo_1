#ifndef COLORHISTOGRAM_H_H_HEAD__FILE__
#define COLORHISTOGRAM_H_H_HEAD__FILE__
#pragma once

#include "ColorHistogram_export.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

/// @brief 彩色图的直方图
class COLORHISTOGRAM_EXPORT ColorHistogram {

private:
	int histSize[3];// 计算3个维度，每个维度统计的最大元素
	float hranges[2];// 值范围
	const float *ranges[3];// 每个维度的范围
	int channels[3];// 处理的通道数

public:
	/// @brief 默认的构造，提供建议参数
	ColorHistogram( ) {
		// 所有维度大小相等
		histSize[0] = histSize[1] = histSize[2] = 256;
		// brg 范围 [0,256)
		hranges[0] = 0.0;
		hranges[1] = 256.0;
		// 所有维度的范围相同
		ranges[0] = hranges;
		ranges[1] = hranges;
		ranges[2] = hranges;
		// 3 维度所在通道下标
		channels[0] = 0;// B
		channels[1] = 1;// G
		channels[2] = 2;// R
	}

	// 返回统计像素最大数值
	void setSize( int maxElemValue ) {
		// 每个维度统计的元素上限为 size
		histSize[0] = histSize[1] = histSize[2] = maxElemValue;
	}

	// 计算直方图
	cv::Mat getHistogram( const cv::Mat &image ) {

		cv::Mat hist;

		// BGR color 直方图预设

		// 范围 [0,256)
		hranges[0] = 0.0;
		hranges[1] = 256.0;
		// 3 通道
		channels[0] = 0;// B
		channels[1] = 1;// G
		channels[2] = 2;// R

		// 计算直方图
		cv::calcHist(&image,
			1,// 一个图片参与运算
			channels,// 使用通道数组
			cv::Mat(),// 不适用遮罩
			hist,// 输出直方图数据
			3,// 它是3维的
			histSize,// 大小数组 3 个
			ranges// 范围数组 3 个
			);

		return hist;
	}

	// 使用 OpenCV 大型稀疏矩阵
	cv::SparseMat getSparseHistogram( const cv::Mat &image ) {

		cv::SparseMat hist(3,// 维度数量
			histSize,// 大小
			CV_32F);

		// BGR color 直方图预设

		// 范围 [0,256)
		hranges[0] = 0.0;
		hranges[1] = 256.0;
		// 3 通道
		channels[0] = 0;// B
		channels[1] = 1;// G
		channels[2] = 2;// R

		// 计算直方图
		cv::calcHist(&image,
			1,// 一个图片参与运算
			channels,// 使用通道数组
			cv::Mat(),// 不适用遮罩
			hist,// 输出直方图数据
			3,// 它是3维的
			histSize,// 大小数组 3 个
			ranges// 范围数组 3 个
			);

		return hist;
	}

	
	/// @brief 忽略低饱和度的像素
	/// @brief BGR 的原图转换为 HSV
	/// @brief 计算以为色调直方图
	/// @param image 计算图像
	/// @param minSaturation 最小忽略数
	/// @return 统计的值
	cv::Mat getHueHistogram( const cv::Mat &image,
		int minSaturation = 0 ) {

		cv::Mat hist;

		// 转换到 HSV 色彩空间
		cv::Mat hsv;
		cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

		// 掩码，也许用不到
		cv::Mat mask;
		// 根据需要创建掩码
		if ( minSaturation > 0 ) {
			// 将 3 个通道分割进 3 个图像
			std::vector<cv::Mat> v;
			cv::split(hsv, v);
			// 屏蔽低饱和度的像素
			cv::threshold(v[1], mask, minSaturation, 255,
				cv::THRESH_BINARY);
		}

		// 需要一维色调直方图的参数
		// [0,180)
		hranges[0] = 0.0;
		hranges[1] = 180.0;
		// 使用 hue 通道（色调通道）
		channels[0] = 0;

		// 计算直方图
		cv::calcHist(&hsv,
			1,// 只有一个图片
			channels,// 用到的通道已经存储到数组当中
			mask,// 也许需要掩码，如果参数 minSaturation 大于 0，则存储在 cv::threshold 函数运行过后的返回中
			hist,// 返回的直方图
			1,// 只是用一维
			histSize,// 箱子数已经存在该数组当中
			ranges// 范围已经存在该数组当中
			);

		return hist;
	}

	// Computes the 2D ab histogram.
	// BGR source image is converted to Lab
	cv::Mat getabHistogram( const cv::Mat &image ) {

		cv::Mat hist;

		// Convert to Lab color space
		cv::Mat lab;
		cv::cvtColor(image, lab, cv::COLOR_BGR2Lab);

		// Prepare arguments for a 2D color histogram
		hranges[0] = 0;
		hranges[1] = 256.0;
		channels[0] = 1;// the two channels used are ab 
		channels[1] = 2;

		// Compute histogram
		cv::calcHist(&lab,
			1,// histogram of 1 image only
			channels,// the channel used
			cv::Mat(),// no mask is used
			hist,// the resulting histogram
			2,// it is a 2D histogram
			histSize,// number of bins
			ranges// pixel value range
			);

		return hist;
	}
};


#endif