cmake_minimum_required(VERSION 3.5)

project(
  MultilayerPerceptron
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

include_directories(
  controller
  #
  model
  model/data
  model/parser
  model/perceptron
  model/activation_function
  #
  external
  #
  lib)

set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

set(SOURCES
    controller/mainwindow.cc
    controller/drawarea.cc
    controller/trainingdialog.cc
    #
    model/imagetransformer.cc
    model/data/picture.cc
    model/activation_function/sigmoid.cc
    model/data/dataset.cc
    model/data/mapping.cc
    model/data/picture.cc
    model/parser/parser.cc
    model/perceptron/graph_perceptron.cc
    model/perceptron/matrix_perceptron.cc
    model/perceptron/neuron.cc
    model/perceptron/neuron.cc
    model/perceptron/layer.cc
    #
    lib/matrix.cc)

set(HEADERS
    controller/mainwindow.h
    controller/drawarea.h
    controller/trainingdialog.h
    #
    model/imagetransformer.h
    model/data/picture.h
    model/activation_function/i_activation_function.h
    model/activation_function/sigmoid.h
    model/data/dataset.h
    model/data/mapping.h
    model/data/picture.h
    model/parser/parser.h
    model/perceptron/i_perceptron.h
    model/perceptron/matrix_perceptron.h
    model/perceptron/graph_perceptron.h
    model/perceptron/layer.h
    #
    lib/matrix.h)

set(UI_FORMS forms/mainwindow.ui forms/trainingdialog.ui)

set(PROJECT_SOURCES ${SOURCES} ${HEADERS} ${UI_FORMS} main.cc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(MultilayerPerceptron MANUAL_FINALIZATION ${PROJECT_SOURCES})
  # Define target properties for Android with Qt 6 as: set_property(TARGET
  # MultilayerPerceptron APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  # ${CMAKE_CURRENT_SOURCE_DIR}/android) For more information, see
  # https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(MultilayerPerceptron SHARED ${PROJECT_SOURCES})
    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(MultilayerPerceptron ${PROJECT_SOURCES})
  endif()
endif()

target_compile_options(
  ${PROJECT_NAME} PRIVATE -O3 # -Wall -Werror -Wextra -Wpedantic
)

target_link_libraries(
  MultilayerPerceptron PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                               Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(
  MultilayerPerceptron
  PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE TRUE)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(MultilayerPerceptron)
endif()
