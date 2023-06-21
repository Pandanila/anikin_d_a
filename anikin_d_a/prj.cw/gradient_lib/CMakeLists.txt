cmake_minimum_required(VERSION 3.25)
project(prj.cw)

set(CMAKE_CXX_STANDARD 17)

add_library(gradient_lib library.h library.cpp)
target_include_directories(gradient_lib PUBLIC ".")

find_package(OpenCV REQUIRED)
target_link_libraries(gradient_lib ${OpenCV_LIBS})

install(TARGETS gradient_lib)
if(WIN32)
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../bin")
else()
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../lib")
endif()

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*opencv_core*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*opencv_highgui4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*opencv_imgproc4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*opencv_imgcodecs4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*zlib1*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*jpeg62*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*libwebp*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*libwebpdecoder*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*libpng16*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*opencv_videoio4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*tiff*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*libsharpyuv*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./lib
        FILES_MATCHING PATTERN "*liblzma*"
        )
