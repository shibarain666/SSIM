#include <iostream>
#include "ssim.h"

static const double C1 = 6.5025;
static const double C2 = 58.5225;

ImgInfo::ImgInfo(const char name[], cv::Mat img_src) {
	strcpy(id, name);
	img = img_src;
	return;
}

float getSSIM(cv::Mat image1, cv::Mat image2, int kernel_size) {

	cv::Mat img1_f, img2_f;
	image1.convertTo(img1_f, CV_32F);
	image2.convertTo(img2_f, CV_32F);
	cv::Mat tmp;

	/* Perform mean filtering on image using boxfilter */
	cv::Mat img1_avg, img2_avg;
	cv::boxFilter(img1_f, img1_avg, -1, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
	//GaussianBlur(img1_f, img1_avg, cv::Size(kernel_size, kernel_size), 1.5);
	cv::Mat img1_avg_sqr = img1_avg.mul(img1_avg);
	cv::boxFilter(img2_f, img2_avg, -1, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
	//GaussianBlur(img2_f, img2_avg, cv::Size(kernel_size, kernel_size), 1.5);
	cv::Mat img2_avg_sqr = img2_avg.mul(img2_avg);

	/* Calculate variance map */
	cv::Mat img1_1 = img1_f.mul(img1_f);
	cv::Mat img2_2 = img2_f.mul(img2_f);
	cv::boxFilter(img1_1, tmp, -1, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
	//GaussianBlur(img1_1, tmp, cv::Size(kernel_size, kernel_size), 1.5);
	cv::Mat img1_var = tmp - img1_avg_sqr;
	cv::boxFilter(img2_2, tmp, -1, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
	//GaussianBlur(img2_2, tmp, cv::Size(kernel_size, kernel_size), 1.5);
	cv::Mat img2_var = tmp - img2_avg_sqr;

	/* Calculate covariance map */
	cv::Mat src_mul = img1_f.mul(img2_f);
	cv::Mat avg_mul = img1_avg.mul(img2_avg);
	cv::boxFilter(src_mul, tmp, -1, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1), true, cv::BORDER_DEFAULT);
	//GaussianBlur(src_mul, tmp, cv::Size(kernel_size, kernel_size), 1.5);
	cv::Mat covariance = tmp - avg_mul;

	auto num = ((2 * avg_mul + C1).mul(2 * covariance + C2));
	auto den = ((img1_avg_sqr + img2_avg_sqr + C1).mul(img1_var + img2_var + C2));

	cv::Mat ssim_map;
	cv::divide(num, den, ssim_map);

	cv::Scalar mean_val = cv::mean(ssim_map);
	float mssim = (float)mean_val.val[0];

	return mssim;
}
