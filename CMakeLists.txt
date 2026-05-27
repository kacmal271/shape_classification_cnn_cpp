
cmake_minimum_required(VERSION 3.16)

project(shape_classification_cnn_cpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)

set(PROJECT_SOURCES
        main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(shape_classification_cnn_cpp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/mainwindow.cpp

        src/testing/UnitTest.cpp
        src/ConsoleInterface.h
        src/ConsoleInterface.cpp
        src/helper/declarations.h
        src/helper/macro.h
        src/helper/test.h
        src/testing/TensorTest.h src/testing/TensorTest.cpp
        src/Interface.cpp
        src/Operation.h src/Operation.cpp
        src/Layer.h src/Layer.cpp
        src/Conv.h src/Conv.cpp
        src/Pool.h src/Pool.cpp
        src/Activation.h src/Activation.cpp
        src/Tensor.h src/Tensor.cpp
        src/BatchTensor.h src/BatchTensor.cpp
        src/Tensor3D.h src/Tensor3D.cpp
        src/Tensor1D.h src/Tensor1D.cpp
        src/Tensor2D.h src/Tensor2D.cpp
        src/Extended/Vector.h src/Extended/Vector.cpp
        src/QHelper/QConsoleInterface.h src/QHelper/QConsoleInterface.cpp
        src/Helper/definitions.h
        src/ChartWindow.h src/ChartWindow.cpp src/ChartWindow.ui
        src/Helper/declarations_q.h
        src/QHelper/QTensorAdapter.h src/QHelper/QTensorAdapter.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET shape_classification_cnn_cpp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(shape_classification_cnn_cpp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(shape_classification_cnn_cpp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(shape_classification_cnn_cpp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(shape_classification_cnn_cpp PRIVATE Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.shape_classification_cnn_cpp)
endif()
set_target_properties(shape_classification_cnn_cpp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS shape_classification_cnn_cpp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(shape_classification_cnn_cpp)
endif()
