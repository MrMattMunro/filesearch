/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/
#include <QPainter>
#include <QScrollBar>
#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QStringListModel>

#include <qscintilla2/Qt4/Qsci/qscilexersql.h>
#include <qscintilla2/Qt4/Qsci/qsciapis.h>
#include <qscintilla2/Qt4/Qsci/qsciabstractapis.h>
#include <qscintilla2/Qt4/Qsci/qscilexer.h>

#include "txteditorwidget.h"
#include "preferences.h"
#include "sqlkeywords.h"
#include "utils.h"

#include <QtDebug>

TxtEditorWidget::TxtEditorWidget(QWidget * parent) : QsciScintilla(parent),
      m_searchText(""),
      m_searchIndicator(9) // see QsciScintilla docs
{
	m_prefs = Preferences::instance();

	setMarginLineNumbers(0, true);
	setBraceMatching(SloppyBraceMatch);
	setAutoIndent(true);

	QsciLexerSQL * lexer = new QsciLexerSQL(this);

        //lexer->setAPIs(sqlKeywords());

	QsciAPIs * api = new QsciAPIs(lexer);
//        if (!api->load(":/api/sqlite.api"))
//            qDebug("api is not loaded");
//	else
//	{
//		api->prepare();
//                lexer->setAPIs(api);
//	}

        if (!api->load(":/api/sqlite.api"))
            qDebug("api is not loaded");
        else
        {
                api->prepare();
                lexer->setAPIs(api);
        }

	setAutoCompletionSource(QsciScintilla::AcsAll);
	setAutoCompletionCaseSensitivity(false);
	setAutoCompletionReplaceWord(true);

        setCaretLineVisible(m_prefs->activeHighlighting());
        setCaretLineBackgroundColor(m_prefs->activeHighlightColor());

	setUtf8(true);

	setFolding(QsciScintilla::BoxedFoldStyle);
	lexer->setFoldComments(true);
	lexer->setFoldCompact(false);


        setLexer(lexer);

        // search all occurrences
        // allow indicator painting *under* the text (but it makes editor slower a bit...)
        // It paints a colored box under the text for all occurrences of m_searchText.
        SendScintilla(QsciScintilla::SCI_SETTWOPHASEDRAW, 1);
        SendScintilla(QsciScintilla::SCI_INDICSETSTYLE, m_searchIndicator, QsciScintilla::INDIC_ROUNDBOX);
        // TODO/FIXME: make it configurable
        SendScintilla(QsciScintilla::SCI_INDICSETFORE, m_searchIndicator, QColor(255, 230, 90, 100));
        SendScintilla(QsciScintilla::SCI_INDICSETUNDER, m_searchIndicator, 1);
       // end of search all occurrences

	connect(this, SIGNAL(linesChanged()),
			this, SLOT(linesChanged()));
	connect(this, SIGNAL(cursorPositionChanged(int, int)),
			this, SLOT(cursorPositionChanged(int, int)));

	setCursorPosition(0, 0);
	linesChanged();
	prefsChanged();
}

void TxtEditorWidget::highlightAllOccurrences(const QString & s,
                                               bool caseSensitive,
                                               bool wholeWords)
{
    if (s == m_searchText)
        return;

    m_searchText = s;

    // find and highlight all occurrences of m_searchText
    // from the beginning to the end
    int from = 0;
    int to = text().length();

    SendScintilla(QsciScintilla::SCI_SETINDICATORCURRENT, m_searchIndicator);
    // clear previously used marked text
    SendScintilla(QsciScintilla::SCI_INDICATORCLEARRANGE, 0, to);

    // set searching flags
    int searchFlags = 0;
    if (caseSensitive)
        searchFlags |= QsciScintilla::SCFIND_MATCHCASE;
    if (wholeWords)
        searchFlags |= QsciScintilla::SCFIND_WHOLEWORD;

    while (from < to)
    {
        // set searching range
        SendScintilla(QsciScintilla::SCI_SETTARGETSTART, from);
        SendScintilla(QsciScintilla::SCI_SETTARGETEND, to);
        SendScintilla(QsciScintilla::SCI_SETSEARCHFLAGS, searchFlags);
        from = SendScintilla(QsciScintilla::SCI_SEARCHINTARGET,
                            m_searchText.length(), m_searchText.toUtf8().data());

        // SCI_SEARCHINTARGET returns -1 when it doesn't find anything
        if (from == -1)
            break;

        int end = SendScintilla(QsciScintilla::SCI_GETTARGETEND);
        // mark current occurrence of searchText
        SendScintilla(QsciScintilla::SCI_INDICATORFILLRANGE, from, end - from);
        from = end;
    }
}

void TxtEditorWidget::keyPressEvent(QKeyEvent * e)
{
	// handle editor shortcuts with TAB
	// It uses qscintilla lowlevel API to handle "word unde cursor"
	if (m_prefs->useShortcuts() && e->key() == Qt::Key_Tab)
	{
		int pos = SendScintilla(SCI_GETCURRENTPOS);
		int start = SendScintilla(SCI_WORDSTARTPOSITION, pos,true);
		int end = SendScintilla(SCI_WORDENDPOSITION, pos, true);
		SendScintilla(SCI_SETSELECTIONSTART, start, true);
		SendScintilla(SCI_SETSELECTIONEND, end, true);
		QString key(selectedText());
		bool done = false;
		if (m_prefs->shortcuts().contains(key))
		{
			removeSelectedText();
			insert(m_prefs->shortcuts().value(key).toString());
			SendScintilla(SCI_SETCURRENTPOS,
						  SendScintilla(SCI_GETCURRENTPOS) +
								  m_prefs->shortcuts().value(key).toString().length());
			done = true;
		}
		pos = SendScintilla(SCI_GETCURRENTPOS);
		SendScintilla(SCI_SETSELECTIONSTART, pos,true);
		SendScintilla(SCI_SETSELECTIONEND, pos, true);

		if (done)
			return;
	}

	// Manual popup with code completion
	if (m_prefs->codeCompletion()
		   && (e->modifiers() & Qt::ControlModifier)
		   && e->key() == Qt::Key_Space)
	{
		autoCompleteFromAll();
		return;
	}

	QsciScintilla::keyPressEvent(e);
}

void TxtEditorWidget::linesChanged()
{
	int x = QString::number(lines()).length() + 1;
	setMarginWidth(0, QString().fill('0', x));
}

#if 0
void TxtEditorWidget::cursorPositionChanged(int line, int)
{
}
#endif

void TxtEditorWidget::prefsChanged()
{
	QFont baseFont(m_prefs->sqlFont());
	baseFont.setPointSize(m_prefs->sqlFontSize());

	lexer()->setFont(baseFont);
	setFont(baseFont);

	QFont defFont(lexer()->font(QsciLexerSQL::Keyword));
	defFont.setBold(true);
	lexer()->setFont(defFont, QsciLexerSQL::Keyword);

//        lexer()->setColor(QColor(12,112,11), QsciLexerSQL::Number);
//        lexer()->setColor(QColor(122,12,131), QsciLexerSQL::SingleQuotedString);
//        lexer()->setColor(QColor(122,12,231), QsciLexerSQL::DoubleQuotedString);
//        lexer()->setColor(QColor(122,12,131), QsciLexerSQL::Comment);
//        lexer()->setColor(QColor(12,123,81), QsciLexerSQL::CommentLine);
//        lexer()->setColor(QColor(12,112,31), QsciLexerSQL::CommentDoc);

	setAutoCompletionThreshold(m_prefs->codeCompletion() ?
								m_prefs->codeCompletionLength() : -1
							  );

	if (m_prefs->textWidthMark())
	{
		setEdgeColumn(m_prefs->textWidthMarkSize());
		setEdgeColor(Qt::gray);
		setEdgeMode(QsciScintilla::EdgeLine);
	}
	else
		setEdgeMode(QsciScintilla::EdgeNone);

	setMarkerBackgroundColor(m_prefs->activeHighlighting() ?
								m_prefs->activeHighlightColor() : paper());
}
