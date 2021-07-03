#ifndef SSIM_H_
#define SSIM_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

/* for future use */
class ImgInfo
{
public:
	char id[10];
	cv::Mat img;
	ImgInfo(const char name[], cv::Mat _img);
};

float getSSIM(cv::Mat image1, cv::Mat image2, int kernel_size);

#endif    /* SSIM_H_ */
