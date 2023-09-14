cmake_minimum_required(VERSION 3.5)
project(model_tmp)

set(CMAKE_CXX_STANDARD 17)

include_directories(../controller)
include_directories(../lib)
include_directories(.)
include_directories(data)
include_directories(parser)
include_directories(activation_function)
include_directories(perceptron)

add_executable(model_tmp
       ../lib/matrix.cc
       ../lib/matrix.h
        activation_function/i_activation_function.h
        activation_function/sigmoid.cc
        activation_function/sigmoid.h
        perceptron/matrix_perceptron.cc
        perceptron/matrix_perceptron.h
        perceptron/i_perceptron.h
        data/picture.h
        data/picture.cc
        data/dataset.cc
        data/dataset.h
        data/mapping.cc
        data/mapping.h
        parser/parser.h
        parser/parser.cc
        tmp_main.cc)

target_compile_options(model_tmp PRIVATE -O3)