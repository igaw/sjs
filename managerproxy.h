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

#ifndef MANAGERPROXY_H
#define MANAGERRPOXY_H

#include "manager_interface.h"
#include <QtDBus>
#include <QDebug>

#define CONNMAN_SERVICE		"net.connman"
#define CONNMAN_MANAGER_PATH	"/"

class ManagerProxy : public net::connman::Manager
{
    Q_OBJECT

public:
    ManagerProxy(const QString &service = CONNMAN_SERVICE,
                 const QString &path = CONNMAN_MANAGER_PATH,
                 const QDBusConnection &connection = QDBusConnection::systemBus(),
                 QObject *parent = 0);
    virtual ~ManagerProxy();

private:
    ManagerProxy(const ManagerProxy &);
    ManagerProxy &operator=(ManagerProxy &);
};

#endif
