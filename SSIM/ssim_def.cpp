#include <iostream>
#include "ssim.h"

ImgInfo::ImgInfo(const char name[], cv::Mat _img) {
	strcpy(id, name);
	img = _img;
	return;
}

void ImgInfo::getAverage() {
	double total = 0;
	for (int j = 0; j < img.rows; j++) {
		uchar* ptr = img.ptr<uchar>(j);
		for (int i = 0; i < img.cols; i++) {
			total += ptr[i];
		}
	}
	average = total / (img.rows*img.cols);
	std::cout << id << "'s average: "<< average << std::endl;
}

void ImgInfo::getDeviation() {
	double total = 0;
	for (int j = 0; j < img.rows; j++) {
		uchar* ptr = img.ptr<uchar>(j);
		for (int i = 0; i < img.cols; i++) {
			total += pow((ptr[i] - average), 2);
		}
	}
	deviation = pow(total / (img.rows*img.cols - 1), 0.5);
	std::cout << id << "'s deviation: " << deviation << std::endl;
}

double getCovariance(ImgInfo &a, ImgInfo &b) {

	double total = 0;
	double covariance = 0;
	int rows = a.img.rows;
	int cols = a.img.cols;

	for (int j = 0; j < rows; j++) {
		uchar* ptr_a = a.img.ptr<uchar>(j);
		uchar* ptr_b = b.img.ptr<uchar>(j);
		for (int i = 0; i < cols; i++) {
			total += (ptr_a[i] - a.average)*(ptr_b[i] - b.average);
		}
	}
	covariance = total / (rows*cols - 1);
	std::cout << "covariance: " << covariance << std::endl;

	return covariance;
}

double getSSIM(ImgInfo &a, ImgInfo &b, double c1, double c2, double cov) {

	double num;
	double den;
	num = (2.*a.average*b.average + c1) * (2.*cov + c2);
	den = (pow(a.average, 2) + pow(b.average, 2) + c1) * (pow(a.deviation, 2) + pow(b.deviation, 2) + c2);
	
	return num / den;
}
