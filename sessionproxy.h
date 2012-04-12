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
