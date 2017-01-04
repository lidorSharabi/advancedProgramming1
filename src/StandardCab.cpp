#include "StandardCab.h"

StandardCab::StandardCab(int cabId, Manufacturer carManufacturer, Color color, int cabType)
        : cabId(cabId), carManufacturer(carManufacturer), color(color) {
    int defaultSpeed = 1;
    if (cabType != 1)
    {
        defaultSpeed = 2;
    }
    tariffCoefficient = speed = defaultSpeed ;
}

double StandardCab::getTarrif(int tariff) {
    return tariffCoefficient * tariff;
}

void StandardCab::updateMeters() {
    sumOfMeters++;
}

int StandardCab::getCabId() {
    return cabId;
}

int StandardCab::getSumOfMeters() {
    return sumOfMeters;
}

Manufacturer StandardCab::getCarManufacturer() {
    return carManufacturer;
}

Color StandardCab::getColor() {
    return color;
}

int StandardCab::getSpeed() {
    return speed;
}

StandardCab::~StandardCab() {

}


std::ostream &operator<<(std::ostream &os, const StandardCab &standardCab) {
    os << "id: " << standardCab.cabId << std::endl <<
       "Manufacturer: " << standardCab.carManufacturer << std::endl <<
       "color: " << standardCab.color << std::endl <<
       "speed: " << standardCab.speed << std::endl <<
       "KM: " << standardCab.sumOfMeters <<std::endl <<
       "tariff Coefficient: " << standardCab.tariffCoefficient;
    return os;
}
