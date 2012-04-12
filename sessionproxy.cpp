#include "sessionproxy.h"

SessionProxy::SessionProxy(const QString &service,
			   const QString &path,
			   const QDBusConnection &connection,
			   QObject *parent)
  : net::connman::Session(service, path, connection, parent)
{
}

SessionProxy::~SessionProxy()
{
}
