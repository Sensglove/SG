######################################################################
# Automatically generated by qmake (2.01a) pon. maj 15 10:52:50 2017
######################################################################

OBJECTS_DIR=./out/obj
QMAKE_CXXFLAGS+=-std=c++11
QT+=widgets
QT+=network
TEMPLATE = app
TARGET = SensGlove-data_acquisition
DEPENDPATH += src src src src src inc inc inc inc
INCLUDEPATH += . inc

# Input
HEADERS += inc/odbieranie.hh inc/okno.hh inc/socket.hh inc/transparam.hh
SOURCES += src/main.cpp \
           src/odbieranie.cpp \
           src/okno.cpp \
           src/socket.cpp \
           src/transparam.cpp
