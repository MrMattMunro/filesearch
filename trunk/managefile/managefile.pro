QT       += network webkit xml xmlpatterns sql
TARGET = managefile
TEMPLATE = app

LIBS += C:\QtWorksapce\managefile\lib\sqlite3.lib

CONFIG+=qaxcontainer

SOURCES += main.cpp \
        mainwindow.cpp \
    preferences.cpp \
    utils.cpp \
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
    browser/xbel.cpp \
    browser/webview.cpp \
    browser/urllineedit.cpp \
    browser/toolbarsearch.cpp \
    browser/tabwidget.cpp \
    browser/squeezelabel.cpp \
    browser/settings.cpp \
    browser/searchlineedit.cpp \
    browser/networkaccessmanager.cpp \
    browser/modelmenu.cpp \
    browser/history.cpp \
    browser/edittreeview.cpp \
    browser/edittableview.cpp \
    browser/downloadmanager.cpp \
    browser/cookiejar.cpp \
    browser/chasewidget.cpp \
    browser/browsermainwindow.cpp \
    browser/browserapplication.cpp \
    browser/bookmarks.cpp \
    browser/autosaver.cpp \
    db/database.cpp \
    db/tagdao.cpp \
    createtagdialog.cpp

HEADERS  += mainwindow.h \
    preferences.h \
    utils.h \
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
    browser/xbel.h \
    browser/webview.h \
    browser/urllineedit.h \
    browser/toolbarsearch.h \
    browser/tabwidget.h \
    browser/squeezelabel.h \
    browser/settings.h \
    browser/searchlineedit.h \
    browser/networkaccessmanager.h \
    browser/modelmenu.h \
    browser/history.h \
    browser/edittreeview.h \
    browser/edittableview.h \
    browser/downloadmanager.h \
    browser/cookiejar.h \
    browser/chasewidget.h \
    browser/browsermainwindow.h \
    browser/browserapplication.h \
    browser/bookmarks.h \
    browser/autosaver.h \
    db/sqlite3.h \
    db/database.h \
    db/tagdao.h \
    createtagdialog.h

RESOURCES += \
    managefile.qrc

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    importdocdialog.ui \
    exportdocdialog.ui \
    createsubdirdialog.ui \
    movetodirdialog.ui \
    propofdirdialog.ui \
    history.ui \
    browser/settings.ui \
    browser/proxy.ui \
    browser/passworddialog.ui \
    browser/history.ui \
    browser/downloads.ui \
    browser/downloaditem.ui \
    browser/cookiesexceptions.ui \
    browser/cookies.ui \
    browser/bookmarks.ui \
    browser/addbookmarkdialog.ui \
    createtagdialog.ui

TRANSLATIONS = ts/managefile_zh_cn.ts ts/managefile_en.ts ts/managefile_jp.ts

OTHER_FILES += \
    ts/managefile_en.ts \
    ts/managefile_jp.ts \
    ts/managefile_zh_cn.ts \
    browser/Info_mac.plist \
    lib/sqlite3.lib \
    lib/sqlite3.exp \
    lib/sqlite3.dll \
    lib/sqlite3.def \
    sql/mf_tag_group.sql \
    sql/mf_tag.sql \
    sql/mf_document_tag.sql \
    sql/mf_document_relate.sql \
    sql/mf_document_param.sql \
    sql/mf_document.sql \
    sql/mf_deleted_guid.sql






























































































