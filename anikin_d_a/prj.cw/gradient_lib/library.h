#ifndef CW_LIB_LIBRARY_H
#define CW_LIB_LIBRARY_H
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <cmath>
#include <typeinfo>
#include <fstream>
#include <string>

cv::Mat ConvertToFloat(cv::Mat img1);
cv::Mat GetHsxMatrix();
cv::Mat GetHsyMatrix();
cv::Mat CreateImgXMatrix(cv::Mat img, cv::Mat Hsx);
cv::Mat CreateImgYMatrix(cv::Mat img, cv::Mat Hsy);
cv::Mat CreateIbxMatrix(cv::Mat imgx);
cv::Mat CreateIbyMatrix(cv::Mat imgy);
cv::Mat CreateIgxMatrix(cv::Mat imgx);
cv::Mat CreateIgyMatrix(cv::Mat imgy);
cv::Mat CreateIrxMatrix(cv::Mat imgx);
cv::Mat CreateIryMatrix(cv::Mat imgy);
std::vector<cv::Mat> GetAllMatrix(cv::Mat img);
std::vector<std::vector<float>> GetE(std::vector<cv::Mat> allmatrix);
std::vector<std::vector<float>> GetF(std::vector<cv::Mat> allmatrix);
cv::Mat GradientInGray(std::vector<std::vector<float>> E, cv::Mat img);

#endif //CW_LIB_LIBRARY_H
