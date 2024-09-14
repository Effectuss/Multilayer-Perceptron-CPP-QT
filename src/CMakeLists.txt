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
  ${CMAKE_SOURCE_DIR}/view
  ${CMAKE_SOURCE_DIR}/model
  ${CMAKE_SOURCE_DIR}/model/data
  ${CMAKE_SOURCE_DIR}/model/parser
  ${CMAKE_SOURCE_DIR}/model/perceptron
  ${CMAKE_SOURCE_DIR}/model/activation_function
  ${CMAKE_SOURCE_DIR}/controller
  ${CMAKE_SOURCE_DIR}/view/forms
  ${CMAKE_SOURCE_DIR}/view/mainwindow
  ${CMAKE_SOURCE_DIR}/view/drawarea
  ${CMAKE_SOURCE_DIR}/view/qcustomplot)

set(CMAKE_AUTOUIC_SEARCH_PATHS view/forms)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/controller/mainwindow.cc
    ${CMAKE_SOURCE_DIR}/controller/drawarea.cc
    ${CMAKE_SOURCE_DIR}/model/imagetransformer.cc
    ${CMAKE_SOURCE_DIR}/model/data/picture.cc
    ${CMAKE_SOURCE_DIR}/view/histogramplot.cc
    # ${CMAKE_SOURCE_DIR}/src/model/tmp_main.cc
    ${CMAKE_SOURCE_DIR}/model/activation_function/sigmoid.cc
    ${CMAKE_SOURCE_DIR}/model/data/dataset.cc
    ${CMAKE_SOURCE_DIR}/model/data/mapping.cc
    ${CMAKE_SOURCE_DIR}/model/data/picture.cc
    ${CMAKE_SOURCE_DIR}/model/parser/parser.cc
    ${CMAKE_SOURCE_DIR}/model/perceptron/graph_perceptron.cc
    ${CMAKE_SOURCE_DIR}/model/perceptron/neuron.cc
    ${CMAKE_SOURCE_DIR}/model/perceptron/neuron.cc
    ${CMAKE_SOURCE_DIR}/model/perceptron/layer.cc
    ${CMAKE_SOURCE_DIR}/view/qcustomplot/qcustomplot.cpp)

set(HEADERS
    ${CMAKE_SOURCE_DIR}/controller/mainwindow.h
    ${CMAKE_SOURCE_DIR}/controller/drawarea.h
    ${CMAKE_SOURCE_DIR}/model/imagetransformer.h
    ${CMAKE_SOURCE_DIR}/model/data/picture.h
    ${CMAKE_SOURCE_DIR}/view/histogramplot.h
    ${CMAKE_SOURCE_DIR}/model/activation_function/i_activation_function.h
    ${CMAKE_SOURCE_DIR}/model/activation_function/sigmoid.h
    ${CMAKE_SOURCE_DIR}/model/data/dataset.h
    ${CMAKE_SOURCE_DIR}/model/data/mapping.h
    ${CMAKE_SOURCE_DIR}/model/data/picture.h
    ${CMAKE_SOURCE_DIR}/model/parser/parser.h
    ${CMAKE_SOURCE_DIR}/model/perceptron/i_perceptron.h
    ${CMAKE_SOURCE_DIR}/model/perceptron/graph_perceptron.h
    ${CMAKE_SOURCE_DIR}/model/perceptron/layer.h
    ${CMAKE_SOURCE_DIR}/view/qcustomplot/qcustomplot.h)

set(UI_FORMS ${CMAKE_SOURCE_DIR}/view/forms/mainwindow.ui)

set(PROJECT_SOURCES ${SOURCES} ${HEADERS} ${UI_FORMS}
                    ${CMAKE_SOURCE_DIR}/main.cc)

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
