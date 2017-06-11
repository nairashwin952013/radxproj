TEMPLATE = app
TARGET = radx2grid
CONFIG -= qt
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++14

*-icc* {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O3 -xHost -ipo -fp-model fast=2 -openmp
}

*-g++* {
    QMAKE_CXXFLAGS_RELEASE -= -O2 -mtune=generic
    QMAKE_CXXFLAGS_RELEASE += -O3 -ffast-math -fopt-info-loop -fopenmp
}

INCLUDEPATH += \
    /usr/local/include \
    /apps/compilers/intel/2016/tbb/include


# Input
HEADERS += \
           apps/Radx/src/Radx2Grid/Args.hh \
           apps/Radx/src/Radx2Grid/CartInterp.hh \
           apps/Radx/src/Radx2Grid/Interp.hh \
           apps/Radx/src/Radx2Grid/OutputMdv.hh \
           apps/Radx/src/Radx2Grid/Params.hh \
           apps/Radx/src/Radx2Grid/PolarInterp.hh \
           apps/Radx/src/Radx2Grid/PpiInterp.hh \
           apps/Radx/src/Radx2Grid/Radx2Grid.hh \
           apps/Radx/src/Radx2Grid/Radx2GridPlus.hh \
           apps/Radx/src/Radx2Grid/ReorderInterp.hh \
           apps/Radx/src/Radx2Grid/SatInterp.hh \
           apps/Radx/src/Radx2Grid/SvdData.hh \
           apps/Radx/src/Radx2Grid/Thread.hh \
           apps/Radx/src/Radx2Grid/PolarDataStream.hh \
           apps/Radx/src/Radx2Grid/Polar2Cartesian.hh \
           apps/Radx/src/Radx2Grid/ThreadQueue.hh \
           apps/Radx/src/Radx2Grid/WriteOutput.hh \
           apps/Radx/src/Radx2Grid/Cart2Grid.hh

SOURCES += apps/Radx/src/Radx2Grid/Args.cc \
           apps/Radx/src/Radx2Grid/CartInterp.cc \
           apps/Radx/src/Radx2Grid/Interp.cc \
           apps/Radx/src/Radx2Grid/Main.cc \
           apps/Radx/src/Radx2Grid/OutputMdv.cc \
           apps/Radx/src/Radx2Grid/Params.cc \
           apps/Radx/src/Radx2Grid/Polar2Cartesian.cpp \
           apps/Radx/src/Radx2Grid/PolarDataStream.cpp \
           apps/Radx/src/Radx2Grid/PolarInterp.cc \
           apps/Radx/src/Radx2Grid/PpiInterp.cc \
           apps/Radx/src/Radx2Grid/Radx2Grid.cc \
           apps/Radx/src/Radx2Grid/Radx2GridPlus.cc \
           apps/Radx/src/Radx2Grid/ReorderInterp.cc \
           apps/Radx/src/Radx2Grid/SatInterp.cc \
           apps/Radx/src/Radx2Grid/SvdData.cc \
           apps/Radx/src/Radx2Grid/Thread.cc \
           apps/Radx/src/Radx2Grid/WriteOutput.cpp \
           apps/Radx/src/Radx2Grid/Cart2Grid.cpp

OTHER_FILES += apps/Radx/src/Radx2Grid/makefile.am

LIBS += -lradar \
    -lFmq \
    -lSpdb \
    -lMdv \
    -lphysics \
    -lRadx \
    -lrapformats \
    -ldsserver \
    -ldidss \
    -leuclid \
    -lrapmath \
    -ltoolsa \
    -ldataport \
    -ltdrp \
    -lkd \
    -lnetcdf_c++4 \
    -lnetcdf_c++ \
    -lnetcdf \
    -lhdf5_cpp \
    -lhdf5_hl \
    -lhdf5 \
    -ludunits2 \
    -lz \
    -lbz2 \
    -lpthread \
    -lexpat \
    -lm \
    -lgomp \
    -lfftw3

CONFIG(debug, debug|release) {
    LIBS += -ltbb_debug
} else {
    LIBS += -ltbb
}

LIBS += -L/usr/local/lib \
        -L/apps/lib/expat/2.1.1/lib

unix:{
    T1 = $$(RADX_RUNTIME)
    isEmpty(T1) {
        message(RADX_RUNTIME is empty)
    } else {
        INCLUDEPATH += $$(RADX_RUNTIME)/include
        LIBS += -L$$(RADX_RUNTIME)/lib
    }
}
