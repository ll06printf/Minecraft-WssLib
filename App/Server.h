//
// Created by LL06p on 2024/2/14.
//

#ifndef MINECRAFTWSSLIB_SERVER_H
#define MINECRAFTWSSLIB_SERVER_H

#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>
#include <QFile>
#include <QTextStream>

constexpr auto testMessage = R"({
	"body": {
		"origin": {
			"type": "player"
		},
		"commandLine": "say Hello",
		"version": 1
	},
	"header": {
		"requestId": "00000000-0000-0000-0000-000000000000",
		"messagePurpose": "commandRequest",
		"version": 1,
		"messageType": "commandRequest"
	}
})";

class Server : public QObject{
    Q_OBJECT
public:
    explicit Server(const QString& serverName="Server", QObject *parent= nullptr);
    ~Server() override;

    bool listen(const QHostAddress &address=QHostAddress::Any, quint16 port=6600);
    void setLogFile(QIODevice *path);

signals:
    void closed();

public slots:
    void takeConnection();
    void clientDisconnect();
    void log(const QString& m);
    void errorLog();

private:
    QTextStream logStream;
    QWebSocketServer *serverHandle;
    QList<QWebSocket *> clients;
};


#endif //MINECRAFTWSSLIB_SERVER_H
