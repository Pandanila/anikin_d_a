cmake_minimum_required(VERSION 3.24)
project(prj.cw)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(gradient_lib)

add_executable(test test.cpp)


target_link_libraries(test gradient_lib)


install(TARGETS test)
if(WIN32)
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../bin")
else()
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../lib")
endif()

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*opencv_core*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*opencv_highgui4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*opencv_imgproc4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*opencv_imgcodecs4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*zlib1*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*jpeg62*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*libwebp*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*libwebpdecoder*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*libpng16*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*opencv_videoio4*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*tiff*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*libsharpyuv*"
        )

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
        DESTINATION ./bin
        FILES_MATCHING PATTERN "*liblzma*"
        )




