# qmake project (alternative to CMake) - open this in Qt Creator
QT       += core gui widgets
CONFIG   += c++17
TARGET    = StudentRecordSystem
TEMPLATE  = app

SOURCES += main.cpp StudentFile.cpp MainWindow.cpp
HEADERS += Student.h StudentFile.h MainWindow.h
