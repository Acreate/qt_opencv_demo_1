#ifndef COLORHISTOGRAM_H_H_HEAD__FILE__
#define COLORHISTOGRAM_H_H_HEAD__FILE__
#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/// @brief 彩色图的直方图
class ColorHistogram {

private:
	int histSize[3];// 计算3个维度
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

	// set histogram size for each dimension
	void setSize( int size ) {

		// each dimension has equal size 
		histSize[0] = histSize[1] = histSize[2] = size;
	}

	// Computes the histogram.
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

	// Computes the 1D Hue histogram.
	// BGR source image is converted to HSV
	// Pixels with low saturation are ignored
	cv::Mat getHueHistogram( const cv::Mat &image,
		int minSaturation = 0 ) {

		cv::Mat hist;

		// Convert to HSV colour space
		cv::Mat hsv;
		cv::cvtColor(image, hsv, CV_BGR2HSV);

		// Mask to be used (or not)
		cv::Mat mask;
		// creating the mask if required
		if ( minSaturation > 0 ) {

			// Spliting the 3 channels into 3 images
			std::vector<cv::Mat> v;
			cv::split(hsv, v);

			// Mask out the low saturated pixels
			cv::threshold(v[1], mask, minSaturation, 255,
				cv::THRESH_BINARY);
		}

		// Prepare arguments for a 1D hue histogram
		hranges[0] = 0.0;// range is from 0 to 180
		hranges[1] = 180.0;
		channels[0] = 0;// the hue channel 

		// Compute histogram
		cv::calcHist(&hsv,
			1,// histogram of 1 image only
			channels,// the channel used
			mask,// binary mask
			hist,// the resulting histogram
			1,// it is a 1D histogram
			histSize,// number of bins
			ranges// pixel value range
			);

		return hist;
	}

	// Computes the 2D ab histogram.
	// BGR source image is converted to Lab
	cv::Mat getabHistogram( const cv::Mat &image ) {

		cv::Mat hist;

		// Convert to Lab color space
		cv::Mat lab;
		cv::cvtColor(image, lab, CV_BGR2Lab);

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