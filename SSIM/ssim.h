#ifndef SSIM_H_
#define SSIM_H_

#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class ImgInfo
{
public:
	char id[10];
	cv::Mat img;
	ImgInfo(const char name[], cv::Mat _img);
};

float getSSIM(cv::Mat a, cv::Mat b, int kernel_size);

#endif    /* SSIM_H_ */
