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

#ifndef SESSIONPROXY_H
#define SESSIONRPOXY_H

#include "session_interface.h"
#include <QtDBus>
#include <QDebug>

class SessionProxy : public net::connman::Session
{
    Q_OBJECT

public:
    SessionProxy(const QString &service,
                 const QString &path,
                 const QDBusConnection &connection = QDBusConnection::systemBus(),
                 QObject *parent = 0);
    virtual ~SessionProxy();

private:
    SessionProxy(const SessionProxy &);
    SessionProxy &operator=(SessionProxy &);
};

#endif
