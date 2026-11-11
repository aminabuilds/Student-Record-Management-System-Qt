cmake_minimum_required(VERSION 3.16)
project(StudentRecordSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Works with Qt 6 or Qt 5
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(StudentRecordSystem
    main.cpp
    Student.h
    StudentFile.h
    StudentFile.cpp
    MainWindow.h
    MainWindow.cpp
)

target_link_libraries(StudentRecordSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(StudentRecordSystem PROPERTIES WIN32_EXECUTABLE ON)
