//
// Created by LL06p on 2024/2/19.
//

#ifndef MINECRAFTWSSLIB_RULE_H
#define MINECRAFTWSSLIB_RULE_H

#include <QObject>

#include "Events.h"

namespace WSSLib {

    class Rule: QObject {
        Q_OBJECT
    public:
        ~Rule() override = default;
    public slots:
        virtual void accept(WSSLib::Event *) = 0;
    };

} // WSSLib

#endif //MINECRAFTWSSLIB_RULE_H
