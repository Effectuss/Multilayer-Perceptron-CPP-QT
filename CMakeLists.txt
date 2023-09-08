cmake_minimum_required(VERSION 3.26)
project(Multilayer_Perceptron_CPP_QT)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/controller)
include_directories(src/lib)
include_directories(src/model)
include_directories(src/model/data)
include_directories(src/model/parser)
include_directories(src/model/activation_function)
include_directories(src/model/perceptron)

add_executable(Multilayer_Perceptron_CPP_QT
        src/lib/matrix.cc
        src/lib/matrix.h
        src/model/activation_function/i_activation_function.h
        src/model/activation_function/sigmoid.cc
        src/model/activation_function/sigmoid.h
        src/model/perceptron/matrix_perceptron.cc
        src/model/perceptron/matrix_perceptron.h
        src/model/perceptron/i_perceptron.h
        src/model/data/picture.h
        src/model/data/picture.cc
        src/model/data/dataset.cc
        src/model/data/dataset.h
        src/model/data/mapping.cc
        src/model/data/mapping.h
        src/model/parser/parser.h
        src/model/parser/parser.cc
        main.cc)