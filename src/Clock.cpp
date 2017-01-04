//
// Created by lsharabi on 01/01/17.
//

#include "Clock.h"

//clock increase by one and return his current time
int Clock::move(){
    return ++currentTime;
}

int Clock::getCurrentTime() {
    return currentTime;
}
