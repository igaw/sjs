#include "managerproxy.h"

ManagerProxy::ManagerProxy(const QString &service,
			   const QString &path,
			   const QDBusConnection &connection,
			   QObject *parent)
  : net::connman::Manager(service, path, connection, parent)
{
}

ManagerProxy::~ManagerProxy()
{
}
