/*
// Next Pass Predict
// This is a simplified version of the SGP4 pass predict
// It just searches from the current system time to find the next time the
// satellite will pass over.
// Accuracy: +- 5 seconds (Good enough considering this is for downlink purposes)
*/

// C++ Imports
#include <cmath>
#include <iostream>
#include <list>
#include <cstdlib>
#include <unistd.h>

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

int main()
{
    std::cout << "Entry" << std::endl;

    // Form TLE Object
    CoordGeodetic geo(-27.5593, 151.9507, 0.00);
    Tle tle("CAS-4B",
    "1 42759U 17034B   22104.74682470  .00004911  00000-0  29869-3 0  9991",
    "2 42759  43.0191 323.7127 0009561 253.6844 192.7158 15.11357813266715");
    SGP4 sgp4(tle);

    // Get current time
    DateTime start_date = DateTime::Now(true);
    std::cout << "Current Time: " << start_date << std::endl;

    // Get next satellite pass AOS
    std::cout << "Finding satellite AOS..." << std::endl;
    findNextPass(geo, sgp4, start_date);
    std::cout << "Found satellite AOS time: " << nextPassStart << std::endl;

    // Get next satellite pass LOS
    std::cout << "Finding satellite LOS..." << std::endl;
    findEndNextPass(geo, sgp4, nextPassStart);
    std::cout << "Found satellite LOS time: " << nextPassEnd << std::endl;

    // Get the satellite AOS pass time
    findPassTime();
    std::cout << "Pass Time (Seconds): " << passTime << std::endl;
    std::cout << "Pass Time (Minutes): " << passTimeMin << std::endl;

    // Find time until next satellite pass AOS
    findTimeUntilPass(start_date);
    std::cout << "Time until pass (Seconds): " << timeUntil << std::endl;
    std::cout << "Time until pass (Minutes): " << timeUntilMin << std::endl;

    // Find the next satellite pass max elevation
    findMaxElev(geo, sgp4);
    std::cout << "Max Elevation (degrees): " << satMaxElev << std::endl;

    std::cout << "Exit" << std::endl;
}
