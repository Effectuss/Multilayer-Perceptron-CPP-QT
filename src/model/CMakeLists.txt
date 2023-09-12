# todo: delete later (on merge)

cmake_minimum_required(VERSION 3.0)

project(graph_perceptron)

set(CMAKE_CXX_STANDARD 17)

add_executable(graph_perceptron
        ./tmp_main.cc
        ./activation_function/i_activation_function.h
        ./activation_function/sigmoid.h
        ./activation_function/sigmoid.cc
        ./data/dataset.h
        ./data/dataset.cc
        ./data/mapping.h
        ./data/mapping.cc
        ./data/picture.h
        ./data/picture.cc
        ./parser/parser.h
        ./parser/parser.cc
        ./perceptron/i_perceptron.h
        ./perceptron/graph_perceptron.h
        ./perceptron/graph_perceptron.cc
        )

include_directories(
        ./
        ./activation_function/
        ./data/
        ./parser/
        ./perceptron/
)
