#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"
#include "Colorhistogram.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	
	cv::Mat image, imageROI, result1, result2, color, color2, tmp, lab, hsv, colorhist, shist;
	Histogram1D h;
	ContentFinder finder;
	ColorHistogram hc;
	cv::Rect roi1 = cv::Rect(216, 33, 24, 30);
	cv::Rect roi2 = cv::Rect(0, 0, 100, 45);
	int ch[2] = {1, 2};

	
	cvFunction::readImage("waves.jpg", color);
	cvFunction::readImage("dog.jpg", color2);
	
	imageROI = color(roi2);
	hc.setSize(180);
	colorhist = hc.getHueHistogram(imageROI);
	finder.setHistogram(colorhist);
	finder.setThreshold(0.05f);
	cv::cvtColor(color, hsv, cv::COLOR_BGR2HSV);
	ch[0] = 0;
	result1 = finder.find(hsv, 0.0f, 180.0f, ch);
	cvFunction::showMatImg(result1, "使用 hsv 检测 waves.jpg");
	
	cv::cvtColor(color2, hsv, cv::COLOR_BGR2HSV);
	result2 = finder.find(hsv, 0.0f, 180.0f, ch);
	cvFunction::showMatImg(result2, "使用 hsv 检测 dog.jpg");
	
	cvFunction::showMatImg(color, "waves.jpg");
	cvFunction::showMatImg(color2, "dog.jpg");
	int exec = a.exec();
	return exec;
}