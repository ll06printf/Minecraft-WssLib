//
// Created by LL06p on 2024/2/18.
//

#include "Controller.h"

namespace WSSLib {
    Controller *Controller::getInstance() {
        return instance;
    }

    Controller *Controller::instance = nullptr;
} // WSSLib