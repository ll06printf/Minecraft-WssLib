//
// Created by LL06p on 2024/2/18.
//

#ifndef MINECRAFTWSSLIB_CONTROLLER_H
#define MINECRAFTWSSLIB_CONTROLLER_H

#include <QObject>
#include <QString>

#include "Events.h"
#include "Rule.h"

namespace WSSLib {

    class Controller: QObject {
        Q_OBJECT
    public:
        ~Controller() override = default;
        virtual void run() = 0;
        virtual void config(QString item, QVariant value) = 0;
    public slots:
        virtual void stop() = 0;
        virtual void setupRule(WSSLib::Rule *) = 0;
    signals:
        void eventRaised(WSSLib::Event *);
    };

} // WSSLib

#endif //MINECRAFTWSSLIB_CONTROLLER_H
