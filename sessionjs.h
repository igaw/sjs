#ifndef CONNMANPROXY_H
#define CONNMANPROXY_H

#include <QtGui>

class QString;
class QDBusVariant;

class ManagerProxy;
class SessionProxy;
class NotificationAdaptor;

class SessionJS : public QObject
{
    Q_OBJECT
public:
    SessionJS(QObject * parent=0);
    virtual ~SessionJS();

    void setManager(ManagerProxy *manager);

public slots:
    void do_connect();
    void do_disconnect();

signals:
    void state(QString state);
    void bearer(QString bearer);
    void name(QString name);

private:
    ManagerProxy *m_manager;
    SessionProxy *m_session;
    NotificationAdaptor *m_notification;

private slots:
    void Release();
    void Update(const QVariantMap &settings);
};

#endif
