cmake_minimum_required(VERSION 3.5)
project(model_tmp)

set(CMAKE_CXX_STANDARD 17)

include_directories(controller)
include_directories(lib)
include_directories(model)
include_directories(model/data)
include_directories(model/parser)
include_directories(model/activation_function)
include_directories(model/perceptron)

add_executable(model_tmp
        lib/matrix.cc
        lib/matrix.h
        model/activation_function/i_activation_function.h
        model/activation_function/sigmoid.cc
        model/activation_function/sigmoid.h
        model/perceptron/matrix_perceptron.cc
        model/perceptron/matrix_perceptron.h
        model/perceptron/i_perceptron.h
        model/data/picture.h
        model/data/picture.cc
        model/data/dataset.cc
        model/data/dataset.h
        model/data/mapping.cc
        model/data/mapping.h
        model/parser/parser.h
        model/parser/parser.cc
        tmp_main.cc)