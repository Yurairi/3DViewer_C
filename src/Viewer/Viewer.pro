QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl openglwidgets concurrent

include(QtGifImage/src/gifimage/qtgifimage.pri)


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affin.c \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.c

HEADERS += \
    affin.h \
    glwidget.h \
    mainwindow.h \
    parser.h

ICON = icon/icon.icns

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    3dv.png \
    icon/icon.icns \
    img_src/jopik.png

RESOURCES += \
    img.qrc \
    img.qrc
