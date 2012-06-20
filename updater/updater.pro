#-------------------------------------------------
#
# Project created by QtCreator 2012-06-20T10:54:24
#
#-------------------------------------------------

QT       += core gui

TARGET = updater
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    updatedialog.cpp \
    showupdatedialog.cpp \
    qjson/serializerrunnable.cpp \
    qjson/serializer.cpp \
    qjson/qobjecthelper.cpp \
    qjson/parserrunnable.cpp \
    qjson/parser.cpp \
    qjson/json_scanner.cpp \
    qjson/json_parser.cc

HEADERS  += mainwindow.h \
    updatedialog.h \
    showupdatedialog.h \
    qjson/serializerrunnable.h \
    qjson/serializer.h \
    qjson/qobjecthelper.h \
    qjson/qjson_export.h \
    qjson/qjson_debug.h \
    qjson/position.hh \
    qjson/parserrunnable.h \
    qjson/parser_p.h \
    qjson/parser.h \
    qjson/location.hh \
    qjson/json_scanner.h \
    qjson/json_parser.hh \
    qjson/stack.hh

FORMS    += mainwindow.ui \
    showupdatedialog.ui \
    updatedialog.ui

OTHER_FILES += \
    qjson/json_parser.yy






