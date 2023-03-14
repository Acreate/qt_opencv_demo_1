#include <QGuiApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CvFunction.h"
#include "Histogram.h"
#include "ContentFinder.h"
#include "Colorhistogram.h"


int main( int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);
	// 获取输入
	cv::Mat image;
	if ( !cvFunction::readImage("waves.jpg", image) )
		return 0;

	// 定义感兴趣区域
	cv::Mat imageROI;
	// 获取天空部分
	imageROI = image(cv::Rect(216, 33, 24, 30));
	// 显示感兴趣区域
	cvFunction::showMatImg(imageROI, "Reference");
	// 1 维直方图
	Histogram1D h;
	cv::Mat hist = h.getHistogram(imageROI);
	cv::Mat histogramImage = h.getHistogramImage(imageROI);
	cvFunction::showMatImg(histogramImage, "Reference Hist");

	// 创建探险对象
	ContentFinder finder;

	// 设置直方图到探险对象当中
	finder.setHistogram(hist);
	finder.setThreshold(-1.0f);

	// 获取背景
	cv::Mat result1;
	result1 = finder.find(image);

	// 显示投影
	cv::Mat tmp;
	result1.convertTo(tmp,CV_8U, -1.0, 255.0);
	cvFunction::showMatImg(tmp, "Backprojection result");

	// Get binary back-projection
	finder.setThreshold(0.12f);
	result1 = finder.find(image);

	// Draw a rectangle around the reference area
	cv::rectangle(image, cv::Rect(216, 33, 24, 30), cv::Scalar(0, 0, 0));

	// Display image
	cvFunction::showMatImg(image, "Image");

	// Display result
	cvFunction::showMatImg(result1, "Detection Result");

	// Load color image
	ColorHistogram hc;
	cv::Mat color;
	cvFunction::readImage("waves.jpg", color);

	// extract region of interest
	imageROI = color(cv::Rect(0, 0, 100, 45));// blue sky area

	// Get 3D colour histogram (8 bins per channel)
	hc.setSize(8);// 8x8x8
	cv::Mat shist = hc.getHistogram(imageROI);

	// set histogram to be back-projected
	finder.setHistogram(shist);
	finder.setThreshold(0.05f);

	// Get back-projection of color histogram
	result1 = finder.find(color);

	cvFunction::showMatImg(result1, "Color Detection Result");

	// Second color image
	cv::Mat color2;
	cvFunction::readImage("dog.jpg", color2);
	cvFunction::showMatImg(color2, "Second Image");

	// Get back-projection of color histogram
	cv::Mat result2 = finder.find(color2);
	cvFunction::showMatImg(result2, "Result color (2)");

	// Get ab color histogram
	hc.setSize(256);// 256x256
	cv::Mat colorhist = hc.getabHistogram(imageROI);

	// display 2D histogram
	colorhist.convertTo(tmp,CV_8U, -1.0, 255.0);
	cvFunction::showMatImg(tmp, "ab histogram");

	// set histogram to be back-projected
	finder.setHistogram(colorhist);
	finder.setThreshold(0.05f);

	// Convert to Lab space
	cv::Mat lab;
	cv::cvtColor(color, lab, CV_BGR2Lab);

	// Get back-projection of ab histogram
	int ch[2] = {1, 2};
	result1 = finder.find(lab, 0, 256.0f, ch);

	cvFunction::showMatImg(result1, "Result ab (1)");

	// Second colour image
	cv::cvtColor(color2, lab, CV_BGR2Lab);

	// Get back-projection of ab histogram
	result2 = finder.find(lab, 0, 256.0, ch);

	cvFunction::showMatImg(result2, "Result ab (2)");

	// Draw a rectangle around the reference sky area
	cv::rectangle(color, cv::Rect(0, 0, 100, 45), cv::Scalar(0, 0, 0));
	cvFunction::showMatImg(color, "Color Image");


	// Get Hue colour histogram
	hc.setSize(180);// 180 bins
	colorhist = hc.getHueHistogram(imageROI);

	// set histogram to be back-projected
	finder.setHistogram(colorhist);

	// Convert to HSV space
	cv::Mat hsv;
	cv::cvtColor(color, hsv, CV_BGR2HSV);

	// Get back-projection of hue histogram
	ch[0] = 0;
	result1 = finder.find(hsv, 0.0f, 180.0f, ch);

	cvFunction::showMatImg(result1, "Result Hue (1)");

	// Second colour image
	cvFunction::readImage("dog.jpg", color2);

	// Convert to HSV space
	cv::cvtColor(color2, hsv, CV_BGR2HSV);

	// Get back-projection of hue histogram
	result2 = finder.find(hsv, 0.0f, 180.0f, ch);

	cvFunction::showMatImg(result2, "Result Hue (2)");

	int exec = a.exec();


	return exec;
}