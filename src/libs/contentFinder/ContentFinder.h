#ifndef CONTENTFINDER_H_H_HEAD__FILE__
#define CONTENTFINDER_H_H_HEAD__FILE__
#pragma once
#include "ContentFinder_export.h"
#include <opencv2/opencv.hpp>

class CONTENTFINDER_EXPORT ContentFinder {

private:
	/// @brief 直方图参数
	float hranges[2];
	/// @brief 范围数组
	const float *ranges[3];
	/// @brief 通道下标
	int channels[3];
	/// @brief 判断阈值
	float threshold;
	/// @brief 输入直方图
	cv::Mat histogram;
	/// @brief 稀疏矩阵(或者不使用，使用 isSparse 判定)
	cv::SparseMat shistogram;
	bool isSparse;

public:
	ContentFinder( ) : threshold(0.1f), isSparse(false) {
		// 指向默认的区间
		ranges[0] = hranges;
		ranges[1] = hranges;
		ranges[2] = hranges;
	}

	/// @brief 设置判断阈值
	/// @param t 新的阈值
	void setThreshold( float t ) {
		threshold = t;
	}

	/// @brief 获取阈值
	/// @return 阈值
	float getThreshold( ) {
		return threshold;
	}

	// 设置直方图，并且归一化
	void setHistogram( const cv::Mat &h ) {
		isSparse = false;
		cv::normalize(h, histogram, 1.0);
	}

	// 设置稀疏直方图，并且归一化
	void setHistogram( const cv::SparseMat &h ) {
		isSparse = true;
		cv::normalize(h, shistogram, 1.0, cv::NORM_L2);
	}

	// 使用全部通道，范围 [0,256]
	cv::Mat find( const cv::Mat &image ) {

		cv::Mat result;
		// 设置通道 [0,156)
		hranges[0] = 0.0;
		hranges[1] = 256.0;
		// 3 通道
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;

		return find(image, hranges[0], hranges[1], channels);
	}

	/// @brief 查找属于直方图的像素
	/// @param image 查找图像
	/// @param minValue 最小值
	/// @param maxValue 最大值
	/// @param channels 通道数组（描述通道下标）
	/// @return 查找到的图像
	cv::Mat find( const cv::Mat &image, float minValue, float maxValue, const int *channels ) {
		cv::Mat result;
		hranges[0] = minValue;
		hranges[1] = maxValue;
		if ( isSparse ) {
			// 使用稀疏矩阵
			for ( int i = 0; i < shistogram.dims(); i++ )
				this->channels[i] = channels[i];
			cv::calcBackProject(&image,
				1,// 只是单个图像
				channels,// 通道描述数组
				shistogram,// 直方图
				result,// 方向投影的图像
				ranges,// 维度范围描述数组
				255.0// 把概念从 1 映射到 255
				);
		} else {
			// 通道下标与维度数一致
			for ( int i = 0; i < histogram.dims; i++ )
				this->channels[i] = channels[i];
			cv::calcBackProject(&image,
				1,// 只是单个图像
				channels,// 通道描述数组
				histogram,// 直方图
				result,// 方向投影的图像
				ranges,// 维度范围描述数组
				255.0// 把概念从 1 映射到 255
				);
		}
		// 比要的时候，使用二值化
		if ( threshold > 0.0 )
			cv::threshold(result, result, 255.0 * threshold, 255.0, cv::THRESH_BINARY);
		return result;
	}

};


#endif // CONTENTFINDER_H_H_HEAD__FILE__