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
