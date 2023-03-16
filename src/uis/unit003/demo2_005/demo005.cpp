#include "demo005.h"

void unit002::demo002_005::salt( cv::Mat image, int n ) {
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

void unit002::demo002_005::colorReduce( const cv::Mat &image, cv::Mat &result, int div ) {
	result.create(image.rows, image.cols, image.type());
	// 获取行
	int nl = image.rows;
	// 每一列中有多少元素
	int nc = image.cols * image.channels(),
		orNc = image.step.buf[0];
	size_t elemSize = image.elemSize();
	// div 必须是 2 的幂
	int n = static_cast<int>(log(static_cast<double>(div) / log(2.0) + 0.5));
	// 用来截取像素值的掩码
	uchar mask = 0xff << n;// 如果 div = 16， mask = 0xf0
	uchar div2 = div >> 1;// div = div/2
	// 常量迭代器，表示不可写
	cv::MatConstIterator_<cv::Vec3b> inIt = image.begin<cv::Vec3b>();
	cv::MatConstIterator_<cv::Vec3b> inEnd = image.end<cv::Vec3b>();
	// 常规迭代器，表示可写可读
	cv::Mat_<cv::Vec3b>::iterator outIt = result.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator outEnd = result.end<cv::Vec3b>();

	for( ; inIt != inEnd; ++inIt ) {
		(*outIt)[0] = (*inIt)[0] / div * div + div2;
		(*outIt)[1] = (*inIt)[1] / div * div + div2;
		(*outIt)[2] = (*inIt)[2] / div * div + div2;
		++outIt;
	}

}

void unit002::demo002_005::sharpen( const cv::Mat &image, cv::Mat &result ) {
	result.create(image.rows, image.cols, image.type());
	int nchannels = image.channels();
	for( int j = 1; j < image.rows - 1; ++j ) {
		const uchar *previous = image.ptr<const uchar>(j - 1);// 上一行
		const uchar *current = image.ptr<const uchar>(j);// 当前行
		const uchar *next = image.ptr<const uchar>(j + 1);// 下一行
		uchar *outPut = result.ptr<uchar>(j);// 输出行
		for( int i = nchannels; i < (image.cols - 1) * nchannels; ++i ) {
			// 锐化算法
			*outPut ++ = cv::saturate_cast<uchar>(5 * current[i] - current[i - nchannels] - current[i + nchannels] - previous[i] - next[i]);
		}
	}
	// 边缘处理
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void unit002::demo002_005::sharpen2D( const cv::Mat &image, cv::Mat &result ) {
	// 构建内核
	cv::Mat kernel(3, 3,CV_32F, cv::Scalar(0));
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;
	cv::filter2D(image, result, image.depth(), kernel);
}