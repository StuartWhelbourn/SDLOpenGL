TARGET=SDLOpenGL

OBJECTS_DIR=obj
INCLUDEPATH+=$$PWD/include

SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/SDLOpenGL.cpp

HEADERS+=$$PWD/include/SDLOpenGL.h
QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)
LIBS+=$$system(sdl2-config --libs)
include($(HOME)/NGL/UseNGL.pri)
