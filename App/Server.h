//
// Created by LL06p on 2024/2/14.
//

#ifndef MINECRAFTWSSLIB_SERVER_H
#define MINECRAFTWSSLIB_SERVER_H

#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>
#include <QDir>
#include <QUuid>

const QString eventToScribe[] = {
        "PlayerMessage"
};
const QString commandToRun[] = {
        "list"
};
constexpr int version = 17039360;

class Server : public QObject{
    Q_OBJECT
public:
    explicit Server(const QString& serverName="Server", QObject *parent= nullptr);
    ~Server() override;

    bool listen(const QHostAddress &address=QHostAddress::Any, quint16 port=6600);
    void setLogDir(const QDir &dir);

signals:
    void closed();

public slots:
    void takeConnection();
    void clientDisconnect();
    void log(const QString& m);
    void errorLog();

private:
    QDir logDir;
    QMap<QUuid, QString> descriptor;
    QWebSocketServer *serverHandle;
    QList<QWebSocket *> clients;
};


#endif //MINECRAFTWSSLIB_SERVER_H
