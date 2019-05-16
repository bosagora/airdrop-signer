#-------------------------------------------------
#
# Project created by QtCreator 2019-03-03T16:49:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BOSAGORAAirdropSigner
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

MOC_DIR = bin
OBJECTS_DIR = bin
UI_DIR = src

INCLUDEPATH += src res/sodium/include/

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/stellar/SecretKey.cpp \
        src/stellar/StrKey.cpp \
        src/stellar/crc16.cpp

HEADERS += \
        src/mainwindow.h \
        src/stellar/SecretKey.h \
        src/stellar/ByteSlice.h \
        src/stellar/StrKey.h \
        src/stellar/crc16.h

FORMS += \
        src/mainwindow.ui

# Note: Needs to be manually copied to BOSAGORAAirdropSigner.app/Contents/Resources/
TRANSLATIONS += res/korean.ts
OTHER_FILES  += res/korean.ts

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
    LIBS += -framework CoreFoundation
    ICON = res/BOSAGORA.icns
}

win32 {
    INCLUDES += $$PWD/res/sodium/include/
    LIBS += -L$$PWD/res/sodium/ -lsodium
} else {
    QT_CONFIG -= no-pkg-config
    CONFIG += link_pkgconfig
    PKGCONFIG += libsodium
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

