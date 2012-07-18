/****************************************************************************
 **
 ** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include <QtGui>

 #include "highlighter.h"
 #include "preferences.h"

 Highlighter::Highlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
 {
     HighlightingRule rule;

     keywordFormat.setForeground(Qt::darkBlue);
     keywordFormat.setFontWeight(QFont::Bold);
     QStringList keywordPatterns;

     // 判断是否为代码文件
    Preferences* p = Preferences::instance();
    QString filepath = p->getOpenDoc();

    // 后缀名
    int dotpos = filepath.lastIndexOf(".");
    QString dotsuffix = filepath.right(filepath.length() - dotpos);
    QString suffix = "*" + dotsuffix;

    if(p->sources().contains(suffix)){
         // c++
         if(suffix == "*.cpp" || suffix == "*.h" || suffix == "*.hpp"
                 || suffix == "*.hpp" || suffix == "*.cc"){

             keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                             << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                             << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                             << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                             << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                             << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                             << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                             << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                             << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                             << "\\bvoid\\b" << "\\bvolatile\\b";
         }
         // java
         if(suffix == "*.java" ){
             keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                             << "\\bdouble\\b" << "\\benum\\b" << "\\binline\\b"
                             << "\\bint\\b" << "\\blong\\b" << "\\bshort\\b"
                             << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                             << "\\bList\\b" << "\\breturn\\b" << "\\btry\\b" << "\\bstatic\\b"
                             << "\\bcatch\\b" << "\\bfor\\b" << "\\bIterator\\b"
                             << "\\bnew\\b" << "\\bpackage\\b" << "\\bimport\\b"
                             << "\\bStringBuffer\\b" << "\\bMap\\b" << "\\bString\\b"
                             << "\\bfinal\\b" << "\\bMap\\b" << "\\babstract\\b"
                             << "\\bboolean\\b" << "\\bbreak\\b" << "\\bbyte\\b"
                             << "\\bcase\\b" << "\\bswitch\\b" << "\\bbcontinue\\b"
                             << "\\bdefault\\b" << "\\bdo\\b"
                             << "\\belse\\b" << "\\bextends\\b" << "\\bfalse\\b"
                             << "\\bfloat\\b" << "\\bif\\b" << "\\binstanceof\\b"
                             << "\\binterface\\b" << "\\bnative\\b" << "\\bnull\\b"
                             << "\\bsuper\\b" << "\\bsynchronized\\b" << "\\bthis\\b"
                             << "\\bthrow\\b" << "\\bthrows\\b" << "\\btransient\\b"
                             << "\\bwhile\\b"  << "\\bvoid\\b";
         }
         // php
         if(suffix == "*.php" ){
             keywordPatterns << "\\bbool\\b" << "\\bclassic\\b" << "\\bobject\\b"
                             << "\\barray\\b" << "\\belseif\\b" << "\\bbreakf\\b"
                             << "\\bglobal\\b" << "\\band\\b" << "\\b$argc\\b"
                             << "\\b$argv\\b" << "\\bas\\b" << "\\bcfunction\\b"
                             << "\\bdeclare\\b" << "\\bdie\\b" << "\\bE_ALL\\b"
                             << "\\becho\\b" << "\\bE-ERROE\\b" << "\\bempty\\b"
                             << "\\benddeclare\\b" << "\\bendfor\\b" << "\\bendforeach\\b"
                             << "\\bendif\\b" << "\\bendswithc\\b" << "\\bE_PAESE\\b"
                             << "\\beval\\b" << "\\bE-WARNING\\b" << "\\bexit\\b"
                             << "\\bextends\\b" << "\\bFALSE\\b" << "\\bforeach\\b"
                             << "\\bfunction\\b" << "\\b$HTTP_COOKIE_VARS\\b" << "\\bHTTP_ENV_VARS\\b"
                             << "\\bHTTP_GET_VARS\\b" << "\\bHTTP_POST_VARS\\b" << "\\bHTTP_POST_FILES\\b"
                             << "\\bHTTP_SERVER_VARS\\b" << "\\binclue_once\\b" << "\\bold_function\\b"
                             << "\\bor\\b" << "\\bparents\\b" << "\\btransient\\b";
         }

         // jsp
         if(suffix == "*.jsp" ){
             keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                             << "\\bdouble\\b" << "\\benum\\b" << "\\binline\\b"
                             << "\\bint\\b" << "\\blong\\b" << "\\bshort\\b"
                             << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                             << "\\bList\\b" << "\\breturn\\b" << "\\btry\\b" << "\\bstatic\\b"
                             << "\\bcatch\\b" << "\\bfor\\b" << "\\bIterator\\b"
                             << "\\bnew\\b" << "\\bpackage\\b" << "\\bimport\\b"
                             << "\\bStringBuffer\\b" << "\\bMap\\b" << "\\bString\\b"
                             << "\\bfinal\\b" << "\\bMap\\b" << "\\babstract\\b"
                             << "\\bboolean\\b" << "\\bbreak\\b" << "\\bbyte\\b"
                             << "\\bcase\\b" << "\\bswitch\\b" << "\\bbcontinue\\b"
                             << "\\bdefault\\b" << "\\bdo\\b"
                             << "\\belse\\b" << "\\bextends\\b" << "\\bfalse\\b"
                             << "\\bfloat\\b" << "\\bif\\b" << "\\binstanceof\\b"
                             << "\\binterface\\b" << "\\bnative\\b" << "\\bnull\\b"
                             << "\\bsuper\\b" << "\\bsynchronized\\b" << "\\bthis\\b"
                             << "\\bthrow\\b" << "\\bthrows\\b" << "\\btransient\\b"
                             << "\\bwhile\\b"  << "\\bvoid\\b";
         }
         // javascript
         if(suffix == "*.js" || suffix == "*.jsp"  || suffix == "*.asp"  || suffix == "*.php" ){
             keywordPatterns << "\\bbreak\\b" << "\\bdelete\\b" << "\\bfunction\\b"
                             << "\\breturn\\b" << "\\btypeof\\b" << "\\bcase\\b"
                             << "\\bdo\\b" << "\\bif\\b" << "\\bswitch\\b"
                             << "\\bvar\\b" << "\\bcatch\\b" << "\\belse\\b"
                             << "\\bin\\b" << "\\bthis\\b" << "\\bvoid\\b" << "\\bcontinue\\b"
                             << "\\bfalse\\b" << "\\binstanceof\\b" << "\\bthrow\\b"
                             << "\\bwhile\\b" << "\\bdebugger\\b" << "\\bfinally\\b"
                             << "\\bnew\\b" << "\\btrue\\b" << "\\bwith\\b"
                             << "\\bdefault\\b" << "\\bfor\\b" << "\\bnull\\b"
                             << "\\btry\\b";
         }

         // sql
         if(suffix == "*.sql" ){
             keywordPatterns << "\\bADD\\b" << "\\bALL\\b" << "\\bALTER\\b" << "\\bint\\b"
                             << "\\bDEFAULT\\b"<< "\\bORDER\\b"<< "\\bBY\\b"
                             << "\\bINSERT\\b"<< "\\bINTO\\b"<< "\\bPRIMARY\\b"
                              << "\\bKEY\\b"<< "\\bINTO\\b"<< "\\bPRIMARY\\b" << "\\bIF NOT EXISTS\\b"
                             << "\\bANALYZE\\b" << "\\bAND\\b" << "\\bAS\\b"
                             << "\\bASC\\b" << "\\bASENSITIVE\\b" << "\\bBEFORE\\b"
                             << "\\bBETWEEN\\b" << "\\bBIGINT	\\b" << "\\bBINARY\\b"
                             << "\\bBLOB\\b" << "\\bBOTH\\b" << "\\bBY\\b"
                             << "\\bCALL\\b" << "\\bCASCADE\\b" << "\\bCASE\\b"
                             << "\\bCHANGE\\b" << "\\bCHAR\\b" << "\\bCHARACTER\\b"
                             << "\\bCHECK\\b" << "\\bCOLLATE\\b" << "\\bCOLUMN\\b"
                             << "\\bCONDITION\\b" << "\\bCONNECTION\\b" << "\\bCONSTRAINT\b"
                             << "\\bCONTINUE\\b" << "\\bCONVERT\\b" << "\\bCREATE\\b"
                             << "\\bCROSS\\b" << "\\bCURRENT_DATE\\b" << "\\bCURRENT_TIME\\b"
                             << "\\bCURRENT_TIMESTAMP\\b" << "\\bCURRENT_USER\\b" << "\\bCURSOR\\b"
                             << "\\bDATABASE\\b" << "\\bDATABASES\\b" << "\\bDAY_HOUR\\b"
                             << "\\bDAY_MICROSECOND\\b" << "\\bDAY_MINUTE\\b" << "\\bDAY_SECOND\\b"
                             << "\\bDEC	\\b" << "\\bDECIMAL\\b" << "\\bDECLARE\\b"
                             << "\\bDEFAULT\\b" << "\\bDELAYED\\b" << "\\bDELETE\\b"
                             << "\\bDESC\\b" << "\\bDESCRIBE\\b" << "\\bDETERMINISTIC\\b"
                             << "\\bDISTINCT\\b" << "\\bDISTINCTROW\\b" << "\\bDIV\\b"
                             << "\\bDOUBLE\\b" << "\\bDROP\\b" << "\\bDUAL\\b"
                             << "\\bEACH\\b" << "\\bELSE\\b" << "\\bELSEIF\\b"
                             << "\\bENCLOSED\\b" << "\\bESCAPED	\\b" << "\\bEXISTS\\b"
                             << "\\bEXIT\\b" << "\\bEXPLAIN\\b" << "\\bFALSE\\b"
                             << "\\bFETCH\\b" << "\\bFLOAT\\b" << "\\bFLOAT4\\b"
                             << "\\bFLOAT8\\b" << "\\bFOR\\b" << "\\bFORCE\\b"
                             << "\\bFOREIGN\\b" << "\\bFROM\\b" << "\\bFULLTEXT	\\b"
                             << "\\bGOTO\\b" << "\\bGRANT\\b" << "\\bGROUP\\b"
                             << "\\bHAVING\\b" << "\\bHIGH_PRIORITY\\b" << "\\bHOUR_MICROSECOND\\b"
                             << "\\bHOUR_MINUTE	\\b" << "\\bHOUR_SECOND	\\b" << "\\bIF	\\b"
                             << "\\bIGNORE\\b" << "\\bIN\\b" << "\\bINDEX\\b"
                             << "\\bINFILE\\b" << "\\bINNER\\b" << "\\bINOUT\\b"
                             << "\\bINSENSITIVE	\\b" << "\\bINSERT\\b" << "\\bINT\\b"
                             << "\\bINT1\\b" << "\\bINT2\\b" << "\\bINT3\\b"
                             << "\\bINT4\\b" << "\\bINT8\\b" << "\\bINTEGER\\b"
                             << "\\bINTERVAL\\b" << "\\bINTO\\b" << "\\bIS\\b"
                             << "\\bITERATE\\b" << "\\bJOIN\\b" << "\\bKEY\\b"
                             << "\\bKEYS\\b" << "\\bKILL\\b" << "\\bLABEL\\b"
                             << "\\bLEADING\\b" << "\\bLEAVE\\b" << "\\bLEFT\\b"
                             << "\\bLIKE\\b" << "\\bLIMIT\\b" << "\\bLINEAR\\b"
                             << "\\bLINES\\b" << "\\bLOAD\\b" << "\\bLOCALTIME\\b"
                             << "\\bLOCALTIMESTAMP\\b" << "\\bLOCK\\b" << "\\bLONG\\b"
                             << "\\bLONGBLOB\\b" << "\\bLONGTEXT\\b" << "\\bLOOP\\b"
                             << "\\bLOW_PRIORITY\\b" << "\\bMATCH\\b" << "\\bMEDIUMBLOB	\\b"
                             << "\\bMEDIUMINT\\b" << "\\bMEDIUMTEXT\\b" << "\\bMIDDLEINT\\b"
                             << "\\bMINUTE_MICROSECOND\\b" << "\\bMINUTE_SECOND\\b" << "\\bMOD\\b"
                             << "\\bMODIFIES\\b" << "\\bNATURAL\\b" << "\\bNOT\\b"
                             << "\\bNO_WRITE_TO_BINLOG	\\b" << "\\bNULL\\b" << "\\bNUMERIC\\b"
                             << "\\bON\\b" << "\\bOPTIMIZE\\b" << "\\bOPTION\\b"
                             << "\\bOPTIONALLY	\\b" << "\\bOR\\b" << "\\bORDER\\b"
                             << "\\bOUT\\b" << "\\bOUTER\\b" << "\\bOUTFILE\\b"
                             << "\\bPRECISION\\b" << "\\bPRIMARY\\b" << "\\bPROCEDURE\\b"
                             << "\\bPURGE\\b" << "\\bRAID0\\b" << "\\bRANGE\\b"
                             << "\\bREAD\\b" << "\\bREADS\\b" << "\\bREAL\\b"
                             << "\\bREFERENCES\\b" << "\\bREGEXP\\b" << "\\bRELEASE\\b"
                             << "\\bRENAME\\b" << "\\bREPEAT\\b" << "\\bREPLACE\\b"
                             << "\\bREQUIRE\\b" << "\\bRESTRICT\\b" << "\\bRETURN\\b"
                             << "\\bREVOKE\\b" << "\\bRIGHT\\b" << "\\bRLIKE\\b"
                             << "\\bSCHEMA\\b" << "\\bSCHEMAS\\b" << "\\bSECOND_MICROSECOND\\b"
                             << "\\bSELECT\\b" << "\\bSENSITIVE\\b" << "\\bSEPARATOR\\b"
                             << "\\bSET\\b" << "\\bSHOW\\b" << "\\bSMALLINT\\b"
                             << "\\bSPATIAL\\b" << "\\bSPECIFIC\\b" << "\\bSQL\\b"
                             << "\\bSQLEXCEPTION\\b" << "\\bSQLSTATE\\b" << "\\bSQLWARNING\\b"
                             << "\\bSQL_BIG_RESULT\\b" << "\\bSQL_CALC_FOUND_ROWS\\b" << "\\bSQL_SMALL_RESULT\\b"
                             << "\\bSSL\\b" << "\\bSTARTING\\b" << "\\bSTRAIGHT_JOIN\\b"
                             << "\\bTABLE\\b" << "\\bTERMINATED\\b" << "\\bTHEN\\b"
                             << "\\bTINYBLOB\\b" << "\\bTINYINT\\b" << "\\bTINYTEXT\\b"
                             << "\\bTO\\b" << "\\bTRAILING\\b" << "\\bTRIGGER\\b"
                             << "\\bTRUE\\b" << "\\bUNDO\\b" << "\\bUNION\\b"
                             << "\\bUNIQUE\\b" << "\\bUNLOCK\\b" << "\\bUNSIGNED\\b"
                             << "\\bUPDATE\\b" << "\\bUSAGE\\b" << "\\bUSE\\b"
                             << "\\bUSING\\b" << "\\bUTC_DATE	\\b" << "\\bUTC_TIME\\b"
                             << "\\bUTC_TIMESTAMP\\b" << "\\bVALUES\\b" << "\\bVARBINARY\\b"
                             << "\\bVARCHAR\\b" << "\\bVARCHARACTER\\b" << "\\bVARYING\\b"
                             << "\\bWHEN\\b" << "\\bWHERE\\b" << "\\bWHILE\\b"
                             << "\\bWITH\\b" << "\\bWRITE\\b" << "\\bX509\\b"
                             << "\\bXOR\\b" << "\\bYEAR_MONTH\\b" << "\\bZEROFILL\\b";

         }
     }


    foreach (const QString &pattern, keywordPatterns) {
         rule.pattern = QRegExp(pattern);
         rule.format = keywordFormat;
         highlightingRules.append(rule);
     }

     classFormat.setFontWeight(QFont::Bold);
     classFormat.setForeground(Qt::darkMagenta);
     rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
     rule.format = classFormat;
     highlightingRules.append(rule);

     singleLineCommentFormat.setForeground(Qt::red);
     rule.pattern = QRegExp("//[^\n]*");
     rule.format = singleLineCommentFormat;
     highlightingRules.append(rule);

     multiLineCommentFormat.setForeground(Qt::red);

     quotationFormat.setForeground(Qt::darkGreen);
     rule.pattern = QRegExp("\".*\"");
     rule.format = quotationFormat;
     highlightingRules.append(rule);

     functionFormat.setFontItalic(true);
     functionFormat.setForeground(Qt::blue);
     rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
     rule.format = functionFormat;
     highlightingRules.append(rule);

     commentStartExpression = QRegExp("/\\*");
     commentEndExpression = QRegExp("\\*/");
 }

 void Highlighter::highlightBlock(const QString &text)
 {
     foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = commentStartExpression.indexIn(text);

     while (startIndex >= 0) {
         int endIndex = commentEndExpression.indexIn(text, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex
                             + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, multiLineCommentFormat);
         startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
     }
 }
