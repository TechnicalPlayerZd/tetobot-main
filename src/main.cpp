#include "main.h"
#include "robot.hpp"


void initialize() {
    robotInitialize();
}

void disabled() {
    robot::stop();
}

void competition_initialize() {
}

void autonomous() {
    robot::stop();
}

void opcontrol() {
    robotOpcontrol();
}