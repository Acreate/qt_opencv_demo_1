#ifndef HISTOGRAM_H_H_HEAD__FILE__
#define HISTOGRAM_H_H_HEAD__FILE__
#pragma once

#include "Histogram_export.h"
#include <opencv2/opencv.hpp>

/// @brief 创建灰度图像的直方图
/// @brief 仅仅处理灰度图
class HISTOGRAM_EXPORT Histogram1D {

private:
	int histSize[1];// 直方图中箱子的数量
	float hranges[2];// 值范围
	const float *ranges[1];// 值范围的指针
	int channels[1];// 要检查的通道数量

public:
	Histogram1D( ) {

		// 一些建议的默认参数
		histSize[0] = 256;// 256 个箱子
		hranges[0] = 0.0;// 从 0 开始 (含)
		hranges[1] = 256.0;// 到 256 (不含)
		ranges[0] = hranges;
		channels[0] = 0;// 先关注通道 0
	}

	// 设置通道数量，默认为 1
	void setChannel( int c ) {

		channels[0] = c;
	}

	// 获取通道数量
	int getChannel( ) {

		return channels[0];
	}

	// 设置范围 [0,256)
	void setRange( float minValue, float maxValue ) {

		hranges[0] = minValue;
		hranges[1] = maxValue;
	}

	// 获取最小值
	float getMinValue( ) {

		return hranges[0];
	}

	// 获取最大值
	float getMaxValue( ) {

		return hranges[1];
	}

	// 设置箱子数量，默认为 256
	void setNBins( int nbins ) {

		histSize[0] = nbins;
	}

	// 获取箱子数量
	int getNBins( ) {
		return histSize[0];
	}

	// 计算一维直方图
	cv::Mat getHistogram( const cv::Mat &image ) {

		cv::Mat hist;

		// 使用 opencv 中的 calcHist 函数计算
		cv::calcHist(&image,
			1,// 只计算一个图像
			channels,// 使用的通道
			cv::Mat(),// 不使用掩码
			hist,// 作为结果的直方图
			1,// 描述为 1维
			histSize,// 箱子数量
			ranges// 像素值的范围
			);

		return hist;
	}


	// 计算一维直方图，并且返回它的图像
	cv::Mat getHistogramImage( const cv::Mat &image, int zoom = 1 ) {

		// 开始计算
		cv::Mat hist = getHistogram(image);

		// 创建图像
		return Histogram1D::getImageOfHistogram(hist, zoom);
	}

	// Stretches the source image using min number of count in bins.
	cv::Mat stretch( const cv::Mat &image, int minValue = 0 ) {

		// Compute histogram first
		cv::Mat hist = getHistogram(image);

		// find left extremity of the histogram
		int imin = 0;
		for ( ; imin < histSize[0]; imin++ ) {
			// ignore bins with less than minValue entries
			if ( hist.at<float>(imin) > minValue )
				break;
		}

		// find right extremity of the histogram
		int imax = histSize[0] - 1;
		for ( ; imax >= 0; imax-- ) {

			// ignore bins with less than minValue entries
			if ( hist.at<float>(imax) > minValue )
				break;
		}

		// Create lookup table
		int dims[1] = {256};
		cv::Mat lookup(1, dims, CV_8U);

		for ( int i = 0; i < 256; i++ ) {

			if ( i < imin )
				lookup.at<uchar>(i) = 0;
			else if ( i > imax )
				lookup.at<uchar>(i) = 255;
			else
				lookup.at<uchar>(i) = cvRound(255.0 * (i - imin) / (imax - imin));
		}

		// Apply lookup table
		cv::Mat result;
		result = applyLookUp(image, lookup);

		return result;
	}

	// Stretches the source image using percentile.
	cv::Mat stretch( const cv::Mat &image, float percentile ) {

		// number of pixels in percentile
		float number = image.total() * percentile;

		// Compute histogram first
		cv::Mat hist = getHistogram(image);

		// find left extremity of the histogram
		int imin = 0;
		for ( float count = 0.0; imin < 256; imin++ ) {
			// number of pixel at imin and below must be > number
			if ( (count += hist.at<float>(imin)) >= number )
				break;
		}

		// find right extremity of the histogram
		int imax = 255;
		for ( float count = 0.0; imax >= 0; imax-- ) {
			// number of pixel at imax and below must be > number
			if ( (count += hist.at<float>(imax)) >= number )
				break;
		}

		// Create lookup table
		int dims[1] = {256};
		cv::Mat lookup(1, dims, CV_8U);

		for ( int i = 0; i < 256; i++ ) {

			if ( i < imin )
				lookup.at<uchar>(i) = 0;
			else if ( i > imax )
				lookup.at<uchar>(i) = 255;
			else
				lookup.at<uchar>(i) = cvRound(255.0 * (i - imin) / (imax - imin));
		}

		// Apply lookup table
		cv::Mat result;
		result = applyLookUp(image, lookup);

		return result;
	}

	// static methods

	// 创建一个表示直方图的图像
	static cv::Mat getImageOfHistogram( const cv::Mat &hist, int zoom ) {

		// 获取箱子值最大值和最小值
		double maxVal = 0;
		double minVal = 0;
		cv::minMaxLoc(hist, &minVal, &maxVal);

		// 取得直方图的大小
		int histSize = hist.rows;

		// 用于显示直方图的方形图像
		cv::Mat histImg(histSize * zoom, histSize * zoom, CV_8U, cv::Scalar(255));

		// 设置最高点为 90%(即图像高度)的箱子个数
		int hpt = static_cast<int>(0.9 * histSize);

		// 为每个箱子绘制垂直直线
		for ( int h = 0; h < histSize; h++ ) {

			float binVal = hist.at<float>(h);
			if ( binVal > 0 ) {
				int intensity = static_cast<int>(binVal * hpt / maxVal);
				cv::line(histImg, cv::Point(h * zoom, histSize * zoom),
					cv::Point(h * zoom, (histSize - intensity) * zoom), cv::Scalar(0), zoom);
			}
		}

		return histImg;
	}

	// Equalizes the source image.
	static cv::Mat equalize( const cv::Mat &image ) {

		cv::Mat result;
		cv::equalizeHist(image, result);

		return result;
	}


	// Applies a lookup table transforming an input image into a 1-channel image
	static cv::Mat applyLookUp( const cv::Mat &image,
		// input image
		const cv::Mat &lookup ) {
		// 1x256 uchar matrix

		// the output image
		cv::Mat result;

		// apply lookup table
		cv::LUT(image, lookup, result);

		return result;
	}

	// Applies a lookup table transforming an input image into a 1-channel image
	// this is a test version with iterator; always use function cv::LUT
	static cv::Mat applyLookUpWithIterator( const cv::Mat &image, const cv::Mat &lookup ) {

		// Set output image (always 1-channel)
		cv::Mat result(image.rows, image.cols,CV_8U);
		cv::Mat_<uchar>::iterator itr = result.begin<uchar>();

		// Iterates over the input image
		cv::Mat_<uchar>::const_iterator it = image.begin<uchar>();
		cv::Mat_<uchar>::const_iterator itend = image.end<uchar>();

		// Applies lookup to each pixel
		for ( ; it != itend; ++it, ++itr ) {

			*itr = lookup.at<uchar>(*it);
		}

		return result;
	}
};


#endif // HISTOGRAM_H_H_HEAD__FILE__