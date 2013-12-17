#-------------------------------------------------
#
# Project created by QtCreator 2013-09-27T20:13:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET =
TEMPLATE =


SOURCES += \
    main.cpp \
    gui/cmainframe.cpp \
    gui/customstyle.cpp \
    gui/menu.cpp \
    gui/uiFont.cpp \
    gui/uiglobal.cpp \
    gobal.cpp \
    gui/cmainwindow.cpp \
    hiwaylib.cpp \
    uiRtc.cpp \
    Database.cpp \
    gui/UserManage.cpp \
    gui/cenrollstep1.cpp \
    gui/enrollpwd.cpp



HEADERS  += \
    gui/cmainframe.h \
    gui/Define.h \
    gui/customstyle.h \
    gui/menu.h \
    gui/uiFont.h \
    gui/cmainwindow.h \
    hiwaylib.h \
    global.h \
    include/rtc.h \
    Database.h \
    gui/UserManage.h \
    gui/cenrollstep1.h \
    gui/enrollpwd.h


FORMS    += \
    gui/cmainframe.ui \
    gui/cmainwindow.ui \
    gui/cenrollstep1.ui \
    gui/enrollpwd.ui

RESOURCES += \
    hiway.qrc

TRANSLATIONS = hiway.ts
