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
