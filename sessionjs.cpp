#include "sessionjs.h"
#include "managerproxy.h"
#include "sessionproxy.h"
#include "notification_adaptor.h"

#define NOTIFY_PATH "/sjs"

SessionJS::SessionJS(QObject* parent)
  : QObject(parent), m_manager(NULL)
{
    qDebug("Create Session JavaScript Proxy");
}

SessionJS::~SessionJS()
{
    if (m_notification)
        QDBusConnection::systemBus().unregisterObject(NOTIFY_PATH);

    delete m_notification;
}

void SessionJS::Release()
{
    qDebug("Release called");
}

void SessionJS::Update(const QVariantMap &settings)
{
    qDebug("Update called");

    if (settings.contains("State"))
        emit state(qdbus_cast<QString>(settings["State"]));

    if (settings.contains("Bearer"))
        emit bearer(qdbus_cast<QString>(settings["Bearer"]));

    if (settings.contains("Name"))
        emit name(qdbus_cast<QString>(settings["Name"]));
}

void SessionJS::setManager(ManagerProxy *manager)
{
    if (manager) {
        m_notification = new NotificationAdaptor(this);

        if (!QDBusConnection::systemBus().registerObject(NOTIFY_PATH, this)) {
            qCritical() << "Could not register Notification D-Bus object: " <<
                      QDBusConnection::systemBus().lastError().message();

            delete m_notification;
            m_notification = NULL;

            goto out;
        }

        QVariantMap properties;
        QDBusObjectPath notify_path = QDBusObjectPath(NOTIFY_PATH);
        QDBusObjectPath session_path = manager->CreateSession(properties, notify_path);
	m_session = new SessionProxy(CONNMAN_SERVICE, session_path.path(),
				     QDBusConnection::systemBus(), this);

        qDebug("Session object registered");
    } else {
        if (!m_notification)
            goto out;

        QDBusConnection::systemBus().unregisterObject(NOTIFY_PATH);

	delete m_notification;
	m_notification = NULL;

	delete m_session;
	m_session = NULL;

	qDebug("Session object unregistered");
    }

 out:
    m_manager = manager;
}

void SessionJS::do_connect()
{
    qDebug("connect");

    if (!m_session)
        return;

    m_session->Connect();
}

void SessionJS::do_disconnect()
{
    qDebug("disconnect");

    if (!m_session)
        return;

    m_session->Disconnect();
}
