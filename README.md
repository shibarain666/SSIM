# SSIM
## Introduction
* Implementation of SSIM(Structural Similarity Index)
* Use boxfilter for average operation, for sample image 101.jpg's result(result = 0.903216), it's close to MATLAB(result = 0.8768). Gaussian way for average operation is also provided, the result will be more close to MATLAB result.
* Ref: Wang, Zhou; Bovik, A.C.; Sheikh, H.R.; Simoncelli, E.P. (2004-04-01). "Image quality assessment: from error visibility to structural similarity". IEEE Transactions on Image Processing. 13 (4): 600–612.
* Input: Color image, Output: SSIM result