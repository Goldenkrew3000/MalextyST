// C++ Imports
#include <cmath>
#include <iostream>
#include <list>
#include <cstdlib>
#include <unistd.h>
#include "predict.hpp"

// SGP4 Imports (CMake Local Library)
#include <SGP4/Observer.h>
#include <SGP4/SGP4.h>
#include <SGP4/Util.h>
#include <SGP4/CoordTopocentric.h>
#include <SGP4/CoordGeodetic.h>

// Microsecond and search time step seconds
#define USECOND 1000000
#define time_step 5

// Variables of the final search results
DateTime nextPassStart;
DateTime nextPassEnd;
float passTime;
float timeUntil;
std::string passTimeMin;
std::string timeUntilMin;
float satMaxElev;

void findMaxElev(const CoordGeodetic& user_geo, SGP4& sgp4)
{
    // Create Observer Object
    Observer obs(user_geo);

    // Recreate DateTime objects to be modifiable
    DateTime startTime(nextPassStart);
    DateTime endTime(nextPassEnd);

    // Define variables to keep track of elevation
    float prevElev;
    float elev;

    while (true)
    {
        // Get current satellite position
        Eci eci = sgp4.FindPosition(startTime);
        CoordTopocentric topo = obs.GetLookAngle(eci);

        // Update previous elevation variable
        prevElev = elev;

        // Convert Radians to Degrees (Makes it easier to read)
        elev = Util::RadiansToDegrees(topo.elevation);

        // Check if satellilte is rising or setting
        if (elev > prevElev)
        {
            // Satellite is still rising
            startTime = startTime.AddSeconds(time_step);
        } else if (prevElev > elev)
        {
            // Satellite is setting
            // Set the max elevation to the previous elevation (current is setting, not top of rising)
            satMaxElev = prevElev;
            break;
        }
    }
}

void findTimeUntilPass(const DateTime& currentTime)
{
    // Declare Start and End times
    DateTime startTime(currentTime);
    DateTime endTime(nextPassStart);

    // Calculate the number of seconds between the two dates
    timeUntil = (endTime - startTime).TotalSeconds();

    // Find the same thing above but minutes
    timeUntilMin = (endTime - startTime).ToString();
}

void findPassTime()
{
    // Declare Start and End times
    DateTime startTime(nextPassStart);
    DateTime endTime(nextPassEnd);

    // Calculate the number of seconds between the two dates
    passTime = (endTime - startTime).TotalSeconds();

    // Find the same thing above but minutes
    passTimeMin = (endTime - startTime).ToString();
}

void findEndNextPass(const CoordGeodetic& user_geo, SGP4& sgp4, const DateTime& startTime)
{
    // Create Observer Object
    Observer obs(user_geo);

    // Create new DateTime object (to make it modifiable)
    DateTime current(startTime);

    // Loop to find satellite LOS
    while (true)
    {
        // Find current satellite position
        Eci eci = sgp4.FindPosition(current);
        CoordTopocentric topo = obs.GetLookAngle(eci);

        // Convert Radians to Degrees (Makes it easier to read)
        float elev = Util::RadiansToDegrees(topo.elevation);

        // Check if elevation is in AOS or LOS
        if (elev > 0.0)
        {
            // Satellite is in AOS
            current = current.AddSeconds(time_step);
            //std::cout << current << "     " << elev << std::endl;
        } else
        {
            // Satellite is in LOS
            nextPassEnd = current;
            break;
        }
    }
}

void findNextPass(const CoordGeodetic& user_geo, SGP4& sgp4, const DateTime& startTime)
{
    // Create Observer Object
    Observer obs(user_geo);

    // Create new DateTime object (to make it modifiable)
    DateTime current(startTime);

    // Loop to find satellite AOS
    while (true)
    {
        // Find current satellite position
        Eci eci = sgp4.FindPosition(current);
        CoordTopocentric topo = obs.GetLookAngle(eci);

        // Convert Radians to Degrees (Makes it easier to read)
        float elev = Util::RadiansToDegrees(topo.elevation);

        // Check if elevation is in AOS or LOS
        if (elev < 0.0)
        {
            // Elevation is in LOS
            current = current.AddSeconds(time_step);
            //std::cout << current << "     " << elev << std::endl;
        } else
        {
            // Elevation is in AOS
            nextPassStart = current;
            break;
        }
    }
}

void predictSatInfo(std::string TLE_Name, std::string TLE_LineA, std::string TLE_LineB)
{
    // Form TLE Object
    CoordGeodetic geo(-27.5593, 151.9507, 0.00);
    Tle tle(TLE_Name, TLE_LineA, TLE_LineB);
    SGP4 sgp4(tle);

    // Get current time
    DateTime start_date = DateTime::Now(true);
    
    findNextPass(geo, sgp4, start_date);
    findEndNextPass(geo, sgp4, nextPassStart);
    findPassTime();
    findTimeUntilPass(start_date);
    findMaxElev(geo, sgp4);
}

std::string retNextPassStart()
{
    return nextPassStart.ToString();
}

std::string retNextPassEnd()
{
    return nextPassEnd.ToString();
}

std::string retPassTimeMin()
{
    return passTimeMin;
}

std::string retTimeUntilPassMin()
{
    return timeUntilMin;
}

std::string retSatMaxElev()
{
    std::string tempStr = std::to_string(satMaxElev);
    return tempStr;
}
