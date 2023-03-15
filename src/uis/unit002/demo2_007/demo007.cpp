#include "demo007.h"

void unit002::demo002_007::wave( const cv::Mat &image, cv::Mat &result ) {
	cv::Mat srcX(image.rows, image.cols, CV_32F);
	cv::Mat srcY(image.rows, image.cols, CV_32F);
	for( int i = 0; i < image.rows; ++i ) {
		for( int j = 0; j < image.cols; ++j ) {
			srcX.at<float>(i, j) = j;// 不更改纵向元素
			srcY.at<float>(i, j) = i + 5 * sin(j / 10.0);// 横向元素改为正弦曲线
		}
	}
	// 应用映射参数
	cv::remap(image,// 源
		result,// 目标
		srcX,// x 映射
		srcY,// y 映射
		cv::INTER_LINEAR//填补方法
		);
}

void unit002::demo002_007::filp( const cv::Mat &image, cv::Mat &result ) {
	cv::Mat srcX(image.rows, image.cols, CV_32F);
	cv::Mat srcY(image.rows, image.cols, CV_32F);
	for( int i = 0; i < image.rows; ++i ) {
		for( int j = 0; j < image.cols; ++j ) {
			srcX.at<float>(i, j) = image.cols - j - 1;// 纵向元素翻转
			srcY.at<float>(i, j) = i;// 不更改横向元素
		}
	}
	// 应用映射参数
	cv::remap(image,// 源
		result,// 目标
		srcX,// x 映射
		srcY,// y 映射
		cv::INTER_LINEAR//填补方法
		);
}