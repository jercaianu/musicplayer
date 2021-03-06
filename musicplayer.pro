######################################################################
# Automatically generated by qmake (3.0) Sat Nov 19 23:17:43 2016
######################################################################

TEMPLATE = app
TARGET = musicplayer
INCLUDEPATH += . ../stk/include ../stk/src/include
LIBS = Release/* -lpthread -framework CoreAudio -framework CoreFoundation -framework CoreMIDI
DEFINES += HAVE_GETTIMEOFDAY __MACOSX_CORE__ __LITTLE_ENDIAN__
QMAKE_CXXFLAGS += -O3
CONFIG += c++11 warn_off
HEADERS = effect.h phasereffect.h delayeffect.h audioplayer.h mainwindow.h
QT += core widgets

# Input
SOURCES += phasereffect.cpp delayeffect.cpp audioplayer.cpp mainwindow.cpp play.cpp
