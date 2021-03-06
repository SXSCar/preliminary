//
// Created by Silver Narcissus on 2017/10/27.
//

#include "../header/GPIOlib.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
//该文件用于模拟不稳定的加速电机

namespace stimulate {
    double left;
    double right;
    double left_distance;
    double right_distance;
}

int GPIO::init() {
    stimulate::left = 0;
    stimulate::right = 0;
    stimulate::left_distance = 0;
    stimulate::right_distance = 0;

    return 0;
}

int GPIO::controlLeft(int direction, int speed) {
    srandom(time(nullptr));
    double rand_speed = speed * ((double) random() / RAND_MAX - 0.5) / 5;

    if (direction == FORWARD) {
        stimulate::left = speed + rand_speed;
    } else {
        stimulate::left = -speed + rand_speed;
    }

    return 0;
}

int GPIO::controlRight(int direction, int speed) {
    srandom(time(nullptr) + 100);
    double rand_speed = speed * ((double) random() / RAND_MAX - 0.5) / 5;

    if (direction == FORWARD) {
        stimulate::right = speed + rand_speed;
    } else {
        stimulate::right = -speed + rand_speed;
    }

    return 0;
}

int GPIO::stopLeft() {
    stimulate::left = 0;
    return 0;
}

int GPIO::stopRight() {
    stimulate::right = 0;
    return 0;
}

int GPIO::resetCounter() {
    stimulate::left_distance = 0;
    stimulate::right_distance = 0;
    return 0;
}

void GPIO::getCounter(int *countLeft, int *countRight) {
    *countLeft = (int) stimulate::left_distance;
    *countRight = (int) stimulate::right_distance;
}

void GPIO::delay(int milliseconds) {
    //sleep(1);
    double time = milliseconds / 100;
    stimulate::left_distance += stimulate::left * time;
    stimulate::right_distance += stimulate::right * time;
}



