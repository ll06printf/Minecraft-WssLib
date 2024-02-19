//
// Created by LL06p on 2024/2/18.
//

#ifndef MINECRAFTWSSLIB_CONTROLLER_H
#define MINECRAFTWSSLIB_CONTROLLER_H

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include "Events.h"
#include "Rule.h"

namespace WSSLib {

    class Controller: public QObject {
        Q_OBJECT
    public:
        ~Controller() override = default;
        static Controller* getInstance();

        virtual void run() = 0;
        virtual void config(QString item, QVariant value) = 0;

    public slots:
        virtual void stop() = 0;
        virtual void setupRule() = 0;
        virtual void dispatchEvent(QSharedPointer<const WSSLib::Event> event) = 0;

    signals:
        void eventRaised(QSharedPointer<const WSSLib::Event> event);
        void stoped();

    protected:
        static Controller *instance;
    };

} // WSSLib

#endif //MINECRAFTWSSLIB_CONTROLLER_H
