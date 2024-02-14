//
// Created by LL06p on 2024/2/14.
//

#include "Server.h"

Server::Server(const QString& serverName, QObject *parent):
    serverHandle(new QWebSocketServer(serverName, QWebSocketServer::NonSecureMode, this)),
    QObject(parent) {
    qDebug() << "Server is Created";
    connect(serverHandle, &QWebSocketServer::newConnection, this, &Server::takeConnection);
    connect(serverHandle, &QWebSocketServer::serverError, this, &Server::errorLog);
}

bool Server::listen(const QHostAddress &address, quint16 port) {
    qDebug() << "ServerListen:" << address.toString() << ":" << port;
    return serverHandle->listen(address, port);
}

void Server::takeConnection() {
    auto client = serverHandle->nextPendingConnection();
    if (client) {
        qDebug() << "NewConnection" << client->peerAddress().toString();
        connect(client, &QWebSocket::textMessageReceived, this, &Server::log);
        connect(client, &QWebSocket::binaryMessageReceived, this, &Server::blog);
        connect(client, &QWebSocket::disconnected, this, &Server::clientDisconnect);
        client->sendTextMessage(testMessage);
        clients.append(client);
    } else {
        qDebug() << "Error Connection";
    }
}

void Server::clientDisconnect() {
    auto *client = qobject_cast<QWebSocket *>(QObject::sender());
    qDebug() << "Disconnect:" << client->peerAddress().toString();
    clients.removeAll(client);
}

void Server::log(const QString& m) {
    logStream << m << Qt::endl;
    if (logStream.status() == QTextStream::WriteFailed) {
        qDebug() << "LogDrop";
    }
}

void Server::setLogFile(QIODevice *path) {
    logStream.setDevice(path);
    if (logStream.status() != QTextStream::Ok) {
        qDebug() << "ErrorOnLogFile";
    }
}

Server::~Server() {
    serverHandle->close();
    qDeleteAll(clients.begin(), clients.end());
    logStream.flush();
}

void Server::errorLog() {
    qDebug() << serverHandle->errorString();
}
