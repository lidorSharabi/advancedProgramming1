#include "Clock.h"

//clock increase by one and return his current time
int Clock::move(){
    return ++currentTime;
}
//return current time
int Clock::getCurrentTime() {
    return currentTime;
}
