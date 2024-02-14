#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkReply>

#include "Server.h"

QFile LogFile{R"(E:\Source\MinecraftWssLib\log\capture1.log)"};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
//    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString() << QSslSocket::sslLibraryVersionNumber();
    auto s = new Server();
    QObject::connect(s, &Server::closed, &a, &QCoreApplication::quit);
    LogFile.open(QIODeviceBase::Append);
    s->setLogFile(&LogFile);
    s->listen();
    return QCoreApplication::exec();
}
