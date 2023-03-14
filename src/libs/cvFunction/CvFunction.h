#ifndef CVFUNCTION_H_H_HEAD__FILE__
#define CVFUNCTION_H_H_HEAD__FILE__
#pragma once
#include <QDateTime>
#include "CvFunction_export.h"
#include <opencv2/opencv.hpp>

namespace cvFunction {

	/// @brief 写入文件
	/// @param path 写入路径
	/// @param image 写入的图片
	/// @param params 写入参数，他是配对的存在， ([选项1， 选项1的值 ,[选项2， 选项2的值 , ...]] )
	/// @return 成功返回 true，失败返回 false
	CVFUNCTION_EXPORT inline bool writeImage( const QString &path, const cv::Mat &image = cv::Mat(), const std::vector<int>& params = std::vector<int>() ) {
		return cv::imwrite(path.toLocal8Bit().toStdString(), image);
	}

	/// @brief 从磁盘读取一张图片，若成功，则赋值给 outMat
	/// @param path 路径
	/// @param outMat 返回图像，只有成功返回被改变
	/// @param flags 读取方式，会根据方式进行读取并且进行格式化
	/// @return 成功返回 true
	CVFUNCTION_EXPORT inline bool readImage( const QString &path, cv::Mat &outMat, int flags = cv::IMREAD_COLOR ) {
		auto result = cv::imread(path.toLocal8Bit().toStdString(), flags);
		if ( result.empty() )
			return false;
		outMat = result;
		return true;
	}

	CVFUNCTION_EXPORT inline bool showMatImg( const cv::Mat &showImg, const QString &name ) {
		if ( showImg.empty() || showImg.rows < 1 || showImg.rows < 1 || showImg.channels() < 1 )
			return false;
		std::string string = name.toLocal8Bit().toStdString();
		cv::namedWindow(string, cv::WINDOW_NORMAL);
		cv::imshow(string, showImg);
		return true;
	}

	CVFUNCTION_EXPORT inline bool showMatImg( const cv::Mat &showImg ) {
		QDateTime currentDateTime = QDateTime::currentDateTime();
		QString timeFormStr = currentDateTime.toString("yyyy年MM月dd日 hh : mm : ss . zzz");
		return cvFunction::showMatImg(showImg, timeFormStr);
	}
}

#endif // CVFUNCTION_H_H_HEAD__FILE__