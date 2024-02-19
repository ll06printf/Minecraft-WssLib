//
// Created by LL06p on 2024/2/19.
//

#ifndef MINECRAFTWSSLIB_RULE_H
#define MINECRAFTWSSLIB_RULE_H

#include <QSharedPointer>

#include "Events.h"

namespace WSSLib {

    class Rule {
    public:
        virtual ~Rule() = default;

        virtual QList<WSSLib::EventType> observedEvent() = 0;

        virtual void accept(QSharedPointer<const WSSLib::Event> event) = 0;
    };


} // WSSLib

#endif //MINECRAFTWSSLIB_RULE_H
