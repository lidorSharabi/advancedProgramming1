/*
#include <iostream>
#include "Udp.h"
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "Point.h"
#include "StandardCab.h"
#include "Map.h"
#include "TaxiCenter.h"
#include "Clock.h"
#include "ServerFlow1.h"

using namespace std;
using namespace boost::archive;

#include "ServerFlow1.h"

#include <iostream>
#include "Map.h"
#include "TaxiCenter.h"

Manufacturer ServerFlow::getManufacturerBySymbol(char symbol){
    switch (symbol) {
        case 'H':
            return Manufacturer::HONDA;
        case 'S':
            return Manufacturer::SUBARO;
        case 'T':
            return Manufacturer::TESLA;
        case 'F':
            return Manufacturer::FIAT;
        default:
            return Manufacturer::HONDA;
    }
}

Color ServerFlow::getColorBySymbol(char symbol){
    switch (symbol) {
        case 'R':
            return Color::RED;
        case 'B':
            return Color::BLUE;
        case 'G':
            return Color::GREEN;
        case 'P':
            return Color::PINK;
        case 'W':
            return Color::WHITE;
        default:
            return Color::RED;
    }
}

Trip* ServerFlow::loadNewTrip(){
    int id, startX, startY, endX, endY, numOfPassengers, startingTime;
    double tariff;
    char dummy;
    scanf("%d%c%d%c%d%c%d%c%d%c%d%c%lf%c%d", &id, &dummy, &startX, &dummy, &startY,
          &dummy, &endX, &dummy, &endY, &dummy, &numOfPassengers, &dummy, &tariff,
          &dummy, &startingTime);
    return new Trip(id,startX, startY, endX, endY, numOfPassengers,
                    tariff , startingTime);
}

StandardCab* ServerFlow::loadNewCab(){
    int id, taxiType;
    char dummy, manufacturer, color;
    scanf("%d%c%d%c%c%c%c", &id, &dummy, &taxiType, &dummy,
          &manufacturer, &dummy, &color);

    if (taxiType == 1)
        return new StandardCab(
                id, getManufacturerBySymbol(manufacturer),getColorBySymbol(color));
    return new LuxuryCab (id, getManufacturerBySymbol(manufacturer),
                          getColorBySymbol(color));
}

int ServerFlow::loadDriverId(){
    int id;
    scanf("%d", &id);
    return id;
}

void ServerFlow::runServerFlow() {
    //delete before submitting
    std::cout << "Hello, from server" << std::endl;
    //clock start
    int inputOperation;
    char dummy;
    Clock clock();
    Udp udp(true, 5555);
    udp.initialize();

    initializeServer(&udp);

    //start getting operation inputs
    scanf("%d", &inputOperation);
    while (inputOperation != 7) {
        switch (inputOperation) {
            case 2: //insert new ride
                taxiCenter->addTrip(loadNewTrip());
                break;
            case 3: //insert vehicle
                taxiCenter->addCab(loadNewCab());
                break;
            case 4: //request for driver location
                taxiCenter->findDriverLocation(loadDriverId());
                break;
            case 6: //start driving
                taxiCenter->startAllDriving();
                break;
            case 7: //free all allocated memory
                taxiCenter->freeAllocatedMemory();
                break;
            case 9: //moving the clock one step ahead
                //clock.move();
                break;
        }
        scanf("\n%d", &inputOperation);
    }
}

void ServerFlow::loadAllDrivers(int numOfDrivers, Udp* udp) {

    for (int i = 0; i < numOfDrivers; i++){
        Driver *newDriver;
        char buffer[1024];
        udp->reciveData(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device(buffer, 1024);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> newDriver;
        taxiCenter->addDriver(newDriver);
        //delete before submitting
        cout << *newDriver << endl;
        udp->sendData("one driver load", 15);
    }
}

void initializeServer(Udp* udp){
    int width, height, numOfObstacles, x, y, inputOperation, numOfDrivers;
    char dummy;
    std::list<Point*> obstacles;

    //calculating map inputs
    scanf("%d%c%d", &width, &dummy, &height);
    scanf("%d", &numOfObstacles);
    if (numOfObstacles > 0) {
        for (int i = 0; i < numOfObstacles; i++) {
            scanf("%d%c%d", &x, &dummy, &y);
            obstacles.push_back(new Point(x, y));
        }
    }
    //create map
    Map map(width, height, obstacles);
     = new TaxiCenter(&map);

    //getting drivers

    //inputOperation == 1. start getting drivers
    scanf("%d", &inputOperation);
    if (numOfDrivers == 1){
    //numOfDrivers represent the amount of the drivers, at this ex should be 1
    scanf("%d", &numOfDrivers);
    loadAllDrivers(numOfDrivers, udp);
    }
}

*/
/*

//delete before submitting
std::cout << "Hello, from server" << std::endl;
Clock clock1();
Udp udp(true, 5555);
udp.initialize();

char buffer[1024];
udp.reciveData(buffer, sizeof(buffer));
cout << buffer << endl;
udp.sendData("sup?", 5);


int width, height, numOfObstacles, x, y, inputOperation, numOfDrivers;
char dummy;
std::list<Point*> obstacles;

//calculating map inputs
 */
/*
scanf("%d%c%d", &width, &dummy, &height);
scanf("%d", &numOfObstacles);
if (numOfObstacles > 0) {
for (int i = 0; i < numOfObstacles; i++) {
scanf("%d%c%d", &x, &dummy, &y);
obstacles.push_back(new Point(x, y));
}
}*//*
 */
/*
//create map
Map map(width, height, obstacles);
TaxiCenter* taxiCenter = new TaxiCenter(&map);
//inputOperation == 1. start getting drivers
scanf("%d", &inputOperation);
//numOfDrivers represent the amount of the drivers, at this ex should be 1
scanf("%d", &numOfDrivers);



char buffer2[1024];
udp.reciveData(buffer2, sizeof(buffer2));
udp.sendData("sup?", 5);
//cout << buffer2 << endl;


for (int i = 0; i < numOfDrivers; i++){
Driver *newDriver;
boost::iostreams::basic_array_source<char> device(buffer2, 1024);
boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
boost::archive::binary_iarchive ia(s2);
ia >> newDriver;
cout << *newDriver << endl;
}
//start getting operation inputs
scanf("%d", &inputOperation);

*//*

*/
/*
//usleep(5000);
//Udp udp2(1, 5554);
//udp2.initialize();

char buffer2[1024];
udp.reciveData(buffer2, sizeof(buffer2));
//cout << buffer2 << endl;
udp.sendData("sup?", 5);

StandardCab *gp2;
boost::iostreams::basic_array_source<char> device(buffer2, 1024);
boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
boost::archive::binary_iarchive ia(s2);
ia >> gp2;

cout << (*gp2);
 *//*
*/
/*

// support more than one client?

*/