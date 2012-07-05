QT       += network webkit xml xmlpatterns sql
TARGET = managefile
TEMPLATE = app

LIBS += C:\QtWorksapce\managefile\lib\sqlite3.lib \
         C:\QtSDK\Symbian\tools\sbs\win32\mingw\lib\libwinspool.a

CONFIG+=qaxcontainer

SOURCES += main.cpp \
        mainwindow.cpp \
    preferences.cpp \
    utils.cpp \
    fileutils.cpp \
    importdocdialog.cpp \
    excuteJavaUtil.cpp \
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
    noteobj.cpp \
    noteeditor.cpp \
    texteditor.cpp \
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
    qscintilla2/src/XPM.cpp \
    qscintilla2/src/WindowAccessor.cpp \
    qscintilla2/src/ViewStyle.cpp \
    qscintilla2/src/UniConversion.cpp \
    qscintilla2/src/StyleContext.cpp \
    qscintilla2/src/Style.cpp \
    qscintilla2/src/ScintillaBase.cpp \
    qscintilla2/src/RunStyles.cpp \
    qscintilla2/src/RESearch.cpp \
    qscintilla2/src/PropSet.cpp \
    qscintilla2/src/PositionCache.cpp \
    qscintilla2/src/PerLine.cpp \
    qscintilla2/src/LineMarker.cpp \
    qscintilla2/src/LexYAML.cpp \
    qscintilla2/src/LexVHDL.cpp \
    qscintilla2/src/LexVerilog.cpp \
    qscintilla2/src/LexVB.cpp \
    qscintilla2/src/LexTeX.cpp \
    qscintilla2/src/LexTCL.cpp \
    qscintilla2/src/LexTAL.cpp \
    qscintilla2/src/LexTADS3.cpp \
    qscintilla2/src/LexTACL.cpp \
    qscintilla2/src/LexSQL.cpp \
    qscintilla2/src/LexSpice.cpp \
    qscintilla2/src/LexSpecman.cpp \
    qscintilla2/src/LexSorcus.cpp \
    qscintilla2/src/LexSML.cpp \
    qscintilla2/src/LexSmalltalk.cpp \
    qscintilla2/src/LexScriptol.cpp \
    qscintilla2/src/LexRuby.cpp \
    qscintilla2/src/LexRebol.cpp \
    qscintilla2/src/LexR.cpp \
    qscintilla2/src/LexPython.cpp \
    qscintilla2/src/LexPS.cpp \
    qscintilla2/src/LexProgress.cpp \
    qscintilla2/src/LexPowerShell.cpp \
    qscintilla2/src/LexPowerPro.cpp \
    qscintilla2/src/LexPOV.cpp \
    qscintilla2/src/LexPLM.cpp \
    qscintilla2/src/LexPerl.cpp \
    qscintilla2/src/LexPB.cpp \
    qscintilla2/src/LexPascal.cpp \
    qscintilla2/src/LexOthers.cpp \
    qscintilla2/src/LexOpal.cpp \
    qscintilla2/src/LexNsis.cpp \
    qscintilla2/src/LexNimrod.cpp \
    qscintilla2/src/LexMySQL.cpp \
    qscintilla2/src/LexMSSQL.cpp \
    qscintilla2/src/LexMPT.cpp \
    qscintilla2/src/LexMMIXAL.cpp \
    qscintilla2/src/LexMetapost.cpp \
    qscintilla2/src/LexMatlab.cpp \
    qscintilla2/src/LexMagik.cpp \
    qscintilla2/src/LexLua.cpp \
    qscintilla2/src/LexLout.cpp \
    qscintilla2/src/LexLisp.cpp \
    qscintilla2/src/LexKix.cpp \
    qscintilla2/src/LexInno.cpp \
    qscintilla2/src/LexHTML.cpp \
    qscintilla2/src/LexHaskell.cpp \
    qscintilla2/src/LexGui4Cli.cpp \
    qscintilla2/src/LexGAP.cpp \
    qscintilla2/src/LexFortran.cpp \
    qscintilla2/src/LexForth.cpp \
    qscintilla2/src/LexFlagship.cpp \
    qscintilla2/src/LexEScript.cpp \
    qscintilla2/src/LexErlang.cpp \
    qscintilla2/src/LexEiffel.cpp \
    qscintilla2/src/LexD.cpp \
    qscintilla2/src/LexCSS.cpp \
    qscintilla2/src/LexCsound.cpp \
    qscintilla2/src/LexCrontab.cpp \
    qscintilla2/src/LexCPP.cpp \
    qscintilla2/src/LexConf.cpp \
    qscintilla2/src/LexCOBOL.cpp \
    qscintilla2/src/LexCmake.cpp \
    qscintilla2/src/LexCLW.cpp \
    qscintilla2/src/LexCaml.cpp \
    qscintilla2/src/LexBullant.cpp \
    qscintilla2/src/LexBasic.cpp \
    qscintilla2/src/LexBash.cpp \
    qscintilla2/src/LexBaan.cpp \
    qscintilla2/src/LexAVE.cpp \
    qscintilla2/src/LexAU3.cpp \
    qscintilla2/src/LexASY.cpp \
    qscintilla2/src/LexAsn1.cpp \
    qscintilla2/src/LexAsm.cpp \
    qscintilla2/src/LexAPDL.cpp \
    qscintilla2/src/LexAda.cpp \
    qscintilla2/src/LexAbaqus.cpp \
    qscintilla2/src/KeyWords.cpp \
    qscintilla2/src/KeyMap.cpp \
    qscintilla2/src/Indicator.cpp \
    qscintilla2/src/ExternalLexer.cpp \
    qscintilla2/src/Editor.cpp \
    qscintilla2/src/DocumentAccessor.cpp \
    qscintilla2/src/Document.cpp \
    qscintilla2/src/Decoration.cpp \
    qscintilla2/src/ContractionState.cpp \
    qscintilla2/src/CharClassify.cpp \
    qscintilla2/src/CellBuffer.cpp \
    qscintilla2/src/CallTip.cpp \
    qscintilla2/src/AutoComplete.cpp \
    qscintilla2/Qt4/ScintillaQt.cpp \
    qscintilla2/Qt4/SciClasses.cpp \
    qscintilla2/Qt4/qscistyledtext.cpp \
    qscintilla2/Qt4/qscistyle.cpp \
    qscintilla2/Qt4/qsciscintillabase.cpp \
    qscintilla2/Qt4/qsciscintilla.cpp \
    qscintilla2/Qt4/qsciprinter.cpp \
    qscintilla2/Qt4/qscimacro.cpp \
    qscintilla2/Qt4/qscilexeryaml.cpp \
    qscintilla2/Qt4/qscilexerxml.cpp \
    qscintilla2/Qt4/qscilexervhdl.cpp \
    qscintilla2/Qt4/qscilexerverilog.cpp \
    qscintilla2/Qt4/qscilexertex.cpp \
    qscintilla2/Qt4/qscilexertcl.cpp \
    qscintilla2/Qt4/qscilexersql.cpp \
    qscintilla2/Qt4/qscilexerspice.cpp \
    qscintilla2/Qt4/qscilexerruby.cpp \
    qscintilla2/Qt4/qscilexerpython.cpp \
    qscintilla2/Qt4/qscilexerproperties.cpp \
    qscintilla2/Qt4/qscilexerpov.cpp \
    qscintilla2/Qt4/qscilexerpostscript.cpp \
    qscintilla2/Qt4/qscilexerperl.cpp \
    qscintilla2/Qt4/qscilexerpascal.cpp \
    qscintilla2/Qt4/qscilexermakefile.cpp \
    qscintilla2/Qt4/qscilexerlua.cpp \
    qscintilla2/Qt4/qscilexerjavascript.cpp \
    qscintilla2/Qt4/qscilexerjava.cpp \
    qscintilla2/Qt4/qscilexeridl.cpp \
    qscintilla2/Qt4/qscilexerhtml.cpp \
    qscintilla2/Qt4/qscilexerfortran.cpp \
    qscintilla2/Qt4/qscilexerfortran77.cpp \
    qscintilla2/Qt4/qscilexerdiff.cpp \
    qscintilla2/Qt4/qscilexerd.cpp \
    qscintilla2/Qt4/qscilexercustom.cpp \
    qscintilla2/Qt4/qscilexercss.cpp \
    qscintilla2/Qt4/qscilexercsharp.cpp \
    qscintilla2/Qt4/qscilexercpp.cpp \
    qscintilla2/Qt4/qscilexercmake.cpp \
    qscintilla2/Qt4/qscilexerbatch.cpp \
    qscintilla2/Qt4/qscilexerbash.cpp \
    qscintilla2/Qt4/qscilexer.cpp \
    qscintilla2/Qt4/qscidocument.cpp \
    qscintilla2/Qt4/qscicommandset.cpp \
    qscintilla2/Qt4/qscicommand.cpp \
    qscintilla2/Qt4/qsciapis.cpp \
    qscintilla2/Qt4/qsciabstractapis.cpp \
    qscintilla2/Qt4/PlatQt.cpp \
    qscintilla2/Qt4/ListBoxQt.cpp \
    shortcuteditordialog.cpp \
    shortcutmodel.cpp \
    sqlkeywords.cpp \
    txteditorwidget.cpp \
    txteditor.cpp \
    logview.cpp \
    logindialog.cpp \
    qjson/serializerrunnable.cpp \
    qjson/serializer.cpp \
    qjson/qobjecthelper.cpp \
    qjson/parserrunnable.cpp \
    qjson/parser.cpp \
    qjson/json_scanner.cpp \
    qjson/json_parser.cc \
    accountdialog.cpp \
    changepwddialog.cpp \
    requtil.cpp \
    scoretovipdialog.cpp \
    aboutdialog.cpp \
    db/resultdao.cpp \
    jvm.cpp

HEADERS  += mainwindow.h \
    preferences.h \
    utils.h \
    extensionmodel.h \
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
    noteeditor.h \
    noteobj.h \
    texteditor.h \
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
    qscintilla2/src/XPM.h \
    qscintilla2/src/ViewStyle.h \
    qscintilla2/src/UniConversion.h \
    qscintilla2/src/SVector.h \
    qscintilla2/src/StyleContext.h \
    qscintilla2/src/Style.h \
    qscintilla2/src/SplitVector.h \
    qscintilla2/src/ScintillaBase.h \
    qscintilla2/src/RunStyles.h \
    qscintilla2/src/RESearch.h \
    qscintilla2/src/PositionCache.h \
    qscintilla2/src/PerLine.h \
    qscintilla2/src/Partitioning.h \
    qscintilla2/src/LineMarker.h \
    qscintilla2/src/KeyMap.h \
    qscintilla2/src/Indicator.h \
    qscintilla2/src/ExternalLexer.h \
    qscintilla2/src/Editor.h \
    qscintilla2/src/DocumentAccessor.h \
    qscintilla2/src/Document.h \
    qscintilla2/src/Decoration.h \
    qscintilla2/src/ContractionState.h \
    qscintilla2/src/CharClassify.h \
    qscintilla2/src/CharacterSet.h \
    qscintilla2/src/CellBuffer.h \
    qscintilla2/src/CallTip.h \
    qscintilla2/src/AutoComplete.h \
    qscintilla2/include/WindowAccessor.h \
    qscintilla2/include/SString.h \
    qscintilla2/include/ScintillaWidget.h \
    qscintilla2/include/Scintilla.h \
    qscintilla2/include/SciLexer.h \
    qscintilla2/include/PropSet.h \
    qscintilla2/include/Platform.h \
    qscintilla2/include/KeyWords.h \
    qscintilla2/include/Accessor.h \
    qscintilla2/Qt4/Qsci/qscistyledtext.h \
    qscintilla2/Qt4/Qsci/qscistyle.h \
    qscintilla2/Qt4/Qsci/qsciscintillabase.h \
    qscintilla2/Qt4/Qsci/qsciscintilla.h \
    qscintilla2/Qt4/Qsci/qsciprinter.h \
    qscintilla2/Qt4/Qsci/qscimacro.h \
    qscintilla2/Qt4/Qsci/qscilexeryaml.h \
    qscintilla2/Qt4/Qsci/qscilexerxml.h \
    qscintilla2/Qt4/Qsci/qscilexervhdl.h \
    qscintilla2/Qt4/Qsci/qscilexerverilog.h \
    qscintilla2/Qt4/Qsci/qscilexertex.h \
    qscintilla2/Qt4/Qsci/qscilexertcl.h \
    qscintilla2/Qt4/Qsci/qscilexersql.h \
    qscintilla2/Qt4/Qsci/qscilexerspice.h \
    qscintilla2/Qt4/Qsci/qscilexerruby.h \
    qscintilla2/Qt4/Qsci/qscilexerpython.h \
    qscintilla2/Qt4/Qsci/qscilexerproperties.h \
    qscintilla2/Qt4/Qsci/qscilexerpov.h \
    qscintilla2/Qt4/Qsci/qscilexerpostscript.h \
    qscintilla2/Qt4/Qsci/qscilexerperl.h \
    qscintilla2/Qt4/Qsci/qscilexerpascal.h \
    qscintilla2/Qt4/Qsci/qscilexermakefile.h \
    qscintilla2/Qt4/Qsci/qscilexerlua.h \
    qscintilla2/Qt4/Qsci/qscilexerjavascript.h \
    qscintilla2/Qt4/Qsci/qscilexerjava.h \
    qscintilla2/Qt4/Qsci/qscilexeridl.h \
    qscintilla2/Qt4/Qsci/qscilexerhtml.h \
    qscintilla2/Qt4/Qsci/qscilexerfortran.h \
    qscintilla2/Qt4/Qsci/qscilexerfortran77.h \
    qscintilla2/Qt4/Qsci/qscilexerdiff.h \
    qscintilla2/Qt4/Qsci/qscilexerd.h \
    qscintilla2/Qt4/Qsci/qscilexercustom.h \
    qscintilla2/Qt4/Qsci/qscilexercss.h \
    qscintilla2/Qt4/Qsci/qscilexercsharp.h \
    qscintilla2/Qt4/Qsci/qscilexercpp.h \
    qscintilla2/Qt4/Qsci/qscilexercmake.h \
    qscintilla2/Qt4/Qsci/qscilexerbatch.h \
    qscintilla2/Qt4/Qsci/qscilexerbash.h \
    qscintilla2/Qt4/Qsci/qscilexer.h \
    qscintilla2/Qt4/Qsci/qsciglobal.h \
    qscintilla2/Qt4/Qsci/qscidocument.h \
    qscintilla2/Qt4/Qsci/qscicommandset.h \
    qscintilla2/Qt4/Qsci/qscicommand.h \
    qscintilla2/Qt4/Qsci/qsciapis.h \
    qscintilla2/Qt4/Qsci/qsciabstractapis.h \
    qscintilla2/Qt4/ScintillaQt.h \
    qscintilla2/Qt4/SciClasses.h \
    qscintilla2/Qt4/ListBoxQt.h \
    shortcuteditordialog.h \
    shortcutmodel.h \
    sqlkeywords.h \
    txteditor.h \
    txteditorwidget.h \
    logview.h \
    logindialog.h \
    qjson/stack.hh \
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
    accountdialog.h \
    changepwddialog.h \
    requtil.h \
    scoretovipdialog.h \
    aboutdialog.h \
    jni.h \
    jni_md.h \
    excuteJavaUtil.h \
    db/resultdao.h \
    jvm.h

RESOURCES += \
    managefile.qrc

FORMS    += mainwindow.ui \
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
    testUI.ui \
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
    aboutdialog.ui

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
    docview/½Ó¿Ú½Å±¾.js \
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
    qscintilla2/include/Face.py

























































































































































































































































































