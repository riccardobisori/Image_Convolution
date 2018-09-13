cmake_minimum_required(VERSION 3.3)
project(Image_Convolution)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RGBPixel.cpp RGBPixel.h Identity.cpp Identity.h Filter.cpp Filter.h GrayPixel.cpp GrayPixel.h BitmapImage.h EdgeDetection.cpp EdgeDetection.h PPM.h PPM.cpp PGM.cpp PGM.h Sharpen.cpp Sharpen.h Emboss.cpp Emboss.h Blur.cpp Blur.h)
add_executable(Image_Convolution ${SOURCE_FILES})