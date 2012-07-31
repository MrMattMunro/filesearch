#include "texteditor.h"

#include <typeinfo>

#include "noteobj.h"	//Still needed for ascii conversion
// #include "settings.h"
#include "utils.h"
#include "db/notedao.h"
#include "preferences.h"
#include "intelliplugin.h"

int statusbarTime;

QAction *actionViewToggleNoteEditor;

QString iconPath;
QString vymName;

QPrinter *printer;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


TextEditor::TextEditor()
{

    e = new QWebView(this);
    e->setGeometry(50, 50, 1024, 768);

    e->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    e->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    e->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, true);

     e->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
     e->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
     e->settings()->setAttribute(QWebSettings::JavaEnabled, true);
     e->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
     e->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, true);
     e->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
     e->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
     e->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
     e->settings()->setAttribute(QWebSettings::LinksIncludedInFocusChain, true);
     e->settings()->setAttribute(QWebSettings::ZoomTextOnly, true);
     e->settings()->setAttribute(QWebSettings::PrintElementBackgrounds, true);
     e->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
     e->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
     e->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
     e->settings()->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
     e->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
     e->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
     e->settings()->setAttribute(QWebSettings::XSSAuditingEnabled, true);
     e->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
     e->settings()->setAttribute(QWebSettings::SpatialNavigationEnabled, true);
     e->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
     e->settings()->setAttribute(QWebSettings::TiledBackingStoreEnabled, true);
     e->settings()->setAttribute(QWebSettings::FrameFlatteningEnabled, true);
     e->settings()->setAttribute(QWebSettings::SiteSpecificQuirksEnabled, true);

    e->page()->setPluginFactory(new IntelliPlugin);

    QDir pathDir = Utils::directoryOf("html");
    QString path = pathDir.absolutePath();
    path.append(QDir::separator());
    path.append("ueditor1_2_2");
    path.append(QDir::separator());
    path.append("index.html");
    e->setObjectName(QString::fromUtf8("welcome"));
    e->setUrl(QUrl(path));

    e->setFocus();
   // setCentralWidget( e );
//    e = new QTextEdit( this);
//    //e->setFocus();
//    // //e->setTextFormat(Qt::RichText);	// default
//    //e->setTabStopWidth (20);		// unit is pixel
//    //e->setTextColor (Qt::black);
//    //e->setAutoFillBackground (true);
//    connect (e, SIGNAL( textChanged() ), this, SLOT( editorChanged() ) );

//    statusBar()->showMessage( tr("Ready","Statusbar message"), statusbarTime);
//    setWindowTitle (vymName +" - " +tr ("Text Editor","Text Editor Window caption"));


//    connect(e, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
//            this, SLOT(formatChanged(const QTextCharFormat &)));


//    // Don't show menubar per default
//    menuBar()->hide();

//    // Toolbars
//    setupFileActions();
//    setupEditActions();
//    setupFormatActions();
//    setupSettingsActions();

//    // Various states
//    blockChangedSignal=false;
//    setInactive();

//    // Load Settings
//    resize (QSize(450,600));


    /*
    resize (settings.value ( "/satellite/noteeditor/geometry/size", QSize(450,600)).toSize());
    move   (settings.value ( "/satellite/noteeditor/geometry/pos", QPoint (250,50)).toPoint());

    setShowWithMain (settings.value ( "/satellite/noteeditor/showWithMain",true).toBool());

    varFont.fromString( settings.value
        ("/satellite/noteeditor/fonts/varFont",
        "Nimbus Sans l,10,-1,5,48,0,0,0,0,0").toString()
    );
    fixedFont.fromString (settings.value(
        "/satellite/noteeditor/fonts/fixedFont",
        "Courier,10-1,5,48,0,0,0,1,0").toString()
    );
    QString s=settings.value ("/satellite/noteeditor/fonts/fonthintDefault","variable").toString();
    if (s == "fixed")
    {
        actionSettingsFonthintDefault->setChecked (true);
        //e->setCurrentFont (fixedFont);
    } else
    {
        actionSettingsFonthintDefault->setChecked (false);
        //e->setCurrentFont (varFont);
    }
    */
//    filenameHint="";

//    // add
//    setText("");

    // Restore position of toolbars
    //restoreState (settings.value("/satellite/noteeditor/state",0).toByteArray());

    // Save settings in vymrc
    //settings.setValue("/mainwindow/printerName",printer->printerName());
}


TextEditor::~TextEditor()
{
// FIXME-3    if (printer) delete printer;
}

void TextEditor::reset()
{
//    //e->clear();
//    actionFormatUseFixedFont->setChecked (false);
//    actionTextBold->setChecked (false);
//    //e->setFontWeight(QFont::Normal);

//    actionTextUnderline->setChecked (false);
//    //e->setFontUnderline (false);

//    actionTextItalic->setChecked (false);
//    //e->setFontItalic (false);

//    QPixmap pix( 16, 16 );
//    pix.fill( Qt::black );
//    actionTextColor->setIcon( pix );
//    //e->setTextColor (Qt::black);

//    actionAlignSubScript->setChecked (false);
//    actionAlignSuperScript->setChecked (false);
//    actionAlignLeft->setChecked (true);
//    //e->setAlignment( Qt::AlignLeft );

//    //add
//    filename = "";
}

bool TextEditor::isEmpty()
{
//    if (e->toPlainText().length()>0)
//        return false;
//    else
        return true;
}

void TextEditor::setShowWithMain(bool v)
{
    showwithmain=v;
}

bool TextEditor::showWithMain()
{
    return showwithmain;
}


void TextEditor::setFontHint (const QString &fh)
{
    if (fh=="fixed")
        actionFormatUseFixedFont->setChecked (true);
    else
        actionFormatUseFixedFont->setChecked (false);
}


QString TextEditor::getFontHint()
{
    if (actionFormatUseFixedFont->isChecked())
        return "fixed";
    else
        return "var";
}

QString TextEditor::getFontHintDefault()
{
    if (actionSettingsFonthintDefault->isChecked())
        return "fixed";
    else
        return "var";
}

void TextEditor::setFilename(const QString &fn)
{
    if (state==filledEditor)
    {
        if (fn.isEmpty() )
        {
            filename="";
            statusBar()->showMessage( tr("No filename available for this note.","Statusbar message"), statusbarTime );
        }
        else
        {
            filename=fn;
            statusBar()->showMessage( tr(QString( "Current filename is %1" ).arg( filename ).toUtf8(),"Statusbar message"), statusbarTime );
        }
    }
}

QString TextEditor::getFilename()
{
    return filename;
}

void TextEditor::setFilenameHint(const QString &fnh)
{
    filenameHint=fnh;
}

QString TextEditor::getFilenameHint()
{
    return filenameHint;
}

QString TextEditor::getText()
{
//    if (e->toPlainText().isEmpty())
//        return QString();
//    else
//        if (actionFormatRichText->isChecked())
//            return //e->toHtml();
//        else
//            return //e->toPlainText();

    return "texttext";
}

bool TextEditor::findText(const QString &t, const QTextDocument::FindFlags &flags)
{
//    if (e->find (t,flags))
//        return true;
//    else
//        return false;
    return true;
}

bool TextEditor::findText(const QString &t, const QTextDocument::FindFlags &flags, int i)
{
    // Position at beginning
//    QTextCursor c=e->textCursor();
//    c.setPosition (0,QTextCursor::MoveAnchor);
//    //e->setTextCursor (c);

//    // Search for t
//    int j=0;
//    while (j<=i)
//    {
//        if (!e->find (t,flags)) return false;
//        j++;
//    }
    return true;

}

void TextEditor::setTextCursor (const QTextCursor &cursor)
{
    //e->setTextCursor (cursor);
}

void TextEditor::setupFileActions()
{
    QToolBar *tb = addToolBar ( tr("Note Actions") );
    tb->setObjectName ("noteEditorFileActions");
    QMenu *fileMenu = menuBar()->addMenu( tr( "&Note","Menubar" ));

    QAction *a;
    a = new QAction( Utils::getPixmap("fileopen.png"), tr( "&Import..." ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_O );
    connect( a, SIGNAL( activated() ), this, SLOT( textLoad() ) );
    tb->addAction (a);
    fileMenu->addAction (a);
    actionFileLoad=a;

    fileMenu->addSeparator();
    a = new QAction(Utils::getPixmap("filesave.png" ), tr( "&Save..." ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_S );
    a->setShortcutContext (Qt::WidgetShortcut);
    connect( a, SIGNAL( activated() ), this, SLOT( textSave() ) );
    tb->addAction (a);
    fileMenu->addAction (a);
    actionFileSave=a;

    a = new QAction(QPixmap(), tr( "Export &As... (HTML)" ), this);
    connect( a, SIGNAL( activated() ), this, SLOT( textSaveAs() ) );
    fileMenu->addAction (a);
    actionFileSaveAs=a;

    a = new QAction(QPixmap(), tr( "Export &As...(ASCII)" ), this);
    a->setShortcut(Qt::ALT + Qt::Key_X );
    connect( a, SIGNAL( activated() ), this, SLOT( textExportAsASCII() ) );
    fileMenu->addAction (a);
    actionFileSaveAs=a;

    fileMenu->addSeparator();
    a = new QAction(Utils::getPixmap("fileprint.png" ), tr( "&Print..." ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_P );
    connect( a, SIGNAL( activated() ), this, SLOT( textPrint() ) );
    tb->addAction (a);
    fileMenu->addAction (a);
    actionFilePrint=a;

    a = new QAction( Utils::getPixmap("edittrash.png"), tr( "&Delete All" ), this);
    connect( a, SIGNAL( activated() ), e, SLOT( clear() ) );
    fileMenu->addAction (a);
    tb->addAction (a);
    actionFileDeleteAll=a;

    fileMenu->addSeparator();

    // ��ʾ�ñʼǱ�����Note
    a = new QAction( Utils::getPixmap("notes.png"), tr( "&All notes" ), this);
    connect( a, SIGNAL( activated() ), this, SLOT( showNotes() ) );
    tb->addSeparator();
    tb->addAction (a);
    tb->addSeparator();

}

void TextEditor::showNotes()
{
    emit showMainNotes();
//    m_notesdlg = new NotesDialog(this);
//    connect(m_notesdlg, SIGNAL(showAddNoteWidget()), this, SLOT(showSelf()));
//    connect(m_notesdlg, SIGNAL(closeNoteWidget()), this, SLOT(hideSelf()));

//    bool hasSelRight = false;
//    // ��ѡ���ĵ�
//    if(!filename.isEmpty()) {
//        hasSelRight = true;
//        m_notesdlg->exec();
//        if(m_notesdlg->update){
//          // �����κβ���
//        }
//    }
//    // ���û��ѡ����Ŀ¼�ڵ�
//    if(!hasSelRight){
//        QMessageBox::warning(0, tr("Warning"), tr("Please Select an Document."), QMessageBox::Yes);
//        return;
//    }
}

void TextEditor::showSelf()
{
    this->show();
    this->parentWidget()->show();
}
void TextEditor::hideSelf()
{
    this->hide();
    this->parentWidget()->hide();
}

void TextEditor::setupEditActions()
{
    QToolBar *editToolBar = addToolBar ( tr( "Edit Actions" ));
    editToolBar->setObjectName ("noteEditorEditActions");
    editToolBar->hide();
    QMenu *editMenu = menuBar()->addMenu ( tr( "&Edit" ));

    QAction *a;
    a = new QAction(Utils::getPixmap("undo.png"), tr( "&Undo" ), this );
    a->setShortcut(Qt::CTRL + Qt::Key_Z );
    connect( a, SIGNAL( activated() ), e, SLOT( undo() ) );
    editMenu->addAction (a);
    editToolBar->addAction (a);
    actionEditUndo=a;

    a = new QAction(Utils::getPixmap("redo.png" ), tr( "&Redo" ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_Y );
    connect( a, SIGNAL( activated() ), e, SLOT( redo() ) );
    editMenu->addAction (a);
    editToolBar->addAction (a);
    actionEditRedo=a;

    editMenu->addSeparator();
    a = new QAction(QPixmap(), tr( "Select and copy &all" ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_A );
    connect( a, SIGNAL( activated() ), this, SLOT( editCopyAll() ) );
    editMenu->addAction (a);

    editMenu->addSeparator();
    a = new QAction(Utils::getPixmap("editcopy.png" ), tr( "&Copy" ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_C );
    connect( a, SIGNAL( activated() ), e, SLOT( copy() ) );
    editMenu->addAction (a);
    editToolBar->addAction (a);
    actionEditCopy=a;

    a = new QAction(Utils::getPixmap("editcut.png" ), tr( "Cu&t" ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_X );
    connect( a, SIGNAL( activated() ), e, SLOT( cut() ) );
    editMenu->addAction (a);
    editToolBar->addAction (a);
    actionEditCut=a;

    a = new QAction(Utils::getPixmap("editpaste.png" ), tr( "&Paste" ),this);
    a->setShortcut( Qt::CTRL + Qt::Key_V );
    connect( a, SIGNAL( activated() ), e, SLOT( paste() ) );
    editMenu->addAction (a);
    editToolBar->addAction (a);
    actionEditPaste=a;
}

void TextEditor::setupFormatActions()
{
    QToolBar *tb = addToolBar ( tr("Format Actions" ));
    tb->setObjectName ("noteEditorFormatActions");
    QMenu *formatMenu = menuBar()->addMenu ( tr( "F&ormat" ));

    QAction *a;

    a = new QAction(Utils::getPixmap("formatfixedfont.png"), tr( "&Font hint" ), this );
    a->setShortcut(Qt::ALT + Qt::Key_I);
    a->setCheckable (true);
    //a->setChecked (settings.value("/noteeditor/fonts/useFixedByDefault",false).toBool() );
    connect( a, SIGNAL( activated() ), this, SLOT( toggleFonthint() ) );
    formatMenu->addAction (a);
    tb->addAction (a);
    actionFormatUseFixedFont=a;

    a = new QAction( QPixmap(), tr( "&Richtext" ), this );
    a->setShortcut (Qt::ALT + Qt::Key_R);
    a->setCheckable (true);
    //a->setChecked (settings.value("/noteeditor/fonts/useFixedByDefault",false).toBool() );
    connect( a, SIGNAL( activated() ), this, SLOT( toggleRichText() ) );
    formatMenu->addAction (a);
    tb->addAction (a);
    actionFormatRichText=a;

    comboFont = new QComboBox;
    tb->addWidget (comboFont);
    QFontDatabase fontDB;
    comboFont->insertItems ( 0,fontDB.families() );
    connect( comboFont, SIGNAL( activated( const QString & ) ),
         this, SLOT( textFamily( const QString & ) ) );

    comboSize = new QComboBox;
    tb->addWidget (comboSize);
    QList<int> sizes=fontDB.standardSizes();
    QList<int>::iterator it = sizes.begin();
    int i=0;
    while (it != sizes.end()) //FIXME-3 check and make better...
    {
        i++;
        ++it; // increment i before using it
        comboSize->insertItem ( i, QString::number(*it));
    }
    connect( comboSize, SIGNAL( activated( const QString & ) ),
         this, SLOT( textSize( const QString & ) ) );

    formatMenu->addSeparator();

    QPixmap pix( 16, 16 );
//    pix.fill( e->textColor());
    a = new QAction( pix, tr( "&Color..." ), this);
    formatMenu->addAction (a);
    tb->addAction (a);
    connect( a, SIGNAL( activated() ), this, SLOT( textColor() ) );
    actionTextColor=a;

    a = new QAction(Utils::getPixmap("text_bold.png"), tr( "&Bold" ), this);
    a->setShortcut(Qt::CTRL + Qt::Key_B );
    connect( a, SIGNAL( activated() ), this, SLOT( textBold() ) );
    tb->addAction (a);
    formatMenu->addAction (a);
    a->setCheckable( true );
    actionTextBold=a;

    a = new QAction(Utils::getPixmap("text_italic.png"), tr( "&Italic" ),  this);
    a->setShortcut(Qt::CTRL + Qt::Key_I);
    connect( a, SIGNAL( activated() ), this, SLOT( textItalic() ) );
    tb->addAction (a);
    formatMenu->addAction (a);
    a->setCheckable( true );
    actionTextItalic=a;

    a = new QAction(Utils::getPixmap("text_under.png"), tr( "&Underline" ), this);
    a->setShortcut(Qt::CTRL + Qt::Key_U );
    connect( a, SIGNAL( activated() ), this, SLOT( textUnderline() ) );
    tb->addAction (a);
    formatMenu->addAction (a);
    a->setCheckable( true );
    //richTextWidgets.append((QWidget*)a);
    actionTextUnderline=a;
    formatMenu->addSeparator();

    QActionGroup *grp2 = new QActionGroup( this );
    grp2->setExclusive(true);
    a = new QAction(Utils::getPixmap("text_sub.png"), tr( "Subs&cript" ),grp2 );
    a->setShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_B );
    a->setCheckable( true );
    tb->addAction (a);
    formatMenu->addAction (a);
    connect(a, SIGNAL(activated()), this, SLOT(textVAlign()));
    actionAlignSubScript=a;

    a = new QAction(Utils::getPixmap("text_super.png"), tr( "Su&perscript" ),grp2  );
    a->setShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_P );
    a->setCheckable( true );
    tb->addAction (a);
    formatMenu->addAction (a);
    connect(a, SIGNAL(activated()), this, SLOT(textVAlign()));
    actionAlignSuperScript=a;
    QActionGroup *grp = new QActionGroup( this );
    connect( grp, SIGNAL( selected( QAction* ) ), this, SLOT( textAlign( QAction* ) ) );

    formatMenu->addSeparator();

    a = new QAction(Utils::getPixmap("text_left.png"), tr( "&Left" ),grp );
    //a->setShortcut( Qt::CTRL+Qt::Key_L );
    a->setCheckable( true );
    tb->addAction (a);
    formatMenu->addAction (a);
    actionAlignLeft=a;
    a = new QAction(Utils::getPixmap("text_center.png"), tr( "C&enter" ),grp);
    //a->setShortcut(  Qt::CTRL + Qt::Key_E);
    a->setCheckable( true );
    tb->addAction (a);
    formatMenu->addAction (a);
    actionAlignCenter=a;
    a = new QAction( Utils::getPixmap("text_right.png" ), tr( "&Right" ), grp);
    //a->setShortcut(Qt::CTRL + Qt::Key_R );
    a->setCheckable( true );
    tb->addAction (a);
    formatMenu->addAction (a);
    actionAlignRight=a;
    a = new QAction( Utils::getPixmap("text_block.png"), tr( "&Justify" ), grp );
    //a->setShortcut(Qt::CTRL + Qt::Key_J );
    a->setCheckable( true );
    tb->addAction (a);
    formatMenu->addAction (a);
    actionAlignJustify=a;
}

void TextEditor::setupSettingsActions()
{
    QMenu *settingsMenu = menuBar()->addMenu ( tr( "&Settings" ));

    QAction *a;
    a = new QAction(tr( "Set &fixed font" ), this);
    connect( a, SIGNAL( activated() ), this, SLOT( setFixedFont() ) );
    settingsMenu->addAction (a);
    actionSettingsFixedFont=a;

    a = new QAction(tr( "Set &variable font" ), this);
    connect( a, SIGNAL( activated() ), this, SLOT( setVarFont() ) );
    settingsMenu->addAction (a);
    actionSettingsVarFont=a;

    a = new QAction(tr( "&fixed font is default" ),  this);
    a->setCheckable (true);
    // set state later in constructor...
    settingsMenu->addAction (a);
    actionSettingsFonthintDefault=a;
}

void TextEditor::textLoad()
{
    if (state!=inactiveEditor)
    {
        if (!isEmpty())
        {
            QMessageBox mb( vymName + " - " +tr("Note Editor"),
                "Loading will overwrite the existing note",
                QMessageBox::Warning,
                QMessageBox::Yes | QMessageBox::Default,
                QMessageBox::Cancel,
                0 );
            mb.setButtonText( QMessageBox::Yes, "Load note" );
            switch( mb.exec() ) {
                case QMessageBox::Cancel:
                    return;
                    break;
            }
        }
        // Load note
        QFileDialog *fd=new QFileDialog( this);
        QStringList types;
        types<< "Text (*.txt *.html)"<<
            "VYM notes and HTML (*.html)" <<
            "ASCII texts (*.txt)" <<
            "All files (*)";
        fd->setFilters (types);
        fd->setDirectory (QDir().current());
        fd->show();
        QString fn;
        if ( fd->exec() == QDialog::Accepted &&!fd->selectedFiles().isEmpty() )
            fn = fd->selectedFiles().first();

        if ( !fn.isEmpty() )
        {
            QFile f( fn );
            if ( !f.open( QIODevice::ReadOnly ) )
            return;

            QTextStream ts( &f );
            setText( ts.readAll() );
            editorChanged();
        }
    }
}

void TextEditor::closeEvent( QCloseEvent* ce )
{
    ce->accept();   // TextEditor can be reopened with show()
    showwithmain=false;
    hide();
    emit (windowClosed() );
    return;
}

void TextEditor::editorChanged()
{
    if (isEmpty())
        state=emptyEditor;
    else
        state=filledEditor;
        if (state==emptyEditor)
            setState (emptyEditor);
        else
            setState (filledEditor);
    if (!blockChangedSignal) emit (textHasChanged() );
}


void TextEditor::setText(const QString &t)
{
    blockChangedSignal=true;
    //e->setReadOnly(false);
    reset();
    if (Qt::mightBeRichText (t))
    {
        //e->setHtml(t);
        actionFormatRichText->setChecked (true);
    } else
    {
        actionFormatUseFixedFont->setChecked (true);
        //e->setPlainText(t);
        actionFormatRichText->setChecked (false);
    }
    updateActions();
    blockChangedSignal=false;
}

void TextEditor::setInactive()
{
    state=inactiveEditor;
    setText("");
    setState (inactiveEditor);
    //e->setReadOnly (true);

    updateActions();
}

void TextEditor::editCopyAll()
{
    //e->selectAll();
    //e->copy();
}

void TextEditor::textSaveAs()	//FIXME-3 Use WarningDialog
{
    QString caption=tr ("Export Note to single file");
    QString fn = QFileDialog::getSaveFileName(this, caption, QString::null, "Note (HTML) (*.html);;All files (*)",0,QFileDialog::DontConfirmOverwrite );

    if ( !fn.isEmpty() )
    {
        QFile file (fn);
        if (file.exists())
        {
            QMessageBox mb( vymName,
                tr("The file %1\nexists already.\nDo you want to overwrite it?","dialog 'save note as'").arg(fn),
            QMessageBox::Warning,
            QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::Cancel | QMessageBox::Escape,
            Qt::NoButton );
            mb.setButtonText( QMessageBox::Yes, tr("Overwrite") );
            mb.setButtonText( QMessageBox::No, tr("Cancel"));
            switch( mb.exec() ) {
                case QMessageBox::Yes:
                    // save
                    filename = fn;
                    textSave();
                    return;
                case QMessageBox::Cancel:
                    // do nothing
                    break;
            }
        } else
        {
            filename = fn;
            textSave();
            return;
        }
    }
    statusBar()->showMessage(tr( "Couldn't export note ","dialog 'save note as'") + fn, statusbarTime );
}


void TextEditor::textSave()
{
    QString notesPath = Utils::getLocateNotesPath();
    Preferences* p = Preferences::instance();
    if(filename.isEmpty()){
        filename = notesPath.append(QDir::separator());
        noteuuId = QUuid::createUuid().toString();
        filename.append(noteuuId);
        filename.append(".html");
        // ����note��
        Note note;
        note.NOTE_GUID = noteuuId;
        //����docUuid ��Ҫ�ж�NotesDialogɾ��ĳһ��ע���,�ٱ༭����ñ�ע��
        //���������ֱ�ӹرոô���
        p->setSelNoteUid(noteuuId);

        QString m_docUuid = p->getSelDocUid();
        note.DOCUMENT_GUID = m_docUuid;
        note.NOTE_CONTENT = //e->toPlainText();
        NoteDao::insertNote(note);
    }else{
        // ����note��
        QString selNoteUid = p->getSelNoteUid();
        if(!selNoteUid.isEmpty()){
           noteuuId = selNoteUid;
        }
        Note note;
        note.NOTE_GUID = noteuuId;
        QString m_docUuid = p->getSelDocUid();
        note.DOCUMENT_GUID = m_docUuid;
        note.NOTE_CONTENT = //e->toPlainText();
        NoteDao::updateNote(note);
    }

//    QString text = e->toHtml(); //FIXME-3 or plaintext? check...
    QFile f( filename );

    QTextStream t( &f );
    //t << text;
    f.close();

    //e->document()->setModified( false );
}

void TextEditor::textExportAsASCII()
{
    //QString text = NoteObj (e->toPlainText()).getNoteASCII();
    QString fn,s;
    if (!filenameHint.isEmpty())
    {
        if (!filenameHint.contains (".txt"))
            s=filenameHint+".txt";
        else
            s=filenameHint;
    } else
        s=QString::null;
    QString caption=tr("Export Note to single file (ASCII)");
    fn = QFileDialog::getSaveFileName(this, caption, s, "VYM Note (ASCII) (*.txt);;All files (*)" );
    int ret=-1;

    if ( !fn.isEmpty() )
    {
        QFile file (fn);
        if (file.exists())
        {
            QMessageBox mb( vymName,
                tr("The file %1\nexists already.\nDo you want to overwrite it?","dialog 'save note as'").arg(fn),
            QMessageBox::Warning,
            QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::Cancel | QMessageBox::Escape,
            Qt::NoButton );
            mb.setButtonText( QMessageBox::Yes, tr("Overwrite") );
            mb.setButtonText( QMessageBox::No, tr("Cancel"));
            ret=mb.exec();
        }
        if (ret==QMessageBox::Cancel)
            return;

        // save
        if ( !file.open( QIODevice::WriteOnly ) )
            statusBar()->showMessage( QString("Could not write to %1").arg(filename),
                          statusbarTime );
        else
        {
            QTextStream t( &file );
            //t << text;
            file.close();

            statusBar()->showMessage( QString( "Note exported as %1" ).arg( fn ), statusbarTime );
        }
    }
}


void TextEditor::textPrint()
{
    QTextDocument *document = 0;//e->document();

//    QPrintDialog dialog (printer, this);
//    dialog.setWindowTitle(tr("Print","TextEditor"));
//    if (dialog.exec() != QDialog::Accepted)
//        return;

//    document->print(printer);
}

void TextEditor::textEditUndo()
{
}

void TextEditor::toggleFonthint()
{
    setUpdatesEnabled (false);
    //e->selectAll ();
    if (!actionFormatUseFixedFont->isChecked() )
        //e->setCurrentFont (varFont);
    //else
        //e->setCurrentFont (fixedFont);
    //e->selectAll ();
    setUpdatesEnabled (true);
    repaint();
}

void TextEditor::toggleRichText()
{
    //setUpdatesEnabled (false);
    if (!actionFormatRichText->isChecked() )
        //e->setPlainText (e->toPlainText());
    //else
        //e->setHtml (e->toHtml());
    updateActions();
}

void TextEditor::setFixedFont()
{
    bool ok;
    QFont font =QFontDialog::getFont(
                    &ok, fixedFont, this );
    if ( ok )
        // font is set to the font the user selected
        fixedFont=font;
}

void TextEditor::setVarFont()
{
    bool ok;
    QFont font =QFontDialog::getFont(
                    &ok, varFont, this );
    if ( ok )
        // font is set to the font the user selected
        varFont=font;
}

void TextEditor::textBold()
{
    if ( actionTextBold->isChecked()){
    }
        //e->setFontWeight( QFont::Bold );
    //else
        //e->setFontWeight( QFont::Normal);
}

void TextEditor::textUnderline()
{
    //e->setFontUnderline( actionTextUnderline->isChecked() );
}

void TextEditor::textItalic()
{
    //e->setFontItalic( actionTextItalic->isChecked() );
}

void TextEditor::textFamily( const QString &f )
{
    //e->setFontFamily( f );
}

void TextEditor::textSize( const QString &p )
{
    //e->setFontPointSize( p.toInt() );
}


void TextEditor::textColor()
{
    //QColor col = QColorDialog::getColor( //e->textColor(), this );
    //if ( !col.isValid() ) return;
    //e->setTextColor( col );
    QPixmap pix( 16, 16 );
    pix.fill( Qt::black );
    actionTextColor->setIcon( pix );
}

void TextEditor::textAlign( QAction *a )
{
//    QTextCursor c=e->textCursor();
//    c.setPosition (3,QTextCursor::MoveAnchor);
//    //e->setTextCursor (c);

    if ( a == actionAlignLeft ){
    }
        //e->setAlignment( Qt::AlignLeft );
    //else if ( a == actionAlignCenter )
        //e->setAlignment( Qt::AlignHCenter );
    //else if ( a == actionAlignRight )
        //e->setAlignment( Qt::AlignRight );
    //else if ( a == actionAlignJustify )
        //e->setAlignment( Qt::AlignJustify );
}

void TextEditor::textVAlign()
{
    QTextCharFormat format;

    if ( sender() == actionAlignSuperScript && actionAlignSuperScript->isChecked()) {
        format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    } else if (sender() == actionAlignSubScript && actionAlignSubScript->isChecked()) {
        format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    } else {
        format.setVerticalAlignment(QTextCharFormat::AlignNormal);
    }
    //e->mergeCurrentCharFormat(format);
}


void TextEditor::fontChanged( const QFont &f )
{
    int i=comboFont->findText(f.family());
    if (i>=0) comboFont->setCurrentIndex (i);
    i=comboSize->findText(QString::number(f.pointSize()));
    if (i>=0) comboSize->setCurrentIndex(i);
    actionTextBold->setChecked( f.bold() );
    actionTextItalic->setChecked( f.italic() );
    actionTextUnderline->setChecked( f.underline() );
}

void TextEditor::colorChanged( const QColor &c )
{
    QPixmap pix( 16, 16 );
    pix.fill( c );
    actionTextColor->setIcon( pix );
}

void TextEditor::formatChanged( const QTextCharFormat &f )
{
    fontChanged(f.font());
    //colorChanged(f.foreground().color());
    //alignmentChanged(e->alignment());
    verticalAlignmentChanged (f.verticalAlignment());
}

void TextEditor::alignmentChanged( int a )
{
    if ( ( a == Qt::AlignLeft ) || ( a & Qt::AlignLeft ))
        actionAlignLeft->setChecked( true );
    else if ( ( a & Qt::AlignHCenter ) )
        actionAlignCenter->setChecked( true );
    else if ( ( a & Qt::AlignRight ) )
        actionAlignRight->setChecked( true );
    else if ( ( a & Qt::AlignJustify ) )
        actionAlignJustify->setChecked( true );
}

void TextEditor::verticalAlignmentChanged(QTextCharFormat::VerticalAlignment a)
{
    actionAlignSubScript->setChecked (false);
    actionAlignSuperScript->setChecked (false);
    switch (a)
    {
        case QTextCharFormat::AlignSuperScript:
            actionAlignSuperScript->setChecked (true);
            break;
        case QTextCharFormat::AlignSubScript:
            actionAlignSubScript->setChecked (true);
            break;
        default: ;
    }
}

void TextEditor::updateActions()
{
    bool b;
    if (state==inactiveEditor)
        b=false;
    else
        b=true;
    actionFileLoad->setEnabled(b);
    actionFileSave->setEnabled(b);
    actionFileSaveAs->setEnabled(b);
    actionFilePrint->setEnabled(b);
    actionFileDeleteAll->setEnabled(b);
    actionEditUndo->setEnabled(b);
    actionEditRedo->setEnabled(b);
    actionEditCopy->setEnabled(b);
    actionEditCut->setEnabled(b);
    actionEditPaste->setEnabled(b);
    actionFormatUseFixedFont->setEnabled(b);
    actionFormatRichText->setEnabled(b);

    if (!actionFormatRichText->isChecked() || !b)
    {
        comboFont->setEnabled (false);
        comboSize->setEnabled (false);
        actionTextColor->setEnabled (false);
        actionTextBold->setEnabled (false);
        actionTextUnderline->setEnabled(false);
        actionTextItalic->setEnabled(false);
        actionTextColor->setEnabled(false);
        actionAlignSubScript->setEnabled(false);
        actionAlignSuperScript->setEnabled(false);
        actionAlignLeft->setEnabled(false);
        actionAlignCenter->setEnabled(false);
        actionAlignRight->setEnabled(false);
        actionAlignJustify->setEnabled(false);
    }
    else
    {
        comboFont->setEnabled (true);
        comboSize->setEnabled (true);
        actionTextColor->setEnabled (true);
        actionTextBold->setEnabled (true);
        actionTextUnderline->setEnabled(true);
        actionTextItalic->setEnabled(true);
        actionTextColor->setEnabled(true);
        actionAlignSubScript->setEnabled(true);
        actionAlignSuperScript->setEnabled(true);
        actionAlignLeft->setEnabled(true);
        actionAlignCenter->setEnabled(true);
        actionAlignRight->setEnabled(true);
        actionAlignJustify->setEnabled(true);
    }
}



void TextEditor::setState (EditorState s)
{

    QPalette p=palette();
    QColor c;
    switch (s)
    {
        case emptyEditor:    c=QColor (150,150,150); break;
        case filledEditor:   c=QColor (255,255,255); break;
        case inactiveEditor: c=QColor (0,0,0);
    }
    p.setColor(QPalette::Active, static_cast<QPalette::ColorRole>(9), c);
    p.setColor(QPalette::Inactive, static_cast<QPalette::ColorRole>(9), c);
    //e->setPalette(p);
}

