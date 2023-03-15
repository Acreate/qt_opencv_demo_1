#ifndef DEMO002_H_H_HEAD__FILE__
#define DEMO002_H_H_HEAD__FILE__
#pragma once
#include <random>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>


namespace unit002 {
	namespace demo002_005 {
		void salt( cv::Mat image, int n );
		void colorReduce( const cv::Mat &image, cv::Mat &result, int div = 64 );
		void sharpen(const cv::Mat &image, cv::Mat &result);
		void sharpen2D(const cv::Mat &image, cv::Mat &result);
	}
}


#endif // NAMESPACEFUN_H_H_HEAD__FILE__