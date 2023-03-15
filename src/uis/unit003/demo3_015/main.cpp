
#include <QGuiApplication>

#include <iostream>
#include "CvFunction.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram.h"
#include "contentFinder.h"
#include "colorhistogram.h"

int main(int argc, char *argv[] ) {
	QGuiApplication a(argc, argv);

	const int exec = a.exec();
	return exec;
}