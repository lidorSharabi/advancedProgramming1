//
// Created by lsharabi on 01/01/17.
//

#ifndef MYPROJECTNAME_CLOCK_H
#define MYPROJECTNAME_CLOCK_H


class Clock {
private:
    int currentTime;

public:
    //get current time
    int getCurrentTime();
    //default constractor start time = 0
    Clock() : currentTime(0) {}

    //clock increase by one and return his current time
    int move();
};


#endif //MYPROJECTNAME_CLOCK_H
