QT       += network webkit xml xmlpatterns

TARGET = managefile
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    preferences.cpp \
    utils.cpp \
    shortcuteditordialog.cpp \
    shortcutmodel.cpp \
    extensionmodel.cpp \
    myTreeList.cpp \
    fileutils.cpp \
    importdocdialog.cpp \
    excuteJavaUtil.cpp \
    mytableview.cpp \
    myitemdelegate.cpp \
    mystandarditemmodel.cpp \
    exportdocdialog.cpp \
    createsubdirdialog.cpp \
    movetodirdialog.cpp \
    propofdirdialog.cpp \
    tabwidget.cpp \
    toolbarsearch.cpp \
    webview.cpp \
    browsermainwindow.cpp

HEADERS  += mainwindow.h \
    preferences.h \
    utils.h \
    shortcuteditordialog.h \
    shortcutmodel.h \
    extensionmodel.h \
    myTreeList.h \
    fileutils.h \
    importdocdialog.h \
    mytableview.h \
    myitemdelegate.h \
    mystandarditemmodel.h \
    exportdocdialog.h \
    createsubdirdialog.h \
    movetodirdialog.h \
    propofdirdialog.h \
    browsermainwindow.h \
    tabwidget.h \
    toolbarsearch.h \
    webview.h

RESOURCES += \
    managefile.qrc

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    shortcuteditordialog.ui \
    importdocdialog.ui \
    exportdocdialog.ui \
    createsubdirdialog.ui \
    movetodirdialog.ui \
    propofdirdialog.ui

TRANSLATIONS = ts/managefile_zh_cn.ts ts/managefile_en.ts ts/managefile_jp.ts

OTHER_FILES += \
    ts/managefile_en.ts \
    ts/managefile_jp.ts \
    ts/managefile_zh_cn.ts






































