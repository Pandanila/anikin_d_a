#include "gradient_lib/library.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <fstream>


int main(int argc, char **argv ) {
    system("chcp 65001");
    std::string OutputName;
    std::string InputName;


    bool loading = false;
    bool saving = false;
    bool visualise = false;
    bool processing = false;
    bool help = false;
    bool show = true;

    if (argc == 1){
        std::cout << "Описание доступных команд\n";
        std::cout << "-H : Показать возможные команды" << std::endl;
        std::cout << "-V : Визуализировать результат" << '\n';
        std::cout << "-P : Обработать изображение и создать массивы E(модули значений градиентов)"
                     " и F(углы ориентации градиентов)" << '\n';
        std::cout << "Следующие команды нужно использовать по образцу: -[command]=[way]" << '\n';
        std::cout << "-l : Указать путь к изображению" << '\n';
        std::cout << "-s : Указать путь для сохранения результатов" << '\n';
        show = false;
    }

    for (int i = 1; i < argc; i ++) {
        if(static_cast<std::string>(argv[i]) == "-V"){
            visualise = true;
        }
        else if(static_cast<std::string>(argv[i]) == "-P"){
            processing = true;
        }
        else if(static_cast<std::string>(argv[i]) == "-H"){
            help = true;
        }

        else if (static_cast<std::string>(argv[i]).size() > 2){
            std::string param = static_cast<std::string>(argv[i]);
            if (param[0] == '-' && param[2] == '='){
                if (param[1] == 'l'){
                    loading = true;
                    InputName = param.substr(3,param.size() - 3);
                }
                else if (param[1] == 's'){
                    saving = true;
                    OutputName = param.substr(3,param.size() - 3);

                    std::ifstream file;
                    file.open(OutputName);
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
            cv::Mat img = cv::imread(InputName);
            cv::Mat grayImg;

            std::vector<std::vector<float>> E;
            std::vector<std::vector<float>> F;
            std::vector<cv::Mat> megamatrix;

            if (help){
                std::cout << "Описание доступных команд\n";
                std::cout << "Следующие команды нужно использовать по образцу:"
                             " -[command]=[way]" << '\n';
                std::cout << "-l : Указать путь к изображению" << '\n';
                std::cout << "-s : Указать путь для сохранения результатов"
                             " (формат сохраняемого файла - строго tiff)" << '\n';
                std::cout << "-h : Показать возможные команды" << std::endl;
                show = false;
            }

            if(img.empty()){
                std::cout << "This image can not be processed";
                return 1;
            }

            if (processing){
                std::vector<cv::Mat> megamatrix = GetAllMatrix(img);
                E = GetE(megamatrix);
                F = GetF(megamatrix);
                grayImg = GradientInGray(E, img);
                std::ofstream out1;
                std::ofstream out2;
                out1.open("E.txt");
                out2.open("F.txt");
                for (int i = 0; i < F.size(); i++){
                    for (int j = 0; j < F[i].size(); j++){
                        out1 << E[i][j] << std::endl;
                        out2 << F[i][j] << std::endl;
                    }
                }
                out1.close();
                out2.close();

                if (saving){
                    saving = false;
                    cv::imwrite(OutputName, grayImg);
                    system("visualisation.py S");

                }
            }

            if (visualise){
                cv::imshow("Source Image", img);
                cv::imshow("Result In Grayscale", grayImg);

                if (saving){
                    saving = false;
                    cv::imwrite(OutputName, grayImg);
                    system("visualisation.py S");
                }
                system("visualisation.py V");
            }

            else if (saving){
                cv::imwrite(OutputName, img);
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
