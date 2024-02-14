#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkReply>

#include "Server.h"

QDir logDir{R"(E:\Source\MinecraftWssLib\doc\DataPackageSample)"};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    auto s = new Server();
    QObject::connect(s, &Server::closed, &a, &QCoreApplication::quit);
    s->setLogDir(logDir);
    s->listen();
    return QCoreApplication::exec();
}
