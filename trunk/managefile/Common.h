/*
 * QEstEidCommon
 *
 * Copyright (C) 2009-2011 Jargo Kõster <jargo@innovaatik.ee>
 * Copyright (C) 2009-2011 Raul Metsma <raul@innovaatik.ee>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#pragma once

//#include "qtsingleapplication/src/QtSingleApplication"

#include <QEvent>
#include <QObject>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#   include <QUrlQuery>
#endif

struct ApplicationStruct;
class QSslCertificate;
class QStringList;
class QUrl;

class Common: public QObject
{
	Q_OBJECT
public:
        Common();
	virtual ~Common();

	virtual QString lastPath() const { return QString(); }
	virtual void setLastPath( const QString & ) {}
	bool noNativeFileDialog() const;
	virtual bool event( QEvent *e );

	static QString applicationOs();
	static bool canWrite( const QString &filename );
	static bool cardsOrder( const QString &s1, const QString &s2 );
	static QString fileSize( quint64 bytes );
	static QString helpUrl();
	static QStringList packages( const QStringList &names, bool withName = true );
	static void showHelp( const QString &msg, int code = -1 );
	static bool startDetached( const QString &program );
	static bool startDetached( const QString &program, const QStringList &arguments );
        static QString tempFilename();

public Q_SLOTS:
	void browse( const QUrl &url );
        void mailTo( const QUrlQuery &url );

private:
	static quint8 cardsOrderScore( const QChar &c );

#if defined(Q_OS_MAC)
	void initMacEvents();
	void deinitMacEvents();
	ApplicationStruct *macEvents;
#endif

	bool m_noNativeFileDialog;
};

class REOpenEvent: public QEvent
{
public:
	enum { Type = QEvent::User + 1 };
	REOpenEvent(): QEvent( QEvent::Type(Type) ) {}
};
