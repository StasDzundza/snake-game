QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console c++14

INCLUDEPATH += "../../"
INCLUDEPATH += "googletest"
INCLUDEPATH += "googletest/include"
INCLUDEPATH += "googlemock"
INCLUDEPATH += "googlemock/include"

SOURCES += \
    main.cpp \
    ../../food.cpp \
    ../../gamecontroller.cpp \
    ../../gamewindow.cpp \
    ../../leaderboard.cpp \
    ../../mainwindow.cpp \
    ../../settings.cpp \
    ../../snake.cpp \
    ../../stopwatch.cpp \
    ../../wall.cpp \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc

FORMS += \
    ../../leaderboard.ui \
    ../../mainwindow.ui \
    ../../settings.ui

HEADERS += \
    ../../constants.h \
    ../../food.h \
    ../../gamecontroller.h \
    ../../gamewindow.h \
    ../../leaderboard.h \
    ../../mainwindow.h \
    ../../settings.h \
    ../../snake.h \
    ../../stopwatch.h \
    ../../wall.h
