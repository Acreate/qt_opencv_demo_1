#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>
#include <CvFunction.h>
#include <iostream>

int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	cv::Mat logo = cv::imread("smalllogo.png");
	cv::Mat image = cv::imread("puppy.bmp");
	// roi 所在位置
	cv::Rect roi = cv::Rect(image.cols - logo.cols,
		image.rows - logo.rows,
		logo.cols, logo.rows);
	// 直接拷贝形式
	auto cloneImg = image.clone();
	cv::Mat imageROI(cloneImg,
		roi);
	logo.copyTo(imageROI);
	cvFunction::showMatImg(cloneImg);

	// 遮罩形式
	cloneImg = image.clone();
	imageROI = cloneImg(roi);
	// 掩码必须是灰度图
	cv::Mat gray = logo.clone();
	cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY);
	cv::Mat mask(gray);
	logo.copyTo(imageROI, mask);
	cvFunction::showMatImg(cloneImg);

	// 行列形式
	cloneImg = image.clone();
	int endrow = cloneImg.rows - 1;
	int startrow = endrow - logo.rows;
	imageROI = cloneImg.rowRange(startrow, endrow);
	int endcol = imageROI.cols - 1;
	int startcol = endcol - logo.cols;
	imageROI = imageROI.colRange(startcol, endcol);
	qDebug() << "imageROI.rows = " << imageROI.rows << ", imageROI.cols = " << imageROI.cols;
	logo.copyTo(imageROI);
	cvFunction::showMatImg(cloneImg);

	return a.exec();
}