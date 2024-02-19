//
// Created by LL06p on 2024/2/16.
//

#ifndef MINECRAFTWSSLIB_PROVIDER_H
#define MINECRAFTWSSLIB_PROVIDER_H

#include <QObject>
#include <QString>
#include <QSet>
#include <QSharedPointer>

#include "Events.h"

namespace WSSLib {
    Q_NAMESPACE
    class Provider: public QObject {
        Q_OBJECT
    public:
        ~Provider() override = default;

        QSet<EventType> getSubscribedEvents() ;
    public slots:
        virtual void runCommand(const QString &command) = 0;

        virtual void subscribe(enum WSSLib::EventType t);
        virtual void subscribe(const QString &eventName) = 0;

        virtual void unsubscribe(enum WSSLib::EventType t);
        virtual void unsubscribe(const QString &eventName) = 0;

    signals:
        void providerTransform(WSSLib::Provider *);
        void eventRaised(QSharedPointer<const WSSLib::Event> event);

    protected:
        explicit Provider(QObject *parent = nullptr);


    protected:
        QSet<EventType> SubscribedEvents;
    };

} // WSSLib

#endif //MINECRAFTWSSLIB_PROVIDER_H
