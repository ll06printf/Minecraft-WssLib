//
// Created by LL06p on 2024/2/16.
//

#ifndef MINECRAFTWSSLIB_PROVIDER_H
#define MINECRAFTWSSLIB_PROVIDER_H

#include <QObject>
#include <QString>
#include <QSet>
#include <QPointer>

#include "Events.h"

namespace WSSLib {
    Q_NAMESPACE
    class Provider: QObject {
        Q_OBJECT
    public:
        ~Provider() override = default;

        QSet<EventType> getSubscribedEvents() ;
    public slots:
        virtual void runCommand(const QString &command) = 0;
        void subscribe(WSSLib::Event *e) { subscribe(e->getType()); }
        virtual void subscribe(enum WSSLib::EventType t) = 0;
        virtual void subscribe(const QString &eventName) = 0;
        virtual void unsubscribe(enum WSSLib::EventType t) = 0;
    signals:
        void providerTransform(Provider *);

    protected:
        QSet<EventType> SubscribedEvents;
    };

} // WSSLib

#endif //MINECRAFTWSSLIB_PROVIDER_H
