TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    graph/Graph.cpp \
    graph/MatrixGraph.cpp \
    graph/ListGraph.cpp

HEADERS += \
    graph/Graph.hpp \
    graph/GraphTester.hpp \
    graph/MatrixGraph.hpp \
    graph/ListGraph.hpp
