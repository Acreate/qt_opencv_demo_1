#ifndef HISTOGRAM_H_H_HEAD__FILE__
#define HISTOGRAM_H_H_HEAD__FILE__
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// 灰度图的直方图计算类
class Histogram1D {
private:
	/// @brief 箱子数量记录数组，当前灰度图只有一个通道，所以只需要描述一个
	int histSize[1];

	/// @brief 值范围，通常是左闭右开 [number1, number2)
	float hranges[2];

	/// @brief 值范围指针数组，指向 {hranges}，若 2个 hranges，则有 const float *ranges[2];  ranges={hranges1, hranges2}
	const float *ranges[1];

	/// @brief 通道数数组，灰度图只有单通道，所以数量只有 1, 若 2个通道，则有 channels[2]
	/// @brief 通道数通常由 0 开始
	int channels[1];

public:
	/// @brief 准备一些默认的配置
	Histogram1D( ) {
		// 256 箱子
		histSize[0] = 256;
		// [0,256) 
		hranges[0] = 0.0, hranges[1] = 256.0;
		ranges[0] = hranges;
		// 关注通道
		channels[0] = 0;
	}


	/// @brief 设置关注通道
	/// @param c 通道下标
	void setChannel( int c ) {
		channels[0] = c;
	}

	/// @brief 获取当前关注通道
	/// @return 当前单通道所关注下标
	int getChannel( ) {
		return channels[0];
	}

	/// @brief 设置数值范围，他总是 [,) 空间
	/// @param minValue 最小（包含）
	/// @param maxValue 最大（不包含）
	void setRange( float minValue, float maxValue ) {
		hranges[0] = minValue;
		hranges[1] = maxValue;
	}

	/// @brief 获取最小值（参与运算的最小值）
	/// @return 最小值
	float getMinValue( ) {
		return hranges[0];
	}

	/// @brief 获取最大值（运算途中是不包含的最大值）
	/// @return 最大值
	float getMaxValue( ) {
		return hranges[1];
	}

	/// @brief 设置限制数量，参与运算运算时候与最大（不包含），最小（包含）以前发生
	/// @brief 该数值属于高度，运算果果结果将会反馈到占用百分比
	/// @param nbins 默认为 256
	void setNBins( int nbins ) {
		histSize[0] = nbins;
	}

	/// @brief 获取限制高度（箱子数量）
	int getNBins( ) {
		return histSize[0];
	}

	/// @brief 需要显示图像，请参考 getHistogramImage
	/// @brief 计算图像一维(单通道，通道由 channels[0] 指定)直方图
	/// @brief 它并不会返回一个可显示的图像，所以显示出来的话，那么你就很幸运
	/// @result 直方观察图
	cv::Mat getHistogram( const cv::Mat &image ) {
		cv::Mat hist;
		// 计算一维
		cv::calcHist(&image,// 图像序列
			1,// 只有一个图
			channels,// 参考通道标识的数组
			cv::Mat(),// 遮罩，cv::Mat() 标识默认
			hist,// 直方图返回
			1,// 只有一个通道
			histSize,// 箱子数目，下标提取由‘通道数’(通道数 -1)指定
			ranges// 范围数组，是一个二维数组，存储一个或多个具备 2成员元素的数组，下标提取由‘通道数’(通道数 -1)指定
			);

		return hist;
	}


	/// @brief 计算图像一维直方图，并且生成一个可视化的图像
	/// @return 可显示的图像
	cv::Mat getHistogramImage( const cv::Mat &image, int zoom = 1 ) {

		// 先计算直方图，本身并不是一个可视化图像，它仅仅是一个数值观察图
		cv::Mat hist = getHistogram(image);

		// 根据观察图进行直方图的绘制
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

	/*
	 * 静态成员
	 */
public:
	/// @brief 绘制直方观察图到一个图像当中
	/// @param hist 直方图观察图
	/// @param zoom 显示倍数
	/// @return 描述直方图数据的图片
	static cv::Mat getImageOfHistogram( const cv::Mat &hist, int zoom ) {

		// 最大值，表示最大高度
		double maxVal = 0;
		// 最小值
		double minVal = 0;
		cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

		// 获取图片的高度
		int histSize = hist.rows;
		// 图片高度(y轴)
		int yPoint = histSize * zoom;
		// 创建用于显示直方图的图片
		cv::Mat histImg(yPoint, yPoint, CV_8U, cv::Scalar(255));

		// 设置最高为原先的 90%
		int hpt = static_cast<int>(0.9 * histSize);

		// 遍历数组，并且绘制垂直线段
		for ( int h = 0; h < histSize; h++ ) {
			// 获取指定下标的值，该值表示当前行的像素数量
			float binVal = hist.at<float>(h);
			if ( binVal > 0 ) {
				// 获取占用百分比
				double occupancyRate = binVal * hpt / maxVal;
				int intensity = static_cast<int>(occupancyRate);
				int xPoint = h * zoom;
				cv::Point satrtPoint = cv::Point(xPoint, yPoint);
				cv::Point endPoint = cv::Point(xPoint, (histSize - intensity) * zoom);
				cv::line(histImg, satrtPoint, endPoint, cv::Scalar(0), zoom);
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


#endif