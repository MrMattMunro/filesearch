QT       +=widgets network webkit xml xmlpatterns sql webkitwidgets
TARGET = Solo
TEMPLATE = app

LIBS += D:\QtWorksapce\managefile\lib\sqlite3.lib \
         C:\Qt\Tools\mingw48_32\i686-w64-mingw32\lib\libwinspool.a \
         -LD:/QtWorksapce/managefile/lib -lqjson0

win32:LIBS += -lshell32 -lole32 -luser32

CONFIG+=qaxcontainer
CONFIG+=release

SOURCES += main.cpp \
        mainwindow.cpp \
    preferences.cpp \
    utils.cpp \
    fileutils.cpp \
    importdocdialog.cpp \
    mytableview.cpp \
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
    createtagdialog.cpp \
    propoftagdialog.cpp \
    movetotagdialog.cpp \
    mylistwidget.cpp \
    customtooldialog.cpp \
    exportconvertdialog.cpp \
    Common.cpp \
    xmlobj.cpp \
    docnoteinfodialog.cpp \
    notesdialog.cpp \
    db/notedao.cpp \
    db/dirdao.cpp \
    db/docdao.cpp \
    mytabledelegate.cpp \
    mytreeitemmodel.cpp \
    mytreedelegate.cpp \
    mytableitemmodel.cpp \
    mytreeview.cpp \
    printerwidget.cpp \
    relatedocdialog.cpp \
    db/relatedocdao.cpp \
    doctagsdialog.cpp \
    db/doctagdao.cpp \
    doctodirdialog.cpp \
    propofdocdialog.cpp \
    sortsubdirsdialog.cpp \
    preferencesdialog.cpp \
    shortcuteditordialog.cpp \
    shortcutmodel.cpp \
    sqlkeywords.cpp \
    txteditor.cpp \
    logview.cpp \
    logindialog.cpp \
    accountdialog.cpp \
    changepwddialog.cpp \
    requtil.cpp \
    scoretovipdialog.cpp \
    aboutdialog.cpp \
    db/resultdao.cpp \
    jvm.cpp \
    saveurldialog.cpp \
    sqlloader.cpp \
    codeeditor.cpp \
    highlighter.cpp \
    refereedialog.cpp \
    intelliplugin.cpp \
    ueditor.cpp \
    uesave.cpp \
    single_application.cpp \
    optofsearchdialog.cpp \
    resultview.cpp \
    resultdelegate.cpp \
    tableresult.cpp \
    document.cpp \
    libmaia/maiaXmlRpcClient.cpp \
    libmaia/maiaObject.cpp \
    libmaia/maiaFault.cpp \
    libmaia/client.cpp


HEADERS  += mainwindow.h \
    preferences.h \
    utils.h \
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
    createtagdialog.h \
    propoftagdialog.h \
    movetotagdialog.h \
    mylistwidget.h \
    customtooldialog.h \
    exportconvertdialog.h \
    Common.h \
    xmlobj.h \
    docnoteinfodialog.h \
    notesdialog.h \
    db/notedao.h \
    db/dirdao.h \
    db/docdao.h \
    mytreeitemmodel.h \
    mytreedelegate.h \
    mytableitemmodel.h \
    mytabledelegate.h \
    mytreeview.h \
    printerwidget.h \
    relatedocdialog.h \
    db/relatedocdao.h \
    doctagsdialog.h \
    db/doctagdao.h \
    doctodirdialog.h \
    propofdocdialog.h \
    sortsubdirsdialog.h \
    preferencesdialog.h \
    shortcuteditordialog.h \
    shortcutmodel.h \
    sqlkeywords.h \
    txteditor.h \
    logview.h \
    logindialog.h \
    qjson/serializer.h \
    qjson/parser.h \
    accountdialog.h \
    changepwddialog.h \
    requtil.h \
    scoretovipdialog.h \
    aboutdialog.h \
    jni.h \
    jni_md.h \
    db/resultdao.h \
    jvm.h \
    saveurldialog.h \
    indexfile.h \
    sqlloader.h \
    codeeditor.h \
    highlighter.h \
    qjson/qjson_export.h \
    refereedialog.h \
    sendmail.h \
    intelliplugin.h \
    ueditor.h \
    uesave.h \
    single_application.h \
    optofsearchdialog.h \
    resultdelegate.h \
    tableresult.h \
    tableresultview.h \
    document.h \
    publicfun.h \
    libmaia/maiaXmlRpcClient.h \
    libmaia/maiaObject.h \
    libmaia/maiaFault.h \
    libmaia/client.h

INCLUDEPATH += C:\Program Files\Microsoft SDKs\Windows\v5.0\Include

RESOURCES += \
    managefile.qrc

FORMS    += \
    preferencesdialog.ui \
    importdocdialog.ui \
    exportdocdialog.ui \
    createsubdirdialog.ui \
    movetodirdialog.ui \
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
    createtagdialog.ui \
    propoftagdialog.ui \
    movetotagdialog.ui \
    customtooldialog.ui \
    exportconvertdialog.ui \
    docnoteinfodialog.ui \
    notesdialog.ui \
    printerwidget.ui \
    relatedocdialog.ui \
    doctagsdialog.ui \
    doctodirdialog.ui \
    sortsubdirsdialog.ui \
    propofdirdialog.ui \
    propofdocdialog.ui \
    prefslnfwidget.ui \
    shortcuteditordialog.ui \
    txteditor.ui \
    logview.ui \
    prefsdatastorewidget.ui \
    prefseditorwidget.ui \
    logindialog.ui \
    accountdialog.ui \
    changepwddialog.ui \
    scoretovipdialog.ui \
    aboutdialog.ui \
    saveurldialog.ui \
    refereedialog.ui \
    ueditor.ui \
    optofsearchdialog.ui

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
    sql/mf_deleted_guid.sql \
    docview/�ӿڽű�.js \
    docview/viewdoc.htm \
    docview/ole32.dll \
    docview/dsoframer.ocx \
    docview/jquery/plugin/jquery.query.js \
    docview/jquery/plugin/jquery.pagination.js \
    docview/jquery/plugin/jquery.blockUI.js \
    docview/jquery/js/jquery-ui-1.8.16.custom.min.js \
    docview/jquery/js/jquery-1.6.2.min.js \
    docview/jquery/development-bundle/themes/base/jquery.ui.theme.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.tabs.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.slider.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.selectable.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.resizable.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.progressbar.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.dialog.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.datepicker.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.core.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.button.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.base.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.autocomplete.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.all.css \
    docview/jquery/development-bundle/themes/base/jquery.ui.accordion.css \
    docview/jquery/development-bundle/themes/base/images/ui-icons_cd0a0a_256x240.png \
    docview/jquery/development-bundle/themes/base/images/ui-icons_888888_256x240.png \
    docview/jquery/development-bundle/themes/base/images/ui-icons_454545_256x240.png \
    docview/jquery/development-bundle/themes/base/images/ui-icons_222222_256x240.png \
    docview/jquery/development-bundle/themes/base/images/ui-icons_2e83ff_256x240.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_highlight-soft_75_cccccc_1x100.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_glass_95_fef1ec_1x400.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_glass_75_e6e6e6_1x400.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_glass_75_dadada_1x400.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_glass_65_ffffff_1x400.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_glass_55_fbf9ee_1x400.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_flat_75_ffffff_40x100.png \
    docview/jquery/development-bundle/themes/base/images/ui-bg_flat_0_aaaaaa_40x100.png \
    docview/jquery/css/ui-darkness/images/ui-icons_ffffff_256x240.png \
    docview/jquery/css/ui-darkness/images/ui-icons_cccccc_256x240.png \
    docview/jquery/css/ui-darkness/images/ui-icons_a83300_256x240.png \
    docview/jquery/css/ui-darkness/images/ui-icons_222222_256x240.png \
    docview/jquery/css/ui-darkness/images/ui-icons_4b8e0b_256x240.png \
    docview/jquery/css/ui-darkness/images/ui-bg_inset-soft_30_f58400_1x100.png \
    docview/jquery/css/ui-darkness/images/ui-bg_inset-soft_25_000000_1x100.png \
    docview/jquery/css/ui-darkness/images/ui-bg_highlight-soft_80_eeeeee_1x100.png \
    docview/jquery/css/ui-darkness/images/ui-bg_gloss-wave_25_333333_500x100.png \
    docview/jquery/css/ui-darkness/images/ui-bg_glass_40_ffc73d_1x400.png \
    docview/jquery/css/ui-darkness/images/ui-bg_glass_40_0078a3_1x400.png \
    docview/jquery/css/ui-darkness/images/ui-bg_glass_20_555555_1x400.png \
    docview/jquery/css/ui-darkness/images/ui-bg_flat_50_5c5c5c_40x100.png \
    docview/jquery/css/ui-darkness/images/ui-bg_flat_30_cccccc_40x100.png \
    docview/jquery/css/ui-darkness/jquery-ui-1.8.16.custom.css \
    qscintilla2/CMakeLists.txt \
    qscintilla2/src/SciTE.properties \
    qscintilla2/src/License.txt \
    qscintilla2/src/LexGen.py \
    qscintilla2/include/Scintilla.iface \
    qscintilla2/include/License.txt \
    qscintilla2/include/HFacer.py \
    qscintilla2/include/Face.py \
    file_manager.ico \
    file_manager.rc \
    libmaia/maia.pro \
    libmaia/maia.pri \
    libmaia/LICENSE \
    libmaia/Changelog \
    libmaia/examples/client/client.pro

RC_FILE = \
  file_manager.rc












































































































































































































































































































