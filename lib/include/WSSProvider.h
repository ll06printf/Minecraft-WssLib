//
// Created by LL06p on 2024/2/19.
//

#ifndef MINECRAFTWSSLIB_WSSPROVIDER_H
#define MINECRAFTWSSLIB_WSSPROVIDER_H

#include <QWebSocket>

#include "Provider.h"

namespace WSSLib {

    class WSSProvider: public Provider {
        Q_OBJECT
    public:
        explicit WSSProvider(QWebSocket *handle, QObject *parent= nullptr);
        ~WSSProvider() override;

    public slots:
        void runCommand(const QString &command) override;
        void subscribe(const QString &eventName) override;
        void unsubscribe(const QString &eventName) override;

    protected slots:
        void receiveMessage(const QString &message);
        void disconnect();

    protected:
        QWebSocket *server;

    };

} // WSSLib

#endif //MINECRAFTWSSLIB_WSSPROVIDER_H
