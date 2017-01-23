#include "ClientFlow.h"
#include "../connection/Tcp.h"
#include "../Map.h"
#include "../../easylogging++.h"

using namespace std;
using namespace boost::archive;

void ClientFlow::runClientFlow(int argc, char *argv[]) {
    StandardCab* newCab;
    std::list<Trip*> tripsList;
    int cab;
    char buffer[40000];
    Tcp tcp(false, atoi(argv[2]), argv[1]);
    tcp.initialize();

    //check the connection work well
    memset(buffer, 0 , sizeof(buffer));
    tcp.reciveData(buffer, sizeof(buffer), 0);
    LOG(INFO) << buffer;

    //serialize driver
    Driver *driver = loadNewDriver();
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    //send driver to server
    tcp.sendData(serial_str, serial_str.size());
    //waiting for operation value
    memset(buffer, 0 , sizeof(buffer));
    tcp.reciveData(buffer, sizeof(buffer), 0);
    while (strcmp(buffer, "exit") != 0){
        //print the recive operation
        LOG(INFO) << buffer;
        //add cab to driver
        if (strcmp(buffer, "add new cab") == 0)
        {
            LOG(INFO) << "CASE ADD NEW CAB";
            memset(buffer, 0 , sizeof(buffer));
            tcp.reciveData(buffer, sizeof(buffer), 0);
            boost::iostreams::basic_array_source<char> device1(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s21(device1);
            boost::archive::binary_iarchive ia1(s21);
            ia1 >> newCab;
            driver->bindCabToDriver(newCab);
        }
        //add trip
        if (strcmp(buffer, "add trip") == 0)
        {
            //add trip to the driver
            LOG(INFO) << "CASE ADD NEW TRIP";
            Trip* newTrip;
            memset(buffer, 0 , sizeof(buffer));
            tcp.reciveData(buffer, sizeof(buffer), 0);
            boost::iostreams::basic_array_source<char> device1(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s21(device1);
            boost::archive::binary_iarchive ia1(s21);
            ia1 >> newTrip;
            //add newTrip to the list of trip and set this trip fot the driver
            tripsList.push_back(newTrip);
            driver->setTrip(newTrip);
        }
        //moving driver
        if (strcmp(buffer, "move driver") == 0)
        {
            LOG(INFO) << "CASE ADD NEW TRIP";
            //NULL input means this is cient
            driver->driveOneStep(NULL);
            Point* p = (Point*)driver->getCurrentLocation();
            LOG(INFO) << (*p);
        }
        memset(buffer, 0 , sizeof(buffer));
        tcp.reciveData(buffer, sizeof(buffer), 0);
    }
    //delete All allocated Memory
    deleteAllocatedMemory();
    driver->getCab()->~StandardCab();
    freeTrips(tripsList);
    driver->~Driver();
    tcp.~Tcp();
}

void ClientFlow::freeTrips(std::list<Trip*> trips) {
    while (!trips.empty()){
        delete(trips.front());
        trips.pop_front();
    }
}

MartialStatus ClientFlow::getMartialStatusBySymbol(char symbol){
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
void ClientFlow::deleteAllocatedMemory(){

}

Driver* ClientFlow::loadNewDriver() {
    int id, age, experience, vehicle_id;
    char status, dummy;
    scanf("%d%c%d%c%c%c%d%c%d", &id, &dummy, &age, &dummy, &status, &dummy,
          &experience, &dummy, &vehicle_id);
    return new Driver(id, age, getMartialStatusBySymbol(status), experience, vehicle_id);
}