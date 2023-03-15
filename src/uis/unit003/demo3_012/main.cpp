#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"
#include "Colorhistogram.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	ColorHistogram hc;
	ContentFinder finder;
	cv::Mat color, color2, imageRoi, shist, lab, result1, result2, image, imageROI, tmp, hsv, colorhist;
	int ch[2] = {1, 2};
	cv::Rect roiRect, roi1, roi2;

	cvFunction::readImage("waves.jpg", color);
	roiRect = cv::Rect(0, 0, 100, 45);
	roi2 = cv::Rect(0, 0, 100, 45);
	cvFunction::readImage("dog.jpg", color2);
	imageROI = color(roi2);

	hc.setSize(256);
	colorhist = hc.getabHistogram(imageROI);
	colorhist.convertTo(tmp,CV_8U, -1.0, 255.0);
	cvFunction::showMatImg(tmp, "截取区域的直方图数据显示");

	finder.setHistogram(colorhist);
	finder.setThreshold(0.05f);
	cv::cvtColor(color, lab, cv::COLOR_BGR2Lab);
	result1 = finder.find(lab, 0, 256.0f, ch);
	cvFunction::showMatImg(result1, "waves.jpg(lab) 查找返回");

	cv::cvtColor(color2, lab, cv::COLOR_BGR2Lab);
	result2 = finder.find(lab, 0, 256.0, ch);
	cvFunction::showMatImg(result2, "dog.jpg(lab) 查找返回");

	cv::rectangle(color, roi2, cv::Scalar(0, 0, 0));
	cvFunction::showMatImg(color, "在 waves.jpg 描述被截取区域");

	int exec = a.exec();
	return exec;
}