/*------------------------------------------------------------------------------------------*\
This file contains material supporting chapter 4 of the book:
OpenCV3 Computer Vision Application Programming Cookbook
Third Edition
by Robert Laganiere, Packt Publishing, 2016.

This program is free software; permission is hereby granted to use, copy, modify,
and distribute this source code, or portions thereof, for any purpose, without fee,
subject to the restriction that the copyright notice may not be removed
or altered from any source or altered source distribution.
The software is released on an as-is basis and without any warranties of any kind.
In particular, the software is not guaranteed to be fault-tolerant or free from failure.
The author disclaims all warranties with regard to this software, any use,
and any consequent failure, is purely the responsibility of the user.

Copyright (C) 2016 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/

#include <iostream>

#include "CvFunction.h"
using namespace std;

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

#include "histogram.h"
#include "contentFinder.h"
#include "colorhistogram.h"

int main( ) {
	cv::Mat image, imageROI, result1, color, color2, tmp, lab, hsv;
	Histogram1D h;
	ContentFinder finder;
	ColorHistogram hc;
	cv::Rect roi1 = cv::Rect(216, 33, 24, 30);
	cv::Rect roi2 = cv::Rect(0, 0, 100, 45);
	int ch[2] = {1, 2};
	if ( !cvFunction::readImage("waves.jpg", image) )
		return 0;
	imageROI = image(roi1);
	cvFunction::showMatImg(imageROI, "Reference");
	cv::Mat hist = h.getHistogram(imageROI);
	cvFunction::showMatImg(h.getHistogramImage(imageROI), "Reference Hist");
	finder.setHistogram(hist);
	finder.setThreshold(-1.0f);
	result1 = finder.find(image);
	result1.convertTo(tmp,CV_8U, -1.0, 255.0);
	cvFunction::showMatImg(tmp, "Backprojection result");
	finder.setThreshold(0.12f);
	result1 = finder.find(image);
	cv::rectangle(image, roi1, cv::Scalar(0, 0, 0));
	cvFunction::showMatImg(image, "Image");
	cvFunction::showMatImg(result1, "Detection Result");
	cvFunction::readImage("waves.jpg", color);
	imageROI = color(roi2);
	hc.setSize(8);
	cv::Mat shist = hc.getHistogram(imageROI);
	finder.setHistogram(shist);
	finder.setThreshold(0.05f);
	result1 = finder.find(color);
	cvFunction::showMatImg(result1, "Color Detection Result");
	cvFunction::readImage("dog.jpg", color2);
	cvFunction::showMatImg(color2, "Second Image");
	cv::Mat result2 = finder.find(color2);
	cvFunction::showMatImg(result2, "Result color (2)");
	hc.setSize(256);
	cv::Mat colorhist = hc.getabHistogram(imageROI);
	colorhist.convertTo(tmp,CV_8U, -1.0, 255.0);
	cvFunction::showMatImg(tmp, "ab histogram");
	finder.setHistogram(colorhist);
	finder.setThreshold(0.05f);
	cv::cvtColor(color, lab, cv::COLOR_BGR2Lab);
	result1 = finder.find(lab, 0, 256.0f, ch);
	cvFunction::showMatImg(result1, "Result ab (1)");
	cv::cvtColor(color2, lab, cv::COLOR_BGR2Lab);
	result2 = finder.find(lab, 0, 256.0, ch);
	cvFunction::showMatImg(result2, "esult ab (2)");
	cv::rectangle(color, roi2, cv::Scalar(0, 0, 0));
	cvFunction::showMatImg(color, "Color Image");
	hc.setSize(180);
	colorhist = hc.getHueHistogram(imageROI);
	finder.setHistogram(colorhist);
	cv::cvtColor(color, hsv, cv::COLOR_BGR2HSV);

	ch[0] = 0;
	result1 = finder.find(hsv, 0.0f, 180.0f, ch);
	cvFunction::showMatImg(result1, "Result Hue (1)");
	cvFunction::readImage("dog.jpg",color2);
	cv::cvtColor(color2, hsv, cv::COLOR_BGR2HSV);
	result2 = finder.find(hsv, 0.0f, 180.0f, ch);
	cvFunction::showMatImg(result2, "Result Hue (2)");
	cv::waitKey();
	return 0;
}