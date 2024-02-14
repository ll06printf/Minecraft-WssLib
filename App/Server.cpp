//
// Created by LL06p on 2024/2/14.
//

#include "Server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <format>

QString makeEventMessage(const QString &eventName, QUuid id) {
    constexpr  auto messageTemplate = R"({{
	"body": {{
		"eventName": "{0}"
	}},
	"header": {{
		"requestId": "{1}",
		"messagePurpose": "subscribe",
		"version": {2},
		"messageType": "commandRequest"
	}}
}})";
    return QString::fromStdString(
                std::format(messageTemplate, eventName.toStdString(), id.toString().toStdString(), version)
            );
}

QString makeCommandMessage(const QString &command, QUuid id) {
    constexpr auto messageTemplate = R"({{
	"body": {{
		"origin": {{
			"type": "player"
		}},
		"commandLine": "{0}",
		"version": {2}
	}},
	"header": {{
		"requestId": "{1}",
		"messagePurpose": "commandRequest",
		"version": {2},
		"messageType": "commandRequest"
	}}
}})";

    return QString::fromStdString(
            std::format(messageTemplate, command.toStdString(), id.toString().toStdString(), version)
    );
}

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
        //Initialize
        qDebug() << "NewConnection" << client->peerAddress().toString();
        connect(client, &QWebSocket::textMessageReceived, this, &Server::log);
        connect(client, &QWebSocket::disconnected, this, &Server::clientDisconnect);
        clients.append(client);

        //send the initial message
        for (auto &i : eventToScribe) {
            auto id = QUuid::createUuid();
            client->sendTextMessage(makeEventMessage(i, id));
            descriptor[id] = i;
        }
        for (auto &i : commandToRun) {
            auto id = QUuid::createUuid();
            client->sendTextMessage(makeCommandMessage(i, id));
            descriptor[id] = i;
        }
        qDebug() << "initial message has been sent";
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
    QJsonParseError e;
    QJsonDocument message = QJsonDocument::fromJson(m.toUtf8(), &e);

    // Format Verify
    if (e.error != QJsonParseError::ParseError::NoError) {
        qDebug() << "Response Message is not JSON";
    } else if (!message.isObject()) {
        qDebug() << "Response Format is not matched";
    } else {

        // Extract the message type
        auto content = message.object();
        QString prefix;
        auto messagePurpose = content["header"][(QString)"messagePurpose"];
        if (messagePurpose.isString()) {

            if (auto purpose = messagePurpose.toString(); purpose == "commandResponse") {
                prefix = "Command_";
                auto messageId = content["header"][QString{"requestId"}];
                if (messageId.isString()) {
                    QUuid id(messageId.toString());
                    prefix += descriptor[id];
                } else {
                    qDebug() << "Invalid ID";
                } // Process Command

            } else if (purpose == "event") {
                prefix = "Event_";
                auto eventName = content["header"][QString{"eventName"}];
                if (eventName.isString()) {
                    prefix += eventName.toString();
                } else {
                    qDebug() << "Invalid Event Name";
                } //Process Event
            }

        } else {
            qDebug() << "Invalid messagePurpose";
        } // extract messagePurpose

        // Find suitable file name and record
        QString logName;
        for (int i=1; ;++i) {
            if (auto fileName = prefix+"_"+QString::number(i); !logDir.exists(fileName)) {
                logName = fileName;
                break;
            }
        }
        QFile log(logDir.filePath(logName)+".json");
        log.open(QIODeviceBase::WriteOnly);
        QTextStream stream(&log);
        stream << message.toJson(QJsonDocument::Indented) << Qt::endl;

    } //Format Verified
}

void Server::setLogDir(const QDir &dir) {
    logDir = dir;
}

Server::~Server() {
    serverHandle->close();
    qDeleteAll(clients.begin(), clients.end());
}

void Server::errorLog() {
    qDebug() << serverHandle->errorString();
}
