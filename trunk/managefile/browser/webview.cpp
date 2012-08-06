/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "browserapplication.h"
#include "browsermainwindow.h"
#include "cookiejar.h"
#include "downloadmanager.h"
#include "networkaccessmanager.h"
#include "tabwidget.h"
#include "webview.h"
#include "indexfile.h"
#include "saveurldialog.h"
#include <QtGui/QClipboard>
#include <QtGui/QMenu>
#include <QtGui/QMessageBox>
#include <QtGui/QMouseEvent>
#include <QUuid>
#include <QtWebKit/QWebHitTestResult>

#ifndef QT_NO_UITOOLS
#include <QtUiTools/QUiLoader>
#endif  //QT_NO_UITOOLS

#include <QtCore/QDebug>
#include <QtCore/QBuffer>

WebPage::WebPage(QObject *parent)
    : QWebPage(parent)
    , m_keyboardModifiers(Qt::NoModifier)
    , m_pressedButtons(Qt::NoButton)
    , m_openInNewTab(false)
{
    setNetworkAccessManager(BrowserApplication::networkAccessManager());
    connect(this, SIGNAL(unsupportedContent(QNetworkReply*)),
            this, SLOT(handleUnsupportedContent(QNetworkReply*)));
}

BrowserMainWindow *WebPage::mainWindow()
{
    QObject *w = this->parent();
    while (w) {
        if (BrowserMainWindow *mw = qobject_cast<BrowserMainWindow*>(w))
            return mw;
        w = w->parent();
    }
    return BrowserApplication::instance()->mainWindow();
}

bool WebPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type)
{
    // ctrl open in new tab
    // ctrl-shift open in new tab and select
    // ctrl-alt open in new window
    if (type == QWebPage::NavigationTypeLinkClicked
        && (m_keyboardModifiers & Qt::ControlModifier
            || m_pressedButtons == Qt::MidButton)) {
        bool newWindow = (m_keyboardModifiers & Qt::AltModifier);
        WebView *webView;
        if (newWindow) {
            BrowserMainWindow *newMainWindow = BrowserApplication::instance()->mainWindow();
            webView = newMainWindow->currentTab();
            newMainWindow->raise();
            newMainWindow->activateWindow();
            webView->setFocus();
        } else {
            bool selectNewTab = (m_keyboardModifiers & Qt::ShiftModifier);
            webView = mainWindow()->tabWidget()->newTab(selectNewTab);
        }
        webView->load(request);
        m_keyboardModifiers = Qt::NoModifier;
        m_pressedButtons = Qt::NoButton;
        return false;
    }
    if (frame == mainFrame()) {
        m_loadingUrl = request.url();
        emit loadingUrl(m_loadingUrl);
    }
    return QWebPage::acceptNavigationRequest(frame, request, type);
}

QWebPage *WebPage::createWindow(QWebPage::WebWindowType type)
{
    Q_UNUSED(type);
//    if (m_keyboardModifiers & Qt::ControlModifier || m_pressedButtons == Qt::MidButton){
//        m_openInNewTab = true;
//    }
    //if (m_openInNewTab) {
        m_openInNewTab = true;
        return mainWindow()->tabWidget()->newTab()->page();
//    }
//    BrowserApplication::instance()->newMainWindow();
//    BrowserMainWindow *mainWindow = BrowserApplication::instance()->mainWindow();
//    return mainWindow->currentTab()->page();
}

//#if !defined(QT_NO_UITOOLS)
//QObject *WebPage::createPlugin(const QString &classId, const QUrl &url, const QStringList &paramNames, const QStringList &paramValues)
//{
//    Q_UNUSED(url);
//    Q_UNUSED(paramNames);
//    Q_UNUSED(paramValues);
//    QUiLoader loader;
//    return loader.createWidget(classId, view());
//}
//#endif // !defined(QT_NO_UITOOLS)

void WebPage::handleUnsupportedContent(QNetworkReply *reply)
{
    QString errorString = reply->errorString();

    if (m_loadingUrl != reply->url()) {
        // sub resource of this page
        qWarning() << "Resource" << reply->url().toEncoded() << "has unknown Content-Type, will be ignored.";
        reply->deleteLater();
        return;
    }

    if (reply->error() == QNetworkReply::NoError && !reply->header(QNetworkRequest::ContentTypeHeader).isValid()) {
        errorString = "Unknown Content-Type";
    }

    QFile file(QLatin1String(":/notfound.html"));
    bool isOpened = file.open(QIODevice::ReadOnly);
    Q_ASSERT(isOpened);
    Q_UNUSED(isOpened);

    QString title = tr("Error loading page: %1").arg(reply->url().toString());
    QString html = QString(QLatin1String(file.readAll()))
                        .arg(title)
                        .arg(errorString)
                        .arg(reply->url().toString());

    QBuffer imageBuffer;
    imageBuffer.open(QBuffer::ReadWrite);
    QIcon icon = view()->style()->standardIcon(QStyle::SP_MessageBoxWarning, 0, view());
    QPixmap pixmap = icon.pixmap(QSize(32,32));
    if (pixmap.save(&imageBuffer, "PNG")) {
        html.replace(QLatin1String("IMAGE_BINARY_DATA_HERE"),
                     QString(QLatin1String(imageBuffer.buffer().toBase64())));
    }

    QList<QWebFrame*> frames;
    frames.append(mainFrame());
    while (!frames.isEmpty()) {
        QWebFrame *frame = frames.takeFirst();
        if (frame->url() == reply->url()) {
            frame->setHtml(html, reply->url());
            return;
        }
        QList<QWebFrame *> children = frame->childFrames();
        foreach(QWebFrame *frame, children)
            frames.append(frame);
    }
    if (m_loadingUrl == reply->url()) {
        mainFrame()->setHtml(html, reply->url());
    }
}


WebView::WebView(QWidget* parent)
    : QWebView(parent)
    , m_progress(0)
    , m_page(new WebPage(this))
{
    setPage(m_page);
    connect(page(), SIGNAL(statusBarMessage(QString)),
            SLOT(setStatusBarText(QString)));
    connect(this, SIGNAL(loadProgress(int)),
            this, SLOT(setProgress(int)));
    connect(this, SIGNAL(loadFinished(bool)),
            this, SLOT(loadFinished()));
    connect(page(), SIGNAL(loadingUrl(QUrl)),
            this, SIGNAL(urlChanged(QUrl)));
    connect(page(), SIGNAL(downloadRequested(QNetworkRequest)),
            this, SLOT(downloadRequested(QNetworkRequest)));
    page()->setForwardUnsupportedContent(true);

}

void WebView::contextMenuEvent(QContextMenuEvent *event)
{
    QWebHitTestResult r = page()->mainFrame()->hitTestContent(event->pos());
    if (!r.linkUrl().isEmpty()) {
        QMenu menu(this);
        menu.addAction(pageAction(QWebPage::OpenLinkInNewWindow));
        menu.addAction(tr("Open in New Tab"), this, SLOT(openLinkInNewTab()));
        menu.addSeparator();
        menu.addAction(pageAction(QWebPage::DownloadLinkToDisk));
        // Add link to bookmarks...
        menu.addSeparator();
        menu.addAction(pageAction(QWebPage::CopyLinkToClipboard));
        if (page()->settings()->testAttribute(QWebSettings::DeveloperExtrasEnabled))
            menu.addAction(pageAction(QWebPage::InspectElement));
        menu.exec(mapToGlobal(event->pos()));
        return;
    }else{
        QMenu menu(this);
        menu.addAction(tr("Save to the Solo"), this, SLOT(saveToSlfile()));
        menu.addSeparator();
        menu.addAction(tr("Exit Full Screen"), this, SLOT(exitFullScreen()));
        menu.exec(mapToGlobal(event->pos()));
        return;
    }

    QWebView::contextMenuEvent(event);
}

// 打开保存界面
void WebView::saveToSlfile()
{
   // 打开保存界面
   QUrl url = page()->mainFrame()->url();
   QString locate = Utils::getLocateDownloadPath();

   QString surl = url.toString();
   // title 换成uuid

   QString title = this->title();

   // curPath 用于判断根节点和子节点
   SaveUrlDialog dlg(this);
   dlg.exec();
   if(dlg.update){
       // 保存网页
       Doc doc;
       doc.DOCUMENT_GUID = QUuid::createUuid();
       doc.DOCUMENT_TITLE = title;
       doc.DIR_GUID = dlg.m_toUuid;
       doc.DOCUMENT_LOCATION = locate.append(QDir::separator()).append(doc.DOCUMENT_GUID).append(".html");
       doc.DOCUMENT_NAME = title.append(".html");
       doc.DOCUMENT_SEO = "";
       doc.DOCUMENT_URL = surl;
       doc.DOCUMENT_AUTHOR = "";
       doc.DOCUMENT_KEYWORDS = "";
       doc.DOCUMENT_TYPE = "html";
       doc.DOCUMENT_OWNER = "";
       doc.DT_CREATED = "";
       doc.DT_MODIFIED = "";
       doc.DT_ACCESSED = "";
       doc.DOCUMENT_ICON_INDEX = 0;
       doc.DOCUMENT_SYNC = 0;
       doc.DOCUMENT_PROTECT = "";
       doc.DOCUMENT_ENCODE = "";
       doc.DOCUMENT_READ_COUNT = 1;
       doc.DOCUMENT_RELATE_COUNT = 0;
       doc.DOCUMENT_INDEXFLG = "0";
       doc.DOCUMENT_OPERFLG = "0";
       doc.DELETE_FLAG = "0";
       doc.MF_VERSION = 0;
       DocDao::insertDoc(doc);
       BrowserApplication::downloadManager()->download(url, doc.DOCUMENT_GUID, false);


       // TODO 暂时注释
//       QThread thread;
//       IndexFilesObj indexFilesObj;
//       indexFilesObj.moveToThread(&thread);

//       IndexFilesSign dummy;
//       qDebug()<<"main thread:"<< QThread::currentThreadId();

//       QObject::connect(&dummy, SIGNAL(sig()), &indexFilesObj, SLOT(indexfiles()));
//       thread.start();
//       // 通知主界面改变不可搜索
//       Preferences* p = Preferences::instance();
//       p->setIsIndexing(true);
//       dummy.emitsig();
   }

}

// 左键双击
void WebView::mouseDoubleClickEvent(QMouseEvent *event)
{
   BrowserApplication::mainWindow()->fullScreen();
}

void WebView::exitFullScreen()
{
   BrowserApplication::mainWindow()->fullScreen();
}

void WebView::wheelEvent(QWheelEvent *event)
{
    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;
        setTextSizeMultiplier(textSizeMultiplier() + numSteps * 0.1);
        event->accept();
        return;
    }
    QWebView::wheelEvent(event);
}

void WebView::openLinkInNewTab()
{
    m_page->m_openInNewTab = true;
    pageAction(QWebPage::OpenLinkInNewWindow)->trigger();
}

void WebView::setProgress(int progress)
{
    m_progress = progress;
}

void WebView::loadFinished()
{
    if (100 != m_progress) {
        qWarning() << "Received finished signal while progress is still:" << progress()
                   << "Url:" << url();
    }
    m_progress = 0;
}

void WebView::loadUrl(const QUrl &url)
{
    m_initialUrl = url;
    load(url);
}

QString WebView::lastStatusBarText() const
{
    return m_statusBarText;
}

QUrl WebView::url() const
{
    QUrl url = QWebView::url();
    if (!url.isEmpty())
        return url;

    return m_initialUrl;
}

void WebView::mousePressEvent(QMouseEvent *event)
{
    m_page->m_pressedButtons = event->buttons();
    m_page->m_keyboardModifiers = event->modifiers();
    QWebView::mousePressEvent(event);
}

void WebView::mouseReleaseEvent(QMouseEvent *event)
{
    QWebView::mouseReleaseEvent(event);
    if (!event->isAccepted() && (m_page->m_pressedButtons & Qt::MidButton)) {
        QUrl url(QApplication::clipboard()->text(QClipboard::Selection));
        if (!url.isEmpty() && url.isValid() && !url.scheme().isEmpty()) {
            setUrl(url);
        }
    }
}


void WebView::setStatusBarText(const QString &string)
{
    m_statusBarText = string;
}

void WebView::downloadRequested(const QNetworkRequest &request)
{
    BrowserApplication::downloadManager()->download(request, this->title(), false);
}

