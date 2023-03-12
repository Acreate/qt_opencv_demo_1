#ifndef CVFUNCTION_H_H_HEAD__FILE__
#define CVFUNCTION_H_H_HEAD__FILE__
#pragma once

namespace cvFunction {

	inline cv::Mat readImage( const QString &path, int flags = cv::IMREAD_COLOR ) {
		return cv::imread(path.toLocal8Bit().toStdString(), flags);
	}

	inline bool showMatImg( const cv::Mat &showImg, const std::string &name ) {
		if( showImg.empty() )
			return false;
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, showImg);
		return true;
	}

	inline bool showMatImg( const cv::Mat &showImg, const QString &name ) {
		return cvFunction::showMatImg(showImg, name.toLocal8Bit().toStdString());
	}

	inline bool showMatImg( const cv::Mat &showImg ) {
		return cvFunction::showMatImg(showImg, std::to_string(cv::getTickCount()));
	}
}

#endif // CVFUNCTION_H_H_HEAD__FILE__