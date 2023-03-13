#ifndef CVFUNCTION_H_H_HEAD__FILE__
#define CVFUNCTION_H_H_HEAD__FILE__
#pragma once
#include <QDateTime>
#include "ConverQimageOrCvMat_export.h"
#include <opencv2/opencv.hpp>

namespace cvFunction {

	inline cv::Mat CONVERQIMAGEORCVMAT_EXPORT readImage( const QString &path, int flags = cv::IMREAD_COLOR ) {
		return cv::imread(path.toLocal8Bit().toStdString(), flags);
	}

	inline bool CONVERQIMAGEORCVMAT_EXPORT showMatImg( const cv::Mat &showImg, const QString &name ) {
		if ( showImg.empty() || showImg.rows < 1 || showImg.rows < 1 || showImg.channels() < 1 )
			return false;
		std::string string = name.toLocal8Bit().toStdString();
		cv::namedWindow(string, cv::WINDOW_NORMAL);
		cv::imshow(string, showImg);
		return true;
	}

	inline bool CONVERQIMAGEORCVMAT_EXPORT showMatImg( const cv::Mat &showImg ) {
		QDateTime currentDateTime = QDateTime::currentDateTime();
		QString timeFormStr = currentDateTime.toString("yyyy年MM月dd日 hh : mm : ss . zzz");
		return cvFunction::showMatImg(showImg, timeFormStr);
	}
}

#endif // CVFUNCTION_H_H_HEAD__FILE__