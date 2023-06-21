#include "gradient_lib/library.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <fstream>


int main(int argc, char **argv ) {
    system("chcp 65001");
    std::string OutputDirectory;
    std::string InputDirectory;


    bool loading = false;
    bool saving = false;
    bool visualiseInGray = false;
    bool visualiseInHSV = false;
    bool processingInGray = false;
    bool processingInHSV = false;
    bool help = false;
    bool show = true;

    if (argc == 1){
        std::cout << "Описание доступных команд\n";
        std::cout << "-VG : Визуализировать результат в градациях серого" << '\n';
        std::cout << "-VH : Визуализировать результат в HSV" << '\n';
        std::cout << "-PG : Обработать изображение для сохранения в градациях серого" << '\n';
        std::cout << "-PH : Обработать изображение для сохранения в HSV" << '\n';
        std::cout << "Следующие команды нужно использовать по образцу: -[command]=[way]" << '\n';
        std::cout << "-H : Показать возможные команды" << std::endl;
        std::cout << "-l : Указать путь к изображению" << '\n';
        std::cout << "-s : Указать путь для сохранения результатов" << '\n';
        show = false;
    }

    for (int i = 1; i < argc; i ++) {
        if(static_cast<std::string>(argv[i]) == "-VG"){
            visualiseInGray = true;
        }
        else if(static_cast<std::string>(argv[i]) == "-VH"){
            visualiseInHSV = true;
        }
        else if(static_cast<std::string>(argv[i]) == "-PG"){
            processingInGray = true;
        }
        else if(static_cast<std::string>(argv[i]) == "-PH"){
            processingInHSV = true;
        }
        else if(static_cast<std::string>(argv[i]) == "-H"){
            help = true;
        }

        else if (static_cast<std::string>(argv[i]).size() > 2){
            std::string param = static_cast<std::string>(argv[i]);
            if (param[0] == '-' && param[2] == '='){
                if (param[1] == 'l'){
                    loading = true;
                    InputDirectory = param.substr(3,param.size() - 3);
                }
                else if (param[1] == 's'){
                    saving = true;
                    OutputDirectory = param.substr(3,param.size() - 3);

                    //checking of file existing
                    std::ifstream file;
                    file.open(OutputDirectory);
                    if (file){
                        saving = false;
                        std::cout << "File exists" << '\n';
                    }
                }
                else{
                    throw std::invalid_argument("invalid argument");
                }
            }
            else{
                throw std::invalid_argument("invalid argument");
            }
        }
        else{
            throw std::invalid_argument("invalid argument");
        }

    }

    if (show){
        if (loading){
            cv::Mat img = cv::imread(InputDirectory);
            cv::Mat grayImg;
            cv::Mat HSVImg;

            if (help){
                std::cout << "Описание доступных команд\n";
                std::cout << "Следующие команды нужно использовать по образцу: -[command]=[way]" << '\n';
                std::cout << "-l : Указать путь к изображению" << '\n';
                std::cout << "-s : Указать путь для сохранения результатов (формат сохраняемого файла - строго tiff)" << '\n';
                std::cout << "-h : Показать возможные команды" << std::endl;
                show = false;
            }

            if(img.empty()){
                std::cout << "This image can not be processed";
                return 1;
            }

            if (processingInGray){
                std::vector<std::vector<float>> E;
                std::vector<cv::Mat> megamatrix = GetAllMatrix(img);
                E = GetE(megamatrix);
                grayImg = GradientInGray(E, img);
            }

            if(processingInHSV){
                std::vector<std::vector<float>> E;
                std::vector<std::vector<float>> F;
                std::vector<cv::Mat> megamatrix = GetAllMatrix(img);
                E = GetE(megamatrix);
                F = GetF(megamatrix);
                HSVImg = GradientInHSV(F, E, img, 0.5);
            }

            if (visualiseInGray){
                std::vector<std::vector<float>> E;
                cv::imshow("Source Image", img);
                std::vector<cv::Mat> megamatrix = GetAllMatrix(img);
                E = GetE(megamatrix);
                grayImg = GradientInGray(E, img);
                cv::imshow("Result In Grayscale", grayImg);

                if (saving){
                    saving = false;
                    cv::imwrite(OutputDirectory, grayImg);
                }
            }

            if (visualiseInHSV){
                std::vector<std::vector<float>> E;
                std::vector<std::vector<float>> F;
                cv::imshow("Source Image", img);
                std::vector<cv::Mat> megamatrix = GetAllMatrix(img);
                E = GetE(megamatrix);
                F = GetF(megamatrix);
                HSVImg = GradientInHSV(F, E, img, 0.5);
                cv::imshow("Result In HSV", HSVImg);

                if (saving){
                    saving = false;
                    cv::cvtColor(HSVImg, img, cv::COLOR_HSV2BGR);
                    cv::imwrite(OutputDirectory, HSVImg);
                }
            }

            if ((saving && processingInGray)||(saving && visualiseInGray)){
                cv::imwrite(OutputDirectory, grayImg);
                saving = false;
            }
//            else if ((saving && processingInHSV)||(saving && visualiseInHSV)){
//                cv::cvtColor(HSVImg, img, cv::COLOR_HSV2BGR);
//                cv::imwrite(OutputDirectory, img);
//                saving = false;
//            }
            else if (saving){
                cv::imwrite(OutputDirectory, img);
                saving = false;
            }



        }

        if (help){
            std::cout << "Описание доступных команд\n";
            std::cout << "Следующие команды нужно использовать по образцу: -[command]=[way]" << '\n';
            std::cout << "-l : Указать путь к изображению" << '\n';
            std::cout << "-s : Указать путь для сохранения результатов" << '\n';
            std::cout << "-h : Показать возможные команды" << std::endl;
            show = false;
        }

        cv::waitKey(0);
        cv::destroyAllWindows();
    }

}

