#ifndef CMDBUSTYPES_H
#define CMDBUSTYPES_H

#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtDBus/QtDBus>

/* For "a(ao{sv})" */
struct ConnManPathProperties
{
    QDBusObjectPath path;
    QVariantMap     properties;
};

Q_DECLARE_METATYPE ( ConnManPathProperties )

QDBusArgument &operator<<(QDBusArgument &argument, const ConnManPathProperties &properties);
const QDBusArgument &operator>>(const QDBusArgument &argument, ConnManPathProperties &properties);
typedef QList< ConnManPathProperties > QArrayOfPathProperties;

Q_DECLARE_METATYPE ( QArrayOfPathProperties )

inline void registerMyDataTypes()
{
    qDBusRegisterMetaType< ConnManPathProperties >();
    qDBusRegisterMetaType< QArrayOfPathProperties >();
}

#endif
