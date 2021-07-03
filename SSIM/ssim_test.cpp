#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ssim.h"

int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cout << "wrong arguments number." << std::endl;
		std::cout << "Ex: .\\SSIM 101.jpg" << std::endl;
		return -1;
	}
	
	cv::Mat img_src = cv::imread(argv[1], cv::IMREAD_COLOR);
	cv::Mat img_grayscale;
	cv::cvtColor(img_src, img_grayscale, cv::COLOR_BGR2GRAY);

	int rows = img_src.rows;
	int cols = img_src.cols;

	cv::Mat img_resized;
	resize(img_grayscale, img_resized, cv::Size(cols/2, rows/2), CV_INTER_LINEAR);
	resize(img_resized, img_resized, cv::Size(cols, rows), CV_INTER_LINEAR);

	cv::imwrite("source_image.jpg", img_grayscale);
	cv::imwrite("resized_img.jpg", img_resized);
	cv::imshow("source image", img_grayscale);
	cv::imshow("resized image", img_resized);

	ImgInfo img_x("X", img_grayscale);
	ImgInfo img_y("Y", img_resized);

	float ssim = getSSIM(img_x.img, img_y.img, 11);
	
	std::cout << "SSIM: " << ssim << std::endl;

	cv::waitKey(0);
	return 0;
}
