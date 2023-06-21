#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <cmath>
#include <typeinfo>
#include <fstream>
#include <string>
#include "library.h"

/**
 * @brief Конвертирует значения матрицы изображения img1 в float
 * @param img1 Исходное изображение
 * @return Возвращает матрицу изображения с конвертированными значениями cv::Mat img1
 */
cv::Mat ConvertToFloat(cv::Mat img1){
    cv::Mat img;
    img1.convertTo(img, CV_32FC3 );
    return img;
}

/**
 * @brief Формирует матрицу Sobel-фильтра Hsx
 * @return Возвращает матрицу cv::Mat Hsx
 */
cv::Mat GetHsxMatrix(){
    cv::Mat Hsx = cv::Mat(3, 3, CV_32FC1);

    std::vector<std::vector<float>> data_x = {{-1,0,1},{-2,0,2},{-1,0,1}};

    for (int i = 0; i < Hsx.rows; i++){
        for (int j = 0; j < Hsx.cols; j++){
            Hsx.at<float>(i, j) = data_x[i][j];
        }
    }
    Hsx = 0.125 * Hsx;

    return Hsx;
}

/**
 * @brief Формирует матрицу Sobel-фильтра Hsy
 * @return Возвращает матрицу cv::Mat Hsy
 */
cv::Mat GetHsyMatrix(){
    cv::Mat Hsy = cv::Mat(3, 3, CV_32FC1);

    std::vector<std::vector<float>> data_y = {{-1,-2,-1},{0,0,0},{1,2,1}};

    for (int i = 0; i < Hsy.rows; i++){
        for (int j = 0; j < Hsy.cols; j++){
            Hsy.at<float>(i, j) = data_y[i][j];
        }
    }
    Hsy = 0.125 * Hsy;

    return Hsy;
}

/**
 * @brief Умножает матрицу изображения img на матрицу Hsx
 * @param img Исходное изображение cv::Mat img
 * @param Hsx Матрица cv::Mat Hsx
 * @return Возвращает преобразованную матрицу cv::Mat imgx
 */
cv::Mat CreateImgXMatrix(cv::Mat img, cv::Mat Hsx){
    img = ConvertToFloat(img);
    cv::Mat temp = cv::Mat(1, 3, CV_32FC1);
    cv::Mat imgx;
    img.copyTo(imgx);


    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < imgx.cols; j++){
            temp.at<float>(0, 0) = imgx.at<cv::Vec3f>(i, j)[0];
            temp.at<float>(0, 1) = imgx.at<cv::Vec3f>(i, j)[1];
            temp.at<float>(0, 2) = imgx.at<cv::Vec3f>(i, j)[2];
            cv::Mat res = temp * Hsx;
            imgx.at<cv::Vec3f>(i, j)[0] = res.at<float>(0, 0);
            imgx.at<cv::Vec3f>(i, j)[1] = res.at<float>(0, 1);
            imgx.at<cv::Vec3f>(i, j)[2] = res.at<float>(0, 2);
        }
    }

    return imgx;
}

/**
 * @brief Умножает матрицу изображения img на матрицу Hsy
 * @param img Исходное изображение cv::Mat img
 * @param Hsy Матрица cv::Mat Hsy
 * @return Возвращает преобразованную матрицу cv::Mat imgy
 */
cv::Mat CreateImgYMatrix(cv::Mat img, cv::Mat Hsy){
    img = ConvertToFloat(img);
    cv::Mat temp = cv::Mat(1, 3, CV_32FC1);
    cv::Mat imgy;
    img.copyTo(imgy);

    for (int i = 0; i < imgy.rows; i++){
        for (int j = 0; j < imgy.cols; j++){
            temp.at<float>(0, 0) = imgy.at<cv::Vec3f>(i, j)[0];
            temp.at<float>(0, 1) = imgy.at<cv::Vec3f>(i, j)[1];
            temp.at<float>(0, 2) = imgy.at<cv::Vec3f>(i, j)[2];
            cv::Mat res = temp * Hsy;
            imgy.at<cv::Vec3f>(i, j)[0] = res.at<float>(0, 0);
            imgy.at<cv::Vec3f>(i, j)[1] = res.at<float>(0, 1);
            imgy.at<cv::Vec3f>(i, j)[2] = res.at<float>(0, 2);
        }
    }

    return imgy;
}

/**
 * @brief Формирует из матрицы imgx матрицу Ibx по цветовой плоскости Ib
 * @param imgx Исходное изображение cv::Mat imgx
 * @return Возвращает матрицу cv::Mat Ibx
 */
cv::Mat CreateIbxMatrix(cv::Mat imgx){
    cv::Mat Ibx(imgx.rows, imgx.cols, CV_32FC1);

    for (int i = 0; i < Ibx.rows; i++){
        for (int j = 0; j < Ibx.cols; j++){
            Ibx.at<float>(i, j) = imgx.at<cv::Vec3f>(i,j)[0];
        }
    }

    return Ibx;
}

/**
 * @brief Формирует из матрицы imgy матрицу Iby по цветовой плоскости Ib
 * @param imgy Исходное изображение cv::Mat imgy
 * @return Возвращает матрицу cv::Mat Iby
 */
cv::Mat CreateIbyMatrix(cv::Mat imgy){
    cv::Mat Iby(imgy.rows, imgy.cols, CV_32FC1);

    for (int i = 0; i < Iby.rows; i++){
        for (int j = 0; j < Iby.cols; j++){
            Iby.at<float>(i, j) = imgy.at<cv::Vec3f>(i,j)[0];
        }
    }

    return Iby;
}

/**
 * @brief Формирует из матрицы imgx матрицу Igx по цветовой плоскости Ig
 * @param imgx Исходное изображение cv::Mat imgx
 * @return Возвращает матрицу cv::Mat Igx
 */
cv::Mat CreateIgxMatrix(cv::Mat imgx){
    cv::Mat Igx(imgx.rows, imgx.cols, CV_32FC1);

    for (int i = 0; i < Igx.rows; i++){
        for (int j = 0; j < Igx.cols; j++){
            Igx.at<float>(i, j) = imgx.at<cv::Vec3f>(i,j)[1];
        }
    }
    return Igx;
}

/**
 * @brief Формирует из матрицы imgy матрицу Igy по цветовой плоскости Ig
 * @param imgy Исходное изображение cv::Mat imgy
 * @return Возвращает матрицу cv::Mat Igy
 */
cv::Mat CreateIgyMatrix(cv::Mat imgy){
    cv::Mat Igy(imgy.rows, imgy.cols, CV_32FC1);

    for (int i = 0; i < Igy.rows; i++){
        for (int j = 0; j < Igy.cols; j++){
            Igy.at<float>(i, j) = imgy.at<cv::Vec3f>(i,j)[1];
        }
    }
    return Igy;
}

/**
 * @brief Формирует из матрицы imgx матрицу Irx по цветовой плоскости Ir
 * @param imgx Исходное изображение cv::Mat imgx
 * @return Возвращает матрицу cv::Mat Irx
 */
cv::Mat CreateIrxMatrix(cv::Mat imgx){
    cv::Mat Irx(imgx.rows, imgx.cols, CV_32FC1);

    for (int i = 0; i < Irx.rows; i++){
        for (int j = 0; j < Irx.cols; j++){
            Irx.at<float>(i, j) = imgx.at<cv::Vec3f>(i,j)[2];
        }
    }
    return Irx;
}

/**
 * @brief Формирует из матрицы imgy матрицу Iry по цветовой плоскости Ir
 * @param imgy Исходное изображение cv::Mat imgy
 * @return Возвращает матрицу cv::Mat Iry
 */
cv::Mat CreateIryMatrix(cv::Mat imgy) {
    cv::Mat Iry(imgy.rows, imgy.cols, CV_32FC1);

    for (int i = 0; i < Iry.rows; i++) {
        for (int j = 0; j < Iry.cols; j++) {
            Iry.at<float>(i, j) = imgy.at<cv::Vec3f>(i, j)[2];
        }
    }
    return Iry;
}

/**
 * @brief Формирует вектор со всеми матрицами, необходимыми для вычисления локальных градиентов
 * @param img исходное изображение cv::Mat img
 * @return Возвращает std::vector<cv::Mat> allmatrix, содержащий все необходимые матрицы
 */
std::vector<cv::Mat> GetAllMatrix(cv::Mat img){
    std::vector<cv::Mat> allmatrix;

    cv::Mat Hsx = GetHsxMatrix();
    cv::Mat Hsy = GetHsyMatrix();

    cv::Mat imgx = CreateImgXMatrix(img, Hsx);
    cv::Mat imgy = CreateImgYMatrix(img, Hsy);

    cv::Mat Ibx = CreateIbxMatrix(imgx);
    cv::Mat Iby = CreateIbyMatrix(imgy);
    cv::Mat Igx = CreateIgxMatrix(imgx);
    cv::Mat Igy = CreateIgyMatrix(imgy);
    cv::Mat Irx = CreateIrxMatrix(imgx);
    cv::Mat Iry = CreateIryMatrix(imgy);

    allmatrix.push_back(img);
    allmatrix.push_back(Ibx);
    allmatrix.push_back(Iby);
    allmatrix.push_back(Igx);
    allmatrix.push_back(Igy);
    allmatrix.push_back(Irx);
    allmatrix.push_back(Iry);

    return allmatrix;
}

/**
 * @brief Вычисляет численные значения локальных градиентов изображения
 * @param allmatrix std::vector<cv::Mat> allmatrix со всеми необходимыми матрицами
 * @return Возвращает вектор со значениями локальных градиентов std::vector<std::vector<float>> E
 */
std::vector<std::vector<float>> GetE(std::vector<cv::Mat> allmatrix){
    std::vector<std::vector<float>> E;
    for (int i = 0; i < allmatrix[0].rows; i++) {
        std::vector<float> temp_e;
        E.push_back(temp_e);

        for (int j = 0; j < allmatrix[0].cols; j++) {
            float b_x = allmatrix[1].at<float>(i, j);
            float g_x = allmatrix[3].at<float>(i, j);
            float r_x = allmatrix[5].at<float>(i, j);

            float b_y = allmatrix[2].at<float>(i, j);
            float g_y = allmatrix[4].at<float>(i, j);
            float r_y = allmatrix[6].at<float>(i, j);

            float A = std::pow(r_x, 2) + std::pow(g_x, 2) + std::pow(b_x, 2);
            float B = std::pow(r_y, 2) + std::pow(g_y, 2) + std::pow(b_y, 2);
            float C = r_x * r_y + g_x * g_y + b_x * b_y;

            float lambda_0 = (A + B + std::sqrt(std::pow((A - B), 2) + 4 * C * C)) / 2;

            E[i].push_back(std::sqrt(lambda_0));
        }
    }
    return E;
}

/**
 * @brief Определяет ориентацию локальных градиентов изображения
 * @param allmatrix std::vector<cv::Mat> allmatrix со всеми необходимыми матрицами
 * @return Возвращает вектор с углами ориентации локальных градиентов std::vector<std::vector<float>> F
 */
std::vector<std::vector<float>> GetF(std::vector<cv::Mat> allmatrix){
    std::vector<std::vector<float>> F;
    for (int i = 0; i < allmatrix[0].rows; i++) {
        std::vector<float> temp_f;
        F.push_back(temp_f);

        for (int j = 0; j < allmatrix[0].cols; j++) {
            float b_x = allmatrix[1].at<float>(i, j);
            float g_x = allmatrix[3].at<float>(i, j);
            float r_x = allmatrix[5].at<float>(i, j);

            float b_y = allmatrix[2].at<float>(i, j);
            float g_y = allmatrix[4].at<float>(i, j);
            float r_y = allmatrix[6].at<float>(i, j);

            float A = std::pow(r_x, 2) + std::pow(g_x, 2) + std::pow(b_x, 2);
            float B = std::pow(r_y, 2) + std::pow(g_y, 2) + std::pow(b_y, 2);
            float C = r_x * r_y + g_x * g_y + b_x * b_y;

            float lambda_0 = (A + B + std::sqrt(std::pow((A - B), 2) + 4 * C * C)) / 2;

            F[i].push_back(0.5 * std::atan2(A - B, 2 * C));
        }
    }
    return F;
}


/**
 * @brief Формирует матрицу изображения в градациях серого по вектору E
 * @param E Вектор E со значениями локальных градиентов std::vector<std::vector<float>> E
 * @param img Исходное изображение cv::Mat img
 * @return Возвращает матрицу изображения в градациях серого cv::Mat grayImg
 */
cv::Mat GradientInGray(std::vector<std::vector<float>> E, cv::Mat img){
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
    grayImg = ConvertToFloat(grayImg);
    for (int i = 0; i < grayImg.rows; i++){
        for (int j = 0; j < grayImg.cols; j++){
            grayImg.at<float>(i, j) = E[i][j]/255.0;
        }
    }

    return grayImg;
}

/**
 * @brief Формирует матрицу HSV-изображения по векторам E, F и параметру param
 * @param F Вектор F со значениями локальных градиентов std::vector<std::vector<float>> F
 * @param E Вектор E со значениями локальных градиентов std::vector<std::vector<float>> E
 * @param img Исходное изображение cv::Mat img
 * @param param параметр float param, отвечающий за значение Value в HSV-изображении
 * @return Возвращает матрицу HSV-изображения cv::Mat HSVImg
 */
cv::Mat GradientInHSV(std::vector<std::vector<float>> F, std::vector<std::vector<float>> E, cv::Mat img, float param) {
    cv::Mat HSVImg;
    cv::cvtColor(img, HSVImg, cv::COLOR_BGR2HSV);
    HSVImg = ConvertToFloat(HSVImg);

    for (int i = 0; i < HSVImg.rows; i++) {
        for (int j = 0; j < HSVImg.cols; j++) {
            HSVImg.at<cv::Vec3f>(i, j)[0] = F[i][j];
            HSVImg.at<cv::Vec3f>(i, j)[1] = E[i][j] / 255.0;
            HSVImg.at<cv::Vec3f>(i, j)[2] = param;
        }
    }

    return HSVImg;
}

