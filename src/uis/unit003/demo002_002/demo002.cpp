#include "demo002.h"

void unit002::demo002_002::salt( cv::Mat image, int n ) {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> randomRwo(0, image.rows - 1);
	std::uniform_int_distribution<int> randomCol(0, image.cols - 1);
	int i, j;

	for( int k = 0; k < n; ++k ) {
		// 随机生成图形位置
		i = randomCol(generator);
		j = randomRwo(generator);
		int type = image.type();
		// 灰度图
		if( type == CV_8UC1 ) {
			// 单通道
			image.at<uchar>(j, i) = 255;
			// 3通道彩色
		} else if( type == CV_8UC3 ) {
			// 3 通道图像
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}

}

void unit002::demo002_002::colorReduce( cv::Mat image, int div ) {
	// 获取行
	int nl = image.rows;
	// 每一列中有多少元素
	int nc = image.cols * image.channels(),
		orNc = image.step.buf[0];
	size_t elemSize = image.elemSize();
	for( int j = 0; j < nl; j++ ) {
		// 访问行
		uchar *data = image.ptr(j);
		// 修改列
		for( int i = 0; i < nc; ++i ) {
			data[i] = data[i] / div * div + div / 2;
		}
	}
}