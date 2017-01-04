
#include <unistd.h>
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
#include "Driver.h"
#include "ClientFlow.h"

using namespace std;
using namespace boost::archive;

MartialStatus getMartialStatusBySymbol(char symbol){
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
Driver* loadNewDriver() {
    int id, age, experience, vehicle_id;
    char status, dummy;
    scanf("%d%c%d%c%c%c%d%c%d", &id, &dummy, &age, &dummy, &status, &dummy,
          &experience, &dummy, &vehicle_id);
    return new Driver(id, age, getMartialStatusBySymbol(status), experience, vehicle_id);
}


int main(int argc, char *argv[]) {

    ClientFlow clientFlow;
    clientFlow.runClientFlow(argc, argv);
    return 0;
    /*
    //delete before submitting
    std::cout << "Hello, from client" << std::endl;

    cout << argv[1] << endl;
    Udp udp(false, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    udp.sendData("hello", 6);
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;

    Driver *driver = loadNewDriver();
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    //Udp udp2(false, 5554);
    //udp2.initialize();

    //waiting for server to say that one driver loaded
    udp.sendData(serial_str, serial_str.size());
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    //wating for the server say "sup?"
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;

    return 0;*/
}

