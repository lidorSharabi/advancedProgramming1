#include "ClientFlow.h"
#include "Udp.h"
#include "Map.h"
using namespace std;
using namespace boost::archive;


void ClientFlow::runClientFlow(int argc, char *argv[]) {
    //delete before submitting
    cout << "Hello, from client" << endl;
    StandardCab* newCab;
    int cab;
    char buffer[1024];
    Udp udp(false, atoi(argv[2]), argv[1]);
    udp.initialize();
    //serialize driver
    Driver *driver = loadNewDriver();
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    //send driver to server
    udp.sendData(serial_str, serial_str.size());
    //delete before submitting
    cout << "loaded one driver" << endl;

    //waiting for operation value
    udp.reciveData(buffer, sizeof(buffer));
    while (strcmp(buffer, "exit") != 0){
        //add cab to driver
        if (strcmp(buffer, "add new cab") == 0)
        {
            udp.reciveData(buffer, sizeof(buffer));
            boost::iostreams::basic_array_source<char> device1(buffer, 1024);
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s21(device1);
            boost::archive::binary_iarchive ia1(s21);
            ia1 >> newCab;
            driver->addCab(newCab);
        }
        //add trip
        if (strcmp(buffer, "add trip") == 0)
        {
            //add trip to the driver
            Trip* newTrip;
            vector<GridItem*> path;
            udp.reciveData(buffer, sizeof(buffer));
            boost::iostreams::basic_array_source<char> device1(buffer, 1024);
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s21(device1);
            boost::archive::binary_iarchive ia1(s21);
            ia1 >> newTrip;

            //add path to trip
            /*udp.reciveData(buffer, sizeof(buffer));
            boost::iostreams::basic_array_source<char> device2(serial_str.c_str(), serial_str.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s22(device2);
            boost::archive::binary_iarchive ia2(s22);
            ia2 >> path;

            newTrip->setPointsPath(path);*/
            driver->setTrip(newTrip);

            //delete
            cout << "add path to the trip" << endl;

        }
        //moving driver
        if (strcmp(buffer, "move driver") == 0)
        {
            cout << "move driver" << endl;
            //NULL input means this is cient
            driver->driveOneStep(NULL);

            //delete
            (*driver->getCurrentLocation()).printGridItem();
        }
        udp.reciveData(buffer, sizeof(buffer));
        cout << "buffer: " << buffer <<endl;
    }
    deleteAllocatedMemory();
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