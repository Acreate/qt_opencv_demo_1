#ifndef COLORDETECTOR_H_H_HEAD__FILE__
#define COLORDETECTOR_H_H_HEAD__FILE__
#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include "Colordetector_export.h"
class COLORDETECTOR_EXPORT ColorDetector {

private:
	// 允许的最小差距
	int maxDist;

	// 目标颜色
	cv::Vec3b target;

	// 存储二值映像结果的图像
	cv::Mat converted;
	// 使用 lab 颜色格式的构造
	bool useLab;

	// 存储二值映像结果的图像
	cv::Mat result;

public:
	// 默认的初始化构造函数
	ColorDetector( ) : maxDist(100), target(0, 0, 0), useLab(false) {}

	// 使用 lab 颜色格式的构造
	ColorDetector( bool useLab ) : maxDist(100), target(0, 0, 0), useLab(useLab) {}

	// 使用目标颜色和颜色距离作为参数的构造
	ColorDetector( uchar blue, uchar green, uchar red, int mxDist = 100, bool useLab = false ): maxDist(mxDist), useLab(useLab) {
		// 设置目标颜色
		setTargetColor(blue, green, red);
	}

	// 计算与目标颜色的差距
	int getDistanceToTargetColor( const cv::Vec3b &color ) const {
		return getColorDistance(color, target);
	}

	// 计算两个颜色之间的城区差距
	int getColorDistance( const cv::Vec3b &color1, const cv::Vec3b &color2 ) const {

		return abs(color1[0] - color2[0]) +
			abs(color1[1] - color2[1]) +
			abs(color1[2] - color2[2]);
	}

	// 处理并且返回成员函数
	cv::Mat process( const cv::Mat &image );

	cv::Mat operator()( const cv::Mat &image ) {

		cv::Mat input;

		if( useLab ) {
			// Lab conversion
			cv::cvtColor(image, input, CV_BGR2Lab);
		} else {
			input = image;
		}

		cv::Mat output;
		// compute absolute difference with target color
		cv::absdiff(input, cv::Scalar(target), output);
		// split the channels into 3 images
		std::vector<cv::Mat> images;
		cv::split(output, images);
		// add the 3 channels (saturation might occurs here)
		output = images[0] + images[1] + images[2];
		// apply threshold
		cv::threshold(output,// input image
			output,// output image
			maxDist,// threshold (must be < 256)
			255,// max value
			cv::THRESH_BINARY_INV);// thresholding type

		return output;
	}

	
	/// @brief 设置颜色差距的阈值
	/// 阈值必须为整数，否则就设置为 0
	/// @param distance 被设置的值
	void setColorDistanceThreshold( int distance ) {

		if( distance < 0 )
			distance = 0;
		maxDist = distance;
	}

	// 取得颜色差距的阈值
	int getColorDistanceThreshold( ) const {

		return maxDist;
	}

	/// @brief 设置需要检测的颜色
	/// @param blue 蓝
	/// @param green 绿
	/// @param red 红
	void setTargetColor( uchar blue, uchar green, uchar red ) {

		// 次序为 bgr
		target = cv::Vec3b(blue, green, red);

		if( useLab ) {
			// Temporary 1-pixel image
			cv::Mat tmp(1, 1, CV_8UC3);
			tmp.at<cv::Vec3b>(0, 0) = cv::Vec3b(blue, green, red);

			// Converting the target to Lab color space 
			cv::cvtColor(tmp, tmp, CV_BGR2Lab);

			target = tmp.at<cv::Vec3b>(0, 0);
		}
	}

	// 设置需要检测的颜色
	void setTargetColor( cv::Vec3b color ) {
		target = color;
	}

	// 获取需要检测的颜色
	cv::Vec3b getTargetColor( ) const {

		return target;
	}
};


#endif