#ifndef COLORHISTOGRAM_H_H_HEAD__FILE__
#define COLORHISTOGRAM_H_H_HEAD__FILE__
#pragma once
#include "ColorHistogram_export.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

/// @brief 处理彩色图像的直方图类
class COLORHISTOGRAM_EXPORT ColorHistogram {
private:
	int histSize[3];// 每个维度的大小（箱子数量）
	float hranges[2];// 值的范围（三个维度用同一个值）
	const float *ranges[3];// 每个维度的范围
	int channels[3];// 需要处理的通道

public:
	/// @brief 准备用于彩色图像的默认参数
	ColorHistogram( ) {
		// 每个维度的大小和范围是相等的
		histSize[0] = histSize[1] = histSize[2] = 256;
		hranges[0] = 0.0;// BRG 范围 [0,256]，[0] 记录最小
		hranges[1] = 255.0;// BRG 范围 [0,256]，[1] 记录最大
		ranges[0] = hranges;//类中，所有通道的范围都相等
		ranges[1] = hranges;
		ranges[2] = hranges;
		channels[0] = 0;// B 通道所在元素的下标偏移
		channels[1] = 1;// G 通道所在元素的下标偏移
		channels[2] = 2;// R 通道所在元素的下标偏移
	}

	// 设置维度的大小
	void setSize( int size ) {
		// 大小相同
		histSize[0] = histSize[1] = histSize[2] = size;
	}

	// 计算直方图
	cv::Mat getHistogram( const cv::Mat &image ) {
		// 切分通道，每个通道都需要获取其匹配的直方图
		std::vector<cv::Mat> bgr_planes;
		cv::split(image, bgr_planes);
		const float *range{ranges[0]};
		cv::Mat b_hist, g_hist, r_hist;
		cv::calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize[0], &range, true, false);
		cv::calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize[1], &range, true, false);
		cv::calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize[2], &range, true, false);

		//归一化
		int hist_w = 500;//直方图的图像的宽
		int hist_h = 300;//直方图的图像的高
		int nHistSize = 256;
		int bin_w = cvRound((double)hist_w / nHistSize);//区间
		cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));//绘制直方图显示的图像
		cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());//归一化
		cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
		cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
		for ( int i = 1; i < nHistSize; i++ ) {
			//绘制蓝色分量直方图
			cv::line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),
				cv::Point((i) * bin_w, hist_h - cvRound(b_hist.at<float>(i))), cv::Scalar(255, 0, 0), 2);
			//绘制绿色分量直方图
			cv::line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
				cv::Point((i) * bin_w, hist_h - cvRound(g_hist.at<float>(i))), cv::Scalar(0, 255, 0), 2);
			//绘制红色分量直方图
			cv::line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
				cv::Point((i) * bin_w, hist_h - cvRound(r_hist.at<float>(i))), cv::Scalar(0, 0, 255), 2);
		}
		return histImage;
	}

	// 使用 OpenCV 数据结构实现
	cv::SparseMat getSparseHistogram( const cv::Mat &image ) {

		cv::SparseMat hist(3,// 维数
			histSize,// 限制大小
			CV_32F);

		// BGR color histogram
		hranges[0] = 0.0;// BRG range
		hranges[1] = 256.0;
		channels[0] = 0;// the three channels 
		channels[1] = 1;
		channels[2] = 2;

		// Compute histogram
		cv::calcHist(&image,
			1,// histogram of 1 image only
			channels,// the channel used
			cv::Mat(),// no mask is used
			hist,// the resulting histogram
			3,// it is a 3D histogram
			histSize,// number of bins
			ranges,// pixel value range
			true,
			false
			);

		return hist;
	}

	cv::Mat getNormalHistogram( const cv::Mat &image ) {
		cv::Mat hist;
		// 计算直方图
		cv::calcHist(&image, 1,// 单幅图像的直方图
			channels,// 用到的通道
			cv::Mat(),// 不使用掩码
			hist,// 得到的直方图
			3,// 这是一个三维直方图
			histSize,// 箱子数量
			ranges// 像素值的范围
			);
		return hist;
	}
};


#endif // COLORHISTOGRAM_H_H_HEAD__FILE__