#-------------------------------------------------
#
# Project created by QtCreator 2012-12-11T19:56:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    food.cpp \
    gamecontroller.cpp \
    snake.cpp \
    wall.cpp \
    gamewindow.cpp \
    settings.cpp \
    leaderboard.cpp \
    stopwatch.cpp

HEADERS  += mainwindow.h \
    food.h \
    gamecontroller.h \
    constants.h \
    snake.h \
    wall.h \
    gamewindow.h \
    settings.h \
    leaderboard.h \
    stopwatch.h \
    Tests/catch2/catch.hpp \
    tests.h

RESOURCES += \
    res.qrc

RC_FILE += myapp.rc

FORMS += \
    mainwindow.ui \
    settings.ui \
    leaderboard.ui
