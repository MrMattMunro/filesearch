/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/
#include <QSettings>
#include <QApplication>

#include "preferences.h"

Preferences* Preferences::_instance = 0;

Preferences::Preferences(QObject *parent)
 : QObject(parent)
{
	QFont f(QApplication::font());

        QSettings s("slfile.cn", "filemanage");

	m_checkQtVersion = s.value("checkQtVersion", true).toBool();
        m_isFullScreen = s.value("isFullScreen", true).toBool();
        m_isShowClassTree = s.value("isShowClassTree", true).toBool();
        m_isShowToolBar = s.value("isShowToolBar", true).toBool();
        m_isShowDocUnderSub = s.value("isShowDocUnderSub", true).toBool();
        m_isShowDocUnderSubTag = s.value("isShowDocUnderSubTag", true).toBool();

        m_seltoolbaritemlist = s.value("selToolbarItemList", QStringList()).toStringList();
        m_waittoolbaritemlist = s.value("waitToolbarItemList", QStringList()).toStringList();
        m_defaulttoolbaritemlist = s.value("defaultToolbarItemList", QStringList()).toStringList();
        m_defaultwaittoolbaritemlist = s.value("defaultWaitToolbarItemList", QStringList()).toStringList();


        m_notedocuid = s.value("notes/selDocUid", QString()).toString();
        m_selnoteuid = s.value("notes/selNoteUid", QString()).toString();

        m_tableselmode = s.value("table/selMode", QString()).toString();
        m_isShowNotesOnTips = s.value("table/showNotesOnTips", true).toBool();
        m_tableselfield = s.value("table/selField", QStringList()).toStringList();

        // prefs data start
        m_mainpath = s.value("prefs/data/mainpath", QString()).toString();
        m_indexpath = s.value("prefs/data/indexpath", QString()).toString();
        m_backpath = s.value("prefs/data/backpath", QString()).toString();
        m_exportpath = s.value("prefs/data/exportpath", QString()).toString();
        // prefs data end

        // userinfo start
        m_useremail = s.value("userinfo/useremail", QString()).toString();
        m_username = s.value("userinfo/username", QString()).toString();
        m_displayname = s.value("userinfo/displayname", QString()).toString();
        m_score = s.value("userinfo/score", QString()).toString();
        m_dt_expired = s.value("userinfo/dtexpired", QString()).toString();
        m_type = s.value("userinfo/type", QString()).toString();
        m_store_limit = s.value("userinfo/storelimit", QString()).toString();
        m_store_used = s.value("userinfo/storeused", QString()).toString();
        m_traffic_limit = s.value("userinfo/trafficlimit", QString()).toString();
        m_traffic_used = s.value("userinfo/trafficused", QString()).toString();
        m_last_sel_tags = s.value("userinfo/lastseltags", QString()).toString();
        m_last_sel_dirs = s.value("userinfo/lastseldirs", QString()).toString();
        m_last_open_docs = s.value("userinfo/lastopendocs", QString()).toString();
        m_last_open_notes = s.value("userinfo/lastopennotes", QString()).toString();
        m_last_open_urls = s.value("userinfo/lastopenurls", QString()).toString();
        m_version = s.value("userinfo/version", QString()).toString();
        // userinfo end

        // search setting start
        m_searchdir = s.value("search/dir", QString()).toString();
        m_searchobject = s.value("search/object", QString()).toString();
        // search setting end

        // is Indexing
        m_is_indexing = s.value("isindexing", false).toBool();

	m_recentlyUsedCount = s.value("prefs/recentlyUsedSpinBox", 5).toInt();
	m_openLastDB = s.value("prefs/openLastDB", true).toBool();
	m_openLastSqlFile = s.value("prefs/openLastSqlFile", true).toBool();
	m_lastDB = s.value("lastDatabase", QString()).toString();
	m_GUItranslator = s.value("prefs/languageComboBox", 0).toInt();
	m_GUIstyle = s.value("prefs/styleComboBox", 0).toInt();
	m_GUIfont = s.value("prefs/applicationFont", f).value<QFont>();
	m_cropColumns = s.value("prefs/cropColumnsCheckBox", false).toBool();

	m_sqlFont = s.value("prefs/sqleditor/font", f).value<QFont>();
	m_sqlFontSize = s.value("prefs/sqleditor/fontSize", f.pointSize()).toInt();
	m_activeHighlighting = s.value("prefs/sqleditor/useActiveHighlightCheckBox", true).toBool();
	m_activeHighlightColor = s.value("prefs/sqleditor/activeHighlightButton", stdDarkColor()).value<QColor>();
	m_textWidthMark = s.value("prefs/sqleditor/useTextWidthMarkCheckBox", true).toBool();
	m_textWidthMarkSize = s.value("prefs/sqleditor/textWidthMarkSpinBox", 60).toInt();
	m_codeCompletion = s.value("prefs/sqleditor/useCodeCompletion", false).toBool();
	m_codeCompletionLength = s.value("prefs/sqleditor/completionLengthBox", 3).toInt();
	m_useShortcuts = s.value("prefs/sqleditor/useShortcuts", false).toBool();
	m_shortcuts = s.value("prefs/sqleditor/shortcuts", QMap<QString,QVariant>()).toMap();

	// data
	m_dateTimeFormat = s.value("data/dateTimeFormat", "MM/dd/yyyy").toString();

	// data export
	m_exportFormat = s.value("dataExport/format", 0).toInt();
	m_exportDestination = s.value("dataExport/destination", 0).toInt();
	m_exportHeaders = s.value("dataExport/headers", true).toBool();
	m_exportEncoding = s.value("dataExport/encoding", "UTF-8").toString();
	m_exportEol = s.value("dataExport/eol", 0).toInt();
        // extensions
        m_allowExtensionLoading = s.value("extensions/allowLoading", true).toBool();
        m_extensionList = s.value("extensions/list", QStringList()).toStringList();

        // 分散每个文件类型
        m_allsupported << "*.doc" << "*.docx" << "*.xls" << "*.xlsx" << "*.ppt" << "*.pptx"
                     << "*.pdf"
                     << "*.html" << "*.htm"
                     << "*.jpeg" << "*.jpg" << "*.png" << "*.bmp" << "*.gif"
                     << "*.flv" << "*.swf"
                     << "*.cpp" << "*.h" << "*.hpp" << "*.c" << "*.java" << "*.js" << "*.cs" << "*.vbs" << "*.sql" << "*.rb" << "*.py" << "*.asp" << "*.aspx" << "*.jsp" << "*.php" << "*.xml"
                     << "*.txt" << "*.ini" << "*.bar" << "*.inf"
                     << "*.rm" << "*.rmvb" << "*.avi" << "*.mpg" << "*.mlv" << "*.mpe" << "*.mpeg" << "*.m2v";

        m_officedoc << "*.doc" << "*.docx" << "*.xls" << "*.xlsx" << "*.ppt" << "*.pptx" << "*.msg";
        m_word << "*.doc" << "*.docx";
        m_excel <<"*.xls" << "*.xlsx";
        m_ppt << "*.ppt" << "*.pptx";

        m_pdf << "*.pdf";
        m_htmls<< "*.html" << "*.htm";
        m_pics  << "*.jpeg" << "*.jpg" << "*.png" << "*.bmp" << "*.gif";
        m_swfs << "*.flv" << "*.swf";
        m_sources << "*.cpp" << "*.h" << "*.hpp" << "*.c" << "*.java" << "*.js" << "*.cs" << "*.vbs" << "*.sql" << "*.rb" << "*.py" << "*.asp" << "*.aspx" << "*.jsp" << "*.php" << "*.xml";
        m_txts << "*.txt" << "*.ini" << "*.bar" << "*.inf";
        m_movies << "*.rm" << "*.rmvb" << "*.avi" << "*.mpg" << "*.mlv" << "*.mpe" << "*.mpeg" << "*.m2v";

        // 初始化 
        if(m_defaulttoolbaritemlist.size() == 0){
            m_defaulttoolbaritemlist << "view_tree.png" << "view_fullscreen.png" << "homepage.png" << "invite.png" << "forum.png";
        }
        if(m_defaultwaittoolbaritemlist.size() == 0){
            m_defaultwaittoolbaritemlist << "document-savetomobi.png" << "document-import.png" << "document-export.png";
        }
        if(m_seltoolbaritemlist.size() == 0){
            m_seltoolbaritemlist  << "view_tree.png" << "view_fullscreen.png" << "homepage.png" << "invite.png" << "forum.png";
        }
        if(m_waittoolbaritemlist.size() == 0){
           m_waittoolbaritemlist << "document-savetomobi.png" << "document-import.png" << "document-export.png";
        }

}

Preferences::~Preferences()
{
        QSettings settings("slfile.cn", "filemanage");
	settings.setValue("checkQtVersion", m_checkQtVersion);
        settings.setValue("isFullScreen", m_isFullScreen);
        settings.setValue("isShowClassTree", m_isShowClassTree);
        settings.setValue("isShowToolBar", m_isShowToolBar);
        settings.setValue("isShowDocUnderSub", m_isShowDocUnderSub);
        settings.setValue("isShowDocUnderSubTag", m_isShowDocUnderSubTag);

        settings.setValue("selToolbarItemList", m_seltoolbaritemlist);
        settings.setValue("waitToolbarItemList", m_waittoolbaritemlist);
        settings.setValue("defaultToolbarItemList", m_defaulttoolbaritemlist);
        settings.setValue("defaultWaitToolbarItemList", m_defaultwaittoolbaritemlist);

        settings.setValue("notes/selDocUid", m_notedocuid);
        settings.setValue("notes/selNoteUid", m_selnoteuid);

        settings.setValue("table/selMode", m_tableselmode);
        settings.setValue("table/showNotesOnTips", m_isShowNotesOnTips);
        settings.setValue("table/selField", m_tableselfield);

	// lnf
	settings.setValue("prefs/languageComboBox", m_GUItranslator);
	settings.setValue("prefs/styleComboBox", m_GUIstyle);
	settings.setValue("prefs/applicationFont", m_GUIfont);
	settings.setValue("prefs/recentlyUsedSpinBox", m_recentlyUsedCount);
	settings.setValue("prefs/openLastDB", m_openLastDB);
	settings.setValue("prefs/openLastSqlFile", m_openLastSqlFile);
	// data results
	settings.setValue("prefs/cropColumnsCheckBox", m_cropColumns);
        // data
        settings.setValue("prefs/data/mainpath", m_mainpath);
        settings.setValue("prefs/data/indexpath", m_indexpath);
        settings.setValue("prefs/data/backpath", m_backpath);
        settings.setValue("prefs/data/exportpath", m_exportpath);

        // userinfo start
        settings.setValue("userinfo/useremail", m_useremail);
        settings.setValue("userinfo/username", m_username);
        settings.setValue("userinfo/displayname",  m_displayname);
        settings.setValue("userinfo/score", m_score);
        settings.setValue("userinfo/dtexpired",m_dt_expired);
        settings.setValue("userinfo/type", m_type);
        settings.setValue("userinfo/storelimit", m_store_limit);
        settings.setValue("userinfo/storeused", m_store_used);
        settings.setValue("userinfo/trafficlimit", m_traffic_limit);
        settings.setValue("userinfo/trafficused",  m_traffic_used);
        settings.setValue("userinfo/lastseltags", m_last_sel_tags);
        settings.setValue("userinfo/lastseldirs", m_last_sel_dirs);
        settings.setValue("userinfo/lastopendocs", m_last_open_docs);
        settings.setValue("userinfo/lastopennotes",  m_last_open_notes);
        settings.setValue("userinfo/lastopenurls", m_last_open_urls);
        settings.setValue("userinfo/version", m_version);
        // userinfo end

        // search setting start
        settings.setValue("search/dir", m_searchdir);
        settings.setValue("search/object", m_searchobject);
        // search setting end
        settings.setValue("isindexing", false);

	// sql editor
	settings.setValue("prefs/sqleditor/font", m_sqlFont);
        settings.setValue("prefs/sqleditor/fontSize", m_sqlFontSize);
	settings.setValue("prefs/sqleditor/useActiveHighlightCheckBox", m_activeHighlighting);
	settings.setValue("prefs/sqleditor/activeHighlightButton", m_activeHighlightColor);
	settings.setValue("prefs/sqleditor/useTextWidthMarkCheckBox", m_textWidthMark);
	settings.setValue("prefs/sqleditor/textWidthMarkSpinBox", m_textWidthMarkSize);
	settings.setValue("prefs/sqleditor/useCodeCompletion", m_codeCompletion);
	settings.setValue("prefs/sqleditor/completionLengthBox", m_codeCompletionLength);
	settings.setValue("prefs/sqleditor/useShortcuts", m_useShortcuts);
	settings.setValue("prefs/sqleditor/shortcuts", m_shortcuts);
	// qscintilla editor
	settings.setValue("prefs/qscintilla/syDefaultColor", m_syDefaultColor);
	settings.setValue("prefs/qscintilla/syKeywordColor", m_syKeywordColor);
	settings.setValue("prefs/qscintilla/syNumberColor", m_syNumberColor);
	settings.setValue("prefs/qscintilla/syStringColor", m_syStringColor);
	settings.setValue("prefs/qscintilla/syCommentColor", m_syCommentColor);
	//
	settings.setValue("data/dateTimeFormat", m_dateTimeFormat);
	// data export
	settings.setValue("dataExport/format", m_exportFormat);
	settings.setValue("dataExport/destination", m_exportDestination);
	settings.setValue("dataExport/headers", m_exportHeaders);
	settings.setValue("dataExport/encoding", m_exportEncoding);
	settings.setValue("dataExport/eol", m_exportEol);
        // extensions
        settings.setValue("extensions/allowLoading", m_allowExtensionLoading);
        settings.setValue("extensions/list", m_extensionList);
}

Preferences* Preferences::instance()
{
    if (_instance == 0)
        _instance = new Preferences();

    return _instance;
}

void Preferences::deleteInstance()
{
    if (_instance)
        delete _instance;
    _instance = 0;
}
