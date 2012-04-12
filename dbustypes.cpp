#include "dbustypes.h"

QDBusArgument &operator<<(QDBusArgument &argument, const ConnManPathProperties &props)
{
    argument.beginStructure();
    argument << props.path << props.properties;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, ConnManPathProperties &props)
{
    argument.beginStructure();
    argument >> props.path >> props.properties;
    argument.endStructure();
    return argument;
}
