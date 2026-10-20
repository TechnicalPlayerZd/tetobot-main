#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "main.h"
#include "lemlib/api.hpp"

extern pros::Controller master;
extern lemlib::Chassis chassis;

void robotInitialize();
void robotOpcontrol();

namespace robot {
    void stop();
}

#endif