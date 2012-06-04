// This module defines interface to the QsciPrinter class.
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


#ifndef QSCIPRINTER_H
#define QSCIPRINTER_H

#ifdef __APPLE__
extern "C++" {
#endif

#include <qprinter.h>

#include <qscintilla2/Qt4/Qsci/qsciglobal.h>
#include <qscintilla2/Qt4/Qsci/qsciscintilla.h>


class QRect;
class QPainter;
class QsciScintillaBase;


//! \brief The QsciPrinter class is a sub-class of the Qt QPrinter class that
//! is able to print the text of a Scintilla document.
//!
//! The class can be further sub-classed to alter to layout of the text, adding
//! headers and footers for example.
class QSCINTILLA_EXPORT QsciPrinter : public QPrinter
{
public:
    //! Constructs a printer paint device with mode \a mode.
    QsciPrinter(PrinterMode mode = ScreenResolution);

    //! Destroys the QsciPrinter instance.
    virtual ~QsciPrinter();

    //! Format a page, by adding headers and footers for example, before the
    //! document text is drawn on it.  \a painter is the painter to be used to
    //! add customised text and graphics.  \a drawing is true if the page is
    //! actually being drawn rather than being sized.  \a painter drawing
    //! methods must only be called when \a drawing is true.  \a area is the
    //! area of the page that will be used to draw the text.  This should be
    //! modified if it is necessary to reserve space for any customised text or
    //! graphics.  By default the area is relative to the printable area of the
    //! page.  Use QPrinter::setFullPage() because calling printRange() if you
    //! want to try and print over the whole page.  \a pagenr is the number of
    //! the page.  The first page is numbered 1.
    virtual void formatPage(QPainter &painter, bool drawing, QRect &area,
            int pagenr);

    //! Return the number of points to add to each font when printing.
    //!
    //! \sa setMagnification()
    int magnification() const {return mag;}

    //! Sets the number of points to add to each font when printing to \a
    //! magnification.
    //!
    //! \sa magnification()
    virtual void setMagnification(int magnification);

    //! Print a range of lines from the Scintilla instance \a qsb.  \a from is
    //! the first line to print and a negative value signifies the first line
    //! of text.  \a to is the last line to print and a negative value
    //! signifies the last line of text.  true is returned if there was no
    //! error.
    virtual int printRange(QsciScintillaBase *qsb, int from = -1, int to = -1);

    //! Return the line wrap mode used when printing.  The default is
    //! QsciScintilla::WrapWord.
    //!
    //! \sa setWrapMode()
    QsciScintilla::WrapMode wrapMode() const {return wrap;}

    //! Sets the line wrap mode used when printing to \a wmode.
    //!
    //! \sa wrapMode()
    virtual void setWrapMode(QsciScintilla::WrapMode wmode);

private:
    int mag;
    QsciScintilla::WrapMode wrap;

    QsciPrinter(const QsciPrinter &);
    QsciPrinter &operator=(const QsciPrinter &);
};

#ifdef __APPLE__
}
#endif

#endif
