#ifndef CVFUNCTION_H_H_HEAD__FILE__
#define CVFUNCTION_H_H_HEAD__FILE__
#pragma once

namespace cvFunction {
	inline void showMatImg( const std::string &name, const cv::Mat &showImg ) {
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, showImg);
	}

	inline void showMatImg( const QString &name, const cv::Mat &showImg ) {
		cv::imshow(name.toLocal8Bit().toStdString(), showImg);
	}

	inline void showMatImg( const cv::Mat &showImg ) {
		cvFunction::showMatImg(std::to_string(cv::getTickCount()), showImg);
	}
}

#endif // CVFUNCTION_H_H_HEAD__FILE__