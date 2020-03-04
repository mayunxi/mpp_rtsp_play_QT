TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    rkdrm/bo.c \
    rkdrm/dev.c \
    rkdrm/modeset.c \
    rkdrm/rkdrm.c \
    mppdecoder.cpp \
    main.cpp \
    rtspprotocolutil.cpp \
    sysfunc.cpp

HEADERS += \
    mppdecoder.h \
    rtspprotocolutil.h \
    tools.h \
    rkdrm/bo.h \
    rkdrm/dev.h \
    rkdrm/modeset.h \
    rkdrm/rkdrm.h \
    sysfunc.h \
    MD5.hpp

DISTFILES += \
    README.md



unix:!macx: LIBS += -L$$PWD/lib/ -lrockchip_mpp \
                    -lpthread \
                    -ldrm




INCLUDEPATH += $$PWD/rkdrm
INCLUDEPATH += $$PWD/inc

LIBS += /usr/lib/arm-linux-gnueabihf/libopencv_highgui.so.2.4 \
        /usr/lib/arm-linux-gnueabihf/libopencv_core.so.2.4    \
        /usr/lib/arm-linux-gnueabihf/libopencv_imgproc.so.2.4 \
        /usr/lib/arm-linux-gnueabihf/libopencv_objdetect.so.2.4  \
        /usr/lib/arm-linux-gnueabihf/libopencv_video.so.2.4       \
        /usr/lib/arm-linux-gnueabihf/libopencv_calib3d.so.2.4
