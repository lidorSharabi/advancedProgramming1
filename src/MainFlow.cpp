#include "MainFlow.h"
#include "Map.h"

MartialStatus MainFlow::getMartialStatusBySymbol(char symbol){
    switch (symbol) {
        case 'S':
            return MartialStatus::SINGLE;
        case 'M':
            return MartialStatus::MARRIED;
        case 'D':
            return MartialStatus::DIVORCED;
        case 'W':
            return MartialStatus::WIDDOWED;
        default:
            return MartialStatus::SINGLE;
    }
}

Manufacturer MainFlow::getManufacturerBySymbol(char symbol){
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

Color MainFlow::getColorBySymbol(char symbol){
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

Driver* MainFlow::loadNewDriver() {
    int id, age, experience, vehicle_id;
    char status, dummy;
    scanf("%d%c%d%c%c%c%d%c%d", &id, &dummy, &age, &dummy, &status, &dummy,
          &experience, &dummy, &vehicle_id);
    return new Driver(id, age, getMartialStatusBySymbol(status), experience, vehicle_id);
}

Trip* MainFlow::loadNewTrip(){
    int id, startX, startY, endX, endY, numOfPassengers, startingtime;
    double tariff;
    char dummy;
    scanf("%d%c%d%c%d%c%d%c%d%c%d%c%lf%c%d", &id, &dummy, &startX, &dummy, &startY,
          &dummy, &endX, &dummy, &endY, &dummy, &numOfPassengers, &dummy, &tariff,
          &dummy, &startingtime);
    return new Trip(id,startX, startY, endX, endY, numOfPassengers,
                    tariff , startingtime);
}

StandardCab* MainFlow::loadNewCab(){
    int id, taxiType;
    char dummy, manufacturer, color;
    scanf("%d%c%d%c%c%c%c", &id, &dummy, &taxiType, &dummy,
          &manufacturer, &dummy, &color);

    //if (taxiType == 1)
        return new StandardCab(
                id, getManufacturerBySymbol(manufacturer),getColorBySymbol(color),1);
    //return new LuxuryCab (id, getManufacturerBySymbol(manufacturer),
      //                    getColorBySymbol(color));
}

int MainFlow::loadDriverId(){
    int id;
    scanf("%d", &id);
    return id;
}

void MainFlow::runMainFlow() {
    int width, height, numOfObstacles, x, y, inputOperation;
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
    taxiCenter = new TaxiCenter(&map);
    //start getting operation inputs
    scanf("%d", &inputOperation);
    while (inputOperation != 7) {
        switch (inputOperation) {
            case 1: //insert driver
                taxiCenter->addDriver(loadNewDriver());
                break;
            case 2: //insert new ride
                taxiCenter->addTrip(loadNewTrip());
                break;
            case 3: //insert vehicle
                taxiCenter->addCab(loadNewCab());
                break;
            case 4: //request for driver location
                taxiCenter->requestForDriverLocation(loadDriverId());
                break;
            case 6: //start driving
                //taxiCenter->startAllDriving(NULL);
                break;
            case 7: //free all allocated memory
                taxiCenter->freeAllocatedMemory();
                break;
        }
        scanf("\n%d", &inputOperation);
    }
}


