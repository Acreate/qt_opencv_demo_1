#ifndef CVFUNCTION_H_H_HEAD__FILE__
#define CVFUNCTION_H_H_HEAD__FILE__
#pragma once

namespace cvFunction {
	inline void showMatImg( const cv::Mat &showImg, const std::string &name ) {
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, showImg);
	}

	inline void showMatImg( const cv::Mat &showImg, const QString &name ) {
		cv::imshow(name.toLocal8Bit().toStdString(), showImg);
	}

	inline void showMatImg( const cv::Mat &showImg ) {
		cvFunction::showMatImg(showImg, std::to_string(cv::getTickCount()));
	}
}

#endif // CVFUNCTION_H_H_HEAD__FILE__