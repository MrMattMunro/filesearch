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
    mystandarditemmodel.cpp

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
    mystandarditemmodel.h

RESOURCES += \
    managefile.qrc

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    shortcuteditordialog.ui \
    importdocdialog.ui

TRANSLATIONS = ts/managefile_zh_cn.ts ts/managefile_en.ts ts/managefile_jp.ts

OTHER_FILES += \
    ts/managefile_en.ts \
    ts/managefile_jp.ts \
    ts/managefile_zh_cn.ts
























