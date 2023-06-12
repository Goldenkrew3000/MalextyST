#include <SGP4/CoordTopocentric.h>
#include <SGP4/CoordGeodetic.h>
#include <SGP4/Observer.h>
#include <SGP4/SGP4.h>
#include <SGP4/Util.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include "serial/serial.h"

/*
// 1) The SGP4 Library contains its own pi double (kPI) with a ridiculous number of decimal
// places so that will be used
// 2) For the observer object, the 0 is the altitude of the base station, but i dont know
// if it is in km or m (i think km)
// 3) The SGP4 Library for C++ (https://github.com/dnwrnr/sgp4) seems to have some issues
// so to compile it (with the library installed to /usr) use this:
// g++ SGP4-poc1.cpp -o SGP4-poc1 -lsgp4s
// (This works on Debian AARCH64)
*/

int msgCount = 0;

float observerLatitude = -27.5597;
float observerLongitude = 151.9503;

unsigned int microsecond = 1000000;

double rTod(double rad)
{
    return rad * 180.0 / kPI;
}

int main()
{
    Observer obs(observerLatitude, observerLongitude, 0); // 0 is altitude but idk units so i think its km
    Tle tle = Tle("COMS 1                  ",
"1 36744U 10032A   21232.32214774 -.00000366  00000-0  00000-0 0  9996",
"2 36744   0.3722  95.7139 0001118  59.2404  58.0274  1.00269779 33428");
    SGP4 sgp4(tle);

    std::cout << "Satellite Name:\t\t" << tle.Name() << std::endl;
    std::cout << tle << std::endl;

    serial::Serial sinter("/dev/ttyUSB0", 9600);
    if (sinter.isOpen())
    {
        std::cout << "Serial interface is open" << std::endl;
    } else
    {
        std::cout << "Serial interface is not open" << std::endl;
        exit(0);
    }

    while (1)
    {
        DateTime dt = DateTime::Now(true);
        std::cout << "Current DateTime (UTC): " << dt << std::endl;

        Eci eci = sgp4.FindPosition(dt);
        CoordTopocentric topo = obs.GetLookAngle(eci);
        CoordGeodetic geo = eci.ToGeodetic();

        std::cout << "Calculations:" << std::endl;
        std::cout << "Azimuth: " <<  Util::RadiansToDegrees(topo.azimuth) << " degrees / " << topo.azimuth << " radians" << std::endl;
        std::cout << "Elevation: " <<  Util::RadiansToDegrees(topo.elevation) << " degrees / " << topo.elevation << " radians" << std::endl;
        std::cout << "Range: " << topo.range << " km" << std::endl;
        std::cout << "Range Rate: " << topo.range_rate << " km/s" << std::endl;
        std::cout << "Satellite Latitude: " <<  Util::RadiansToDegrees(geo.latitude) << " radians / " << geo.latitude << " radians" << std::endl;
        std::cout << "Satellite Longitude: " << Util::RadiansToDegrees(geo.longitude) << " radians / " << geo.longitude << " radians" << std::endl; 
        std::cout << "Satellite Altitude: " << geo.altitude << " km" << std::endl << std::endl;

        msgCount++;
        std::string string1 = std::to_string(Util::RadiansToDegrees(topo.azimuth)) + "\r\n";
        std::string string2 = std::to_string(Util::RadiansToDegrees(topo.elevation)) + "\r\n";
        std::string string3 = std::to_string(msgCount) + "\r\n";

        size_t bytes_wrote0 = sinter.write("STARTMSG\r\n");
        size_t bytes_wrote1 = sinter.write(string1);
        size_t bytes_wrote2 = sinter.write(string2);
        size_t bytes_wrote25 = sinter.write(string3);
        size_t bytes_wrote3 = sinter.write("ENDMSG\r\n");

        usleep(1 * microsecond);
    }

    return 0;
}
