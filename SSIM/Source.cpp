#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ssim.h"

int main(int argc, char *argv[]) {

	cv::Mat img_src = cv::imread("101.jpg", cv::IMREAD_COLOR);
	cv::Mat img_grayscale;
	cv::cvtColor(img_src, img_grayscale, cv::COLOR_BGR2GRAY);

	cv::Mat img_resized;
	resize(img_grayscale, img_resized, cv::Size(240, 320), CV_INTER_LINEAR);
	resize(img_resized, img_resized, cv::Size(480, 640), CV_INTER_LINEAR);

	cv::imwrite("source_image.jpg", img_grayscale);
	cv::imwrite("resized_img.jpg", img_resized);
	cv::imshow("source image", img_grayscale);
	cv::imshow("resized image", img_resized);

	ImgInfo img_x("X", img_grayscale);
	ImgInfo img_y("Y", img_resized);
	img_x.getAverage();
	img_x.getDeviation();
	img_y.getAverage();
	img_y.getDeviation();

	double c1 = pow(0.01 * 255.0, 2);
	double c2 = pow(0.03 * 255.0, 2);

	double cov = getCovariance(img_x, img_y);
	double ssim = getSSIM(img_x, img_y, c1, c2, cov);
	std::cout << "SSIM: " << ssim << std::endl;

	cv::waitKey(0);
	return 0;
}

