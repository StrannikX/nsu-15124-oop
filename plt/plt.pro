#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T19:28:38
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = plt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    expr_parser.cpp \
    Expressions.cpp \
    plotter.cpp

HEADERS  += mainwindow.h \
    expr_parser.hpp \
    Expressions.hpp \
    plotter.h

FORMS    +=

DISTFILES += \
    plt.pro.user

QMAKE_CXXFLAGS += -std=c++14
