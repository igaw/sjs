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

#include "mainwindow.h"
#include "sessionjs.h"

#include "dbustypes.h"
#include "managerproxy.h"

#include <QDBusConnectionInterface>
#include <QDBusConnection>
#include <QDBusServiceWatcher>
#include <QWebFrame>

MainWin::MainWin(QWidget * parent) :
  QWebView(parent), m_manager(NULL)
{
    m_watcher = new QDBusServiceWatcher("net.connman",
                                        QDBusConnection::systemBus(),
                                        QDBusServiceWatcher::WatchForOwnerChange,
                                        this);
    QObject::connect(m_watcher, SIGNAL(serviceOwnerChanged(QString, QString, QString)),
                     this, SLOT(serviceOwnerChanged(QString, QString, QString)));

    QTimer::singleShot(0, this, SLOT(checkForConnMan()));

    m_sessionJS = new SessionJS(this);

    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
                     this, SLOT(addJSObject()));

    setUrl(QUrl("qrc:/index.html"));
}

MainWin::~MainWin()
{
    delete m_sessionJS;
    delete m_manager;
    delete m_watcher;
}

void MainWin::checkForConnMan()
{
    if (m_manager)
        return;

    QDBusConnection bus = QDBusConnection::systemBus();
    QStringList serviceNames = bus.interface()->registeredServiceNames();

    if (serviceNames.contains("net.connman"))
        connmanServiceConnect();
}

void MainWin::connmanServiceConnect()
{
    qDebug("ConnMan appeared");

    m_manager = new ManagerProxy();
    m_sessionJS->setManager(m_manager);
}

void MainWin::connmanServiceDisconnect()
{
    qDebug("ConnMan disappeared");

    m_sessionJS->setManager(NULL);

    delete m_manager;
    m_manager = NULL;
}

void MainWin::serviceOwnerChanged(const QString &serviceName, const QString &oldOwner, const QString &newOwner)
{
    Q_UNUSED(serviceName);
    Q_UNUSED(oldOwner);

    if (!newOwner.isEmpty())
        connmanServiceConnect();
    else
        connmanServiceDisconnect();
}

void MainWin::addJSObject()
{
    page()->mainFrame()->addToJavaScriptWindowObject(QString("sessionJS"), m_sessionJS);
}
