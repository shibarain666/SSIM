#ifndef SSIM_H
#define SSIM_H

#include <opencv2/core/mat.hpp>

class ImgInfo
{
public:
	char id[10];
	cv::Mat img;
	double average;
	double deviation;
	ImgInfo(const char name[], cv::Mat _img);
	void getAverage();
	void getDeviation();
};

double getCovariance(ImgInfo &a, ImgInfo &b);
double getSSIM(ImgInfo &a, ImgInfo &b, double c1, double c2, double cov);

#endif
