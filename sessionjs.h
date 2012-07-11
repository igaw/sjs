/*
 *  Session API JavaScript Demo
 *
 *  Copyright (C) 2012 BMW Car IT GmbH. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef CONNMANPROXY_H
#define CONNMANPROXY_H

#include <QtGui>

class QString;
class QDBusVariant;

class ManagerProxy;
class SessionProxy;
class NotificationAdaptor;

class SessionJS : public QObject
{
    Q_OBJECT
public:
    SessionJS(QObject * parent=0);
    virtual ~SessionJS();

    void setManager(ManagerProxy *manager);

public slots:
    void do_connect();
    void do_disconnect();

signals:
    void state(QString state);
    void bearer(QString bearer);
    void name(QString name);

private:
    ManagerProxy *m_manager;
    SessionProxy *m_session;
    NotificationAdaptor *m_notification;

private slots:
    void Release();
    void Update(const QVariantMap &settings);
};

#endif
