#ifndef IMAGECOMPARATOR_H_H_HEAD__FILE__
#define IMAGECOMPARATOR_H_H_HEAD__FILE__
#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Colorhistogram.h"
#include "ImageComparator_export.h"

class IMAGECOMPARATOR_EXPORT ImageComparator {

private:
	/// @brief 基准直方图
	cv::Mat refH;
	/// @brief 输入图像的直方图
	cv::Mat inputH;
	/// @brief 直方图操作对象
	ColorHistogram hist;
	/// @brief 每个颜色通道使用的箱子数量
	int nBins;

public:
	ImageComparator( ) : nBins(8) { }

	// 设置箱子数量
	void setNumberOfBins( int bins ) {
		nBins = bins;
	}

	int getNumberOfBins( ) {
		return nBins;
	}

	// 设置并计算基准图像的直方图
	void setReferenceImage( const cv::Mat &image ) {
		hist.setSize(nBins);
		refH = hist.getHistogram(image);
	}

	// 用 BGR 直方图比较图像
	double compare( const cv::Mat &image ) {
		inputH = hist.getHistogram(image);
		// 用交叉法比较直方图
		return cv::compareHist(refH, inputH, cv::HISTCMP_INTERSECT);
	}
};


#endif