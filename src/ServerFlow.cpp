#include <stdlib.h>
#include "ServerFlow.h"
#include "BfsAlgorithm.h"

using namespace std;

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
    int id, startX, startY, endX, endY, numOfPassengers, startingtime;
    double tariff;
    char dummy;
    scanf("%d%c%d%c%d%c%d%c%d%c%d%c%lf%c%d", &id, &dummy, &startX, &dummy, &startY,
          &dummy, &endX, &dummy, &endY, &dummy, &numOfPassengers, &dummy, &tariff,
          &dummy, &startingtime);
    return new Trip(id,startX, startY, endX, endY, numOfPassengers,
                    tariff , startingtime);
}

StandardCab* ServerFlow::loadNewCab(){
    int id, taxiType;
    char dummy, manufacturer, color;
    scanf("%d%c%d%c%c%c%c", &id, &dummy, &taxiType, &dummy,
          &manufacturer, &dummy, &color);
        return new StandardCab(
                id, getManufacturerBySymbol(manufacturer),getColorBySymbol(color), taxiType);
}

int ServerFlow::loadDriverId(){
    int id;
    scanf("%d", &id);
    return id;
}

void ServerFlow::runServerFlow(int argc, char *argv[]) {
    int inputOperation;
    char dummy;
    BfsAlgorithm bfsAlgorithm;
    Trip *trip;
    //initialize Udp connection
    Udp udp(true, atoi(argv[1]), "127.0.0.1");
    udp.initialize();
    //creating map and taxi center
    initializeServer();


    //start getting operation inputs
    scanf("%d", &inputOperation);
    while (inputOperation != 7) {
        switch (inputOperation) {
            case 1://getting drivers
                loadAllDrivers(udp);
                //bind the driver cabs and send them to the client
                taxiCenter->bindCabsToDrivers(&udp);
                break;
            case 2: //insert new ride
                trip = loadNewTrip();
                trip->setPointsPath(bfsAlgorithm.findDestination(trip->getStart(),
                                         trip->getEnd(), taxiCenter->getMap()));
                taxiCenter->addTrip(trip);
                break;
            case 3: //insert vehicle
                taxiCenter->addCab(loadNewCab());
                break;
            case 4: //request for driver location
                taxiCenter->findDriverLocation(loadDriverId());
                break;
            case 7: //free all allocated memory
                udp.sendData("exit", 4);
                taxiCenter->freeAllocatedMemory();
                break;
            case 9: //moving the clock one step ahead
                taxiCenter->increaseClock();
                //start driving
                taxiCenter->startAllDriving(&udp);
                break;
        }
        scanf("\n%d", &inputOperation);
    }
    //free all allocated memory
    udp.sendData("exit", 4);
    udp.~Udp();
    taxiCenter->freeAllocatedMemory();
}

void ServerFlow::loadAllDrivers(Udp& udp) {
    int numOfDrivers;
    //numOfDrivers represent the amount of the drivers, should be 1!!!
    scanf("%d", &numOfDrivers);
    for (int i = 0; i < numOfDrivers; i++) {
        Driver *newDriver;
        char buffer[1024];
        //de - serialize driver
        udp.reciveData(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device(buffer, 1024);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> newDriver;
        taxiCenter->addDriver(newDriver);
    }
}

void ServerFlow::initializeServer(){
    int width, height, numOfObstacles, x, y;
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
    //todo delete map at the end of the program
    Map* map = new Map(width, height, obstacles);
    taxiCenter = new TaxiCenter(map);
}
