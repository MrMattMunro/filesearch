// The definition of the Qt specific subclass of ScintillaBase.
//
// Copyright (c) 2010 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of QScintilla.
// 
// This file may be used under the terms of the GNU General Public
// License versions 2.0 or 3.0 as published by the Free Software
// Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
// included in the packaging of this file.  Alternatively you may (at
// your option) use any later version of the GNU General Public
// License if such license has been publicly approved by Riverbank
// Computing Limited (or its successors, if any) and the KDE Free Qt
// Foundation. In addition, as a special exception, Riverbank gives you
// certain additional rights. These rights are described in the Riverbank
// GPL Exception version 1.1, which can be found in the file
// GPL_EXCEPTION.txt in this package.
// 
// Please review the following information to ensure GNU General
// Public Licensing requirements will be met:
// http://trolltech.com/products/qt/licenses/licensing/opensource/. If
// you are unsure which license is appropriate for your use, please
// review the following information:
// http://trolltech.com/products/qt/licenses/licensing/licensingoverview
// or contact the sales department at sales@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#ifndef SCINTILLAQT_H
#define	SCINTILLAQT_H


#include <qtimer.h>
#include <qclipboard.h>

// These are needed because scintilla class header files don't seem to manage
// their own dependencies properly.
#include <ctype.h>
#include <stdlib.h>
#include "qscintilla2/include/Platform.h"
#include "qscintilla2/include/Scintilla.h"
#include "qscintilla2/src/SVector.h"
#include "qscintilla2/src/SplitVector.h"
#include "qscintilla2/src/Partitioning.h"
#include "qscintilla2/src/CellBuffer.h"
#include "qscintilla2/src/CharClassify.h"
#include "qscintilla2/src/RunStyles.h"
#include "qscintilla2/src/Decoration.h"
#include "qscintilla2/src/Document.h"
#include "qscintilla2/src/Style.h"
#include "qscintilla2/src/XPM.h"
#include "qscintilla2/src/LineMarker.h"
#include "qscintilla2/src/Indicator.h"
#include "qscintilla2/src/ViewStyle.h"
#include "qscintilla2/src/KeyMap.h"
#include "qscintilla2/src/ContractionState.h"
#include "qscintilla2/src/PositionCache.h"
#include "qscintilla2/src/Editor.h"
#include "qscintilla2/src/AutoComplete.h"
#include "qscintilla2/src/CallTip.h"
#include "qscintilla2/include/SString.h"
#include "qscintilla2/include/PropSet.h"
#include "qscintilla2/include/Accessor.h"
#include "qscintilla2/include/KeyWords.h"

#include "qscintilla2/src/ScintillaBase.h"


class QPaintEvent;
class QDropEvent;

class QsciScintillaBase;
class SciCallTip;
class SciPopup;


class ScintillaQt : public ScintillaBase
{
	friend class QsciScintillaBase;
	friend class SciCallTip;
	friend class SciPopup;

public:
	ScintillaQt(QsciScintillaBase *qsb_);
	virtual ~ScintillaQt();

	virtual sptr_t WndProc(unsigned int iMessage, uptr_t wParam,
            sptr_t lParam);

private:
	void Initialise();
	void Finalise();
	void StartDrag();
	sptr_t DefWndProc(unsigned int, uptr_t, sptr_t);
	void SetTicking(bool);
	void SetMouseCapture(bool on);
	bool HaveMouseCapture();
	void SetVerticalScrollPos();
	void SetHorizontalScrollPos();
	bool ModifyScrollBars(int nMax, int nPage);
	void ReconfigureScrollBars();
	void NotifyChange();
	void NotifyParent(SCNotification scn);
	void CopyToClipboard(const SelectionText &selectedText);
	void Copy();
	void Paste();
	void CreateCallTipWindow(PRectangle rc);
	void AddToPopUp(const char *label, int cmd = 0, bool enabled = true);
	void ClaimSelection();
	void UnclaimSelection();
	static sptr_t DirectFunction(ScintillaQt *sci, unsigned int iMessage,
            uptr_t wParam,sptr_t lParam);

	QString textRange(const SelectionText *text);
	void paintEvent(QPaintEvent *e);
    void pasteFromClipboard(QClipboard::Mode mode);

	bool capturedMouse;
	QsciScintillaBase *qsb;
	QTimer qtimer;
};

#endif
