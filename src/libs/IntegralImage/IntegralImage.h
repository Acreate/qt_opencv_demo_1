#ifndef INTEGRAL_H_H_HEAD__FILE__
#define INTEGRAL_H_H_HEAD__FILE__
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>
#include "IntegralImage_export.h"

template< typename T, int N >
class IntegralImage {

	/// @brief 图像积分图
	cv::Mat integralImage;

public:
	/// @brief 初始化一个图像积分图
	/// @param image 需要计算积分图的忑
	IntegralImage( cv::Mat image ) {
		// 计算，并且赋值给图像积分图
		// 计算积分很耗时
		cv::integral(image, integralImage, cv::DataType<T>::type);
	}

	// 通过访问四个像素，计算任何尺寸子区域的累计值
	cv::Vec<T, N> operator()( int xo, int yo, int width, int height ) {

		// (xo,yo) 处的窗口，尺寸为 width * height
		return (integralImage.at<cv::Vec<T, N> >(yo + height, xo + width)
			- integralImage.at<cv::Vec<T, N> >(yo + height, xo)
			- integralImage.at<cv::Vec<T, N> >(yo, xo + width)
			+ integralImage.at<cv::Vec<T, N> >(yo, xo));
	}

	// compute sum over sub-regions of any size from 4 pixel access
	cv::Vec<T, N> operator()( int x, int y, int radius ) {

		
		return (integralImage.at<cv::Vec<T, N> >(y + radius + 1, x + radius + 1)
			- integralImage.at<cv::Vec<T, N> >(y + radius + 1, x - radius)
			- integralImage.at<cv::Vec<T, N> >(y - radius, x + radius + 1)
			+ integralImage.at<cv::Vec<T, N> >(y - radius, x - radius));
	}
};


/// @brief 转换成二值图层组成的多通道图像
/// @brief nPlanes 必须是 2 的幂
/// @param input 转化的图像
/// @param output 转化实现的图像
/// @param nPlanes 通道数
inline INTEGRALIMAGE_EXPORT void convertToBinaryPlanes( const cv::Mat &input, cv::Mat &output, int nPlanes ) {

	// 屏蔽的位数
	int n = 8 - static_cast<int>(log(static_cast<double>(nPlanes)) / log(2.0));
	// 用来消除最低有效位的掩码
	uchar mask = 0xFF << n;// e.g. for div=16, mask= 0xF0

	// 创建二值图像的向量
	std::vector<cv::Mat> planes;
	// 消除最低有效为，箱子数为 nBins
	cv::Mat reduced = input & mask;

	// 计算每个二值图像平面
	for ( int i = 0; i < nPlanes; i++ ) {
		// 将每个等于 i << shift 的像素设置为 1
		planes.push_back((reduced == (i << n)) & 0x1);
	}

	// 创建多通道图像
	cv::merge(planes, output);
}


#endif // INTEGRAL_H_H_HEAD__FILE__