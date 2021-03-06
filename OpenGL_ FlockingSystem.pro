# core Qt Libs to use add more here if needed.
QT+=gui opengl core

# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include

# where to put the .o files
OBJECTS_DIR=obj/

# where to put moc auto generated files
MOC_DIR=moc/

# This specifies the exe name
TARGET=bin/FlockingSystem

# were are going to default to a console app
CONFIG += console

# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle

# where to put the ui files
UI_HEADERS_DIR=ui

FORMS += \
    ui/MainWindow.ui

# add the glsl shader files/extra files
OTHER_FILES+= README.md


# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}


# Auto include all .cpp files in the project src directory (can specifiy individually if required)
SOURCES+= $$PWD/src/main.cpp \
          $$PWD/src/NGLScene.cpp \
          $$PWD/src/boid.cpp \
          $$PWD/src/MainWindow.cpp \
          $$PWD/src/flock.cpp


# same for the .h files
HEADERS+= $$PWD/include/NGLScene.h \
          $$PWD/include/boid.h \
          $$PWD/include/flock.h \
          $$PWD/include/MainWindow.h


# note each command you add needs a ; as it will be run as a single line
# first check if we are shadow building or not easiest way is to check out against current
!equals(PWD, $${OUT_PWD}){
        copydata.commands = echo "creating destination dirs" ;
        # now make a dir
        copydata.commands += mkdir -p $$OUT_PWD/shaders ;
        copydata.commands += echo "copying files" ;
        # then copy the files
        copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
        # now make sure the first target is built before copy
        first.depends = $(first) copydata
        export(first.depends)
        export(copydata.commands)
        # now add it as an extra target
        QMAKE_EXTRA_TARGETS += first copydata
}
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}


