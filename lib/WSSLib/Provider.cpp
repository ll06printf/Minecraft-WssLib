//
// Created by LL06p on 2024/2/16.
//

#include "Provider.h"
#include <QMetaObject>
#include <QMetaEnum>


namespace WSSLib {
    Q_NAMESPACE

    Provider::Provider(QObject *parent): QObject(parent) {

    }

    QSet<EventType> Provider::getSubscribedEvents() {
        return SubscribedEvents;
    }

    void Provider::subscribe(enum WSSLib::EventType t) {
        auto eventName = QMetaEnum::fromType<enum WSSLib::EventType>();
        subscribe(eventName.valueToKey(static_cast<int>(t)));
    }

    void Provider::unsubscribe(enum WSSLib::EventType t) {
        auto eventName = QMetaEnum::fromType<enum WSSLib::EventType>();
        unsubscribe(eventName.valueToKey(static_cast<int>(t)));
    }

} // WSSLib