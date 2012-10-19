#-------------------------------------------------
#
# Project created by QtCreator 2012-06-20T10:54:24
#
#-------------------------------------------------
QT += core gui network webkit

TARGET = updater
TEMPLATE = app

win32:LIBS += -lshell32 -lole32 -luser32


LIBS += -Lc:/QtWorksapce/updater/lib -lqjson0

SOURCES += main.cpp\
        mainwindow.cpp \
    updatedialog.cpp \
    showupdatedialog.cpp \
    requtil.cpp \
    preferences.cpp \
    fileutils.cpp \
    utils.cpp \
    downloadcontrol.cpp \
    download.cpp \
    single_application.cpp

HEADERS  += mainwindow.h \
    updatedialog.h \
    showupdatedialog.h \
    qjson/parser.h \
    requtil.h \
    preferences.h \
    fileutils.h \
    utils.h \
    qjson/serializer.h \
    download.h \
    downloadcontrol.h \
    single_application.h

FORMS    += \
    showupdatedialog.ui \
    updatedialog.ui

OTHER_FILES += \
    qjson/json_parser.yy \
    updater.rc \
    ts/updater_en.ts \
    ts/updater_jp.ts \
    ts/updater_zh_cn.ts

RESOURCES += \
    updater.qrc

RC_FILE = \
  updater.rc

TRANSLATIONS = ts/updater_zh_cn.ts ts/updater_en.ts ts/updater_jp.ts






































