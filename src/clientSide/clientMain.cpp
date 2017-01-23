#include <iostream>
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
#include "../Point.h"
#include "../Driver.h"
#include "ClientFlow.h"
#include "../../easylogging++.h"
_INITIALIZE_EASYLOGGINGPP

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
}

