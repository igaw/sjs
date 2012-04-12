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
