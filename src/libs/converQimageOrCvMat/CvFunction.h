#ifndef CVFUNCTION_H_H_HEAD__FILE__
#define CVFUNCTION_H_H_HEAD__FILE__
#pragma once
#include <QDateTime>

namespace cvFunction {

	inline cv::Mat readImage( const QString &path, int flags = cv::IMREAD_COLOR ) {
		return cv::imread(path.toLocal8Bit().toStdString(), flags);
	}

	inline bool showMatImg( const cv::Mat &showImg, const QString &name ) {
		if( showImg.empty() )
			return false;
		std::string string = name.toLocal8Bit().toStdString();
		cv::namedWindow(string, cv::WINDOW_NORMAL);
		cv::imshow(string, showImg);
		return true;
	}

	inline bool showMatImg( const cv::Mat &showImg ) {
		QDateTime currentDateTime = QDateTime::currentDateTime();
		QString timeFormStr = currentDateTime.toString("yyyy年MM月dd日 hh : mm : ss . zzz");
		return cvFunction::showMatImg(showImg, timeFormStr);
	}
}

#endif // CVFUNCTION_H_H_HEAD__FILE__