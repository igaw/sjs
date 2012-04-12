#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWebView>

class QDBusServiceWatcher;
class SessionJS;
class ManagerProxy;

class MainWin : public QWebView
{
    Q_OBJECT

public:
    explicit MainWin(QWidget * parent = 0);
    virtual ~MainWin();

private:
    ManagerProxy *m_manager;
    QDBusServiceWatcher *m_watcher;
    SessionJS *m_sessionJS;

    void connmanServiceConnect();
    void connmanServiceDisconnect();

private slots:
    void addJSObject();
    void serviceOwnerChanged(const QString &serviceName,
                             const QString &oldOwner,
                             const QString &newOwner);
    void checkForConnMan();
};

#endif
