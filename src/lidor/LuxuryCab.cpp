#include "LuxuryCab.h"
#include <boost/serialization/export.hpp>

LuxuryCab::LuxuryCab(int cabId, Manufacturer carManufacturer, Color color, int cabType)
        //: StandardCab(cabId, carManufacturer, color, cabType)
        {
        //    tariffCoefficient = speed = 2;
        }

void LuxuryCab::updateMeters() {
   // sumOfMeters += 2;
}

//BOOST_CLASS_EXPORT(LuxuryCab)