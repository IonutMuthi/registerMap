cmake_minimum_required(VERSION 3.5)

project(RegisterMapDemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml Test)
find_package(libm2k REQUIRED)

include_directories(register)
include_directories(register/bitfield)

file(GLOB REGISTER_SRC src/register/*.cpp src/register/*.hpp)
file(GLOB BITFIELD_SRC src/register/bitfield/*.cpp src/register/bitfield/*.hpp)
file(GLOB SRC_LIST src/*.cpp src/*.hpp *.cpp *.hpp)
file(GLOB READ_WRITE src/readwrite/*.cpp src/readwrite/*.hpp)
file(GLOB TEST test/*.cpp test/*.hpp)

set(PROJECT_SOURCES
    ${SRC_LIST}
    ${REGISTER_SRC}
    ${BITFIELD_SRC}
    ${READ_WRITE}
    ${TEST}
    mainwindow.ui

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RegisterMapDemo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RegisterMapDemo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RegisterMapDemo SHARED
            ${PROJECT_SOURCES}
            ${SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
    add_executable(RegisterMapDemo
        ${PROJECT_SOURCES}
        ${SOURCES}
    )
endif()
endif()

target_link_libraries(RegisterMapDemo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Xml libm2k::libm2k Qt5::Test)

set_target_properties(RegisterMapDemo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS RegisterMapDemo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RegisterMapDemo)
endif()
