#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>
#include <random>

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat image;
	if ( ! cvFunction::readImage("boldt.jpg", image, 1) )
		return -1;
	cvFunction::showMatImg(image);
	cv::Rect rectangle(5, 70, 260, 120);
	cv::Mat result;// 分割结果(四种可能的值)
	cv::Mat bgModel, fgModel;// 模型（内部使用）
	// GRabCut 分割算法
	cv::grabCut(image,// 输入
		result,// 输出
		rectangle,// 描述矩形
		bgModel, fgModel,// 模型
		5,// 迭代次数
		cv::GC_INIT_WITH_RECT// 使用类型(带边框的矩形模型)
		);
	// 取得标记为“可能属于前景”的像素
	cv::Mat compareResult;
	cv::compare(result, cv::GC_PR_FGD, compareResult, cv::CMP_EQ);
	// 生成输出图像
	cv::Mat foreground(image.size(),CV_8UC3, cv::Scalar(255, 255, 255));
	image.copyTo(foreground, result);// 不复制背景像素
	cvFunction::showMatImg(foreground);
	return a.exec();
}