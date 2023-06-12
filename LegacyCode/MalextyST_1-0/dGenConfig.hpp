#ifndef DGENCONFIG_HPP_INCLUDED
#define DGENCONFIG_HPP_INCLUDED

/*
// NOTE: This file is the defaults for the configuration generator
*/

// TLE URLs
std::string def_tleUrlNasabare = "http://www.amsat.org/amsat/ftp/keps/current/nasabare.txt";
std::string def_tleUrlAmateur = "http://www.celestrak.com/NORAD/elements/amateur.txt";
std::string def_tleUrlCubesat = "http://www.celestrak.com/NORAD/elements/cubesat.txt";
std::string def_tleUrlGalileo = "http://www.celestrak.com/NORAD/elements/galileo.txt";
std::string def_tleUrlGloops = "http://www.celestrak.com/NORAD/elements/glo-ops.txt";
std::string def_tleUrlGpsops = "http://www.celestrak.com/NORAD/elements/gps-ops.txt";
std::string def_tleUrlIridium = "http://www.celestrak.com/NORAD/elements/iridium.txt";
std::string def_tleUrlIridiumnext = "http://www.celestrak.com/NORAD/elements/iridium-NEXT.txt";
std::string def_tleUrlMolniya = "http://www.celestrak.com/NORAD/elements/molniya.txt";
std::string def_tleUrlNoaa = "http://www.celestrak.com/NORAD/elements/noaa.txt";
std::string def_tleUrlScience = "http://www.celestrak.com/NORAD/elements/science.txt";
std::string def_tleUrlTlenew = "http://www.celestrak.com/NORAD/elements/tle-new.txt";
std::string def_tleUrlVisual = "http://www.celestrak.com/NORAD/elements/visual.txt";
std::string def_tleUrlWeather = "http://www.celestrak.com/NORAD/elements/weather.txt";

// TLE Filenames
std::string def_tleFileNasabare = "nasabare.txt";
std::string def_tleFileAmateur = "amateur.txt";
std::string def_tleFileCubesat = "cubesat.txt";
std::string def_tleFileGalileo = "galileo.txt";
std::string def_tleFileGloops = "glo-ops.txt";
std::string def_tleFileGpsops = "gps-ops.txt";
std::string def_tleFileIridium = "iridium.txt";
std::string def_tleFileIridiumnext = "iridium-NEXT.txt";
std::string def_tleFileMolniya = "molniya.txt";
std::string def_tleFileNoaa = "noaa.txt";
std::string def_tleFileScience = "science.txt";
std::string def_tleFileTlenew = "tle-new.txt";
std::string def_tleFileVisual = "visual.txt";
std::string def_tleFileWeather = "weather.txt";

// TLE Setnames
std::string def_tleSetnameNasabare = "NASABARE";
std::string def_tleSetnameAmateur = "AMATEUR";
std::string def_tleSetnameCubesat = "CUBESAT";
std::string def_tleSetnameGalileo = "GALILEO";
std::string def_tleSetnameGloops = "GLOOPS";
std::string def_tleSetnameGpsops = "GPSOPS";
std::string def_tleSetnameIridium = "IRIDIUM";
std::string def_tleSetnameIridiumnext = "IRIDIUMNEXT";
std::string def_tleSetnameMolniya = "MOLNIYA";
std::string def_tleSetnameNoaa = "NOAA";
std::string def_tleSetnameScience = "SCIENCE";
std::string def_tleSetnameTlenew = "TLENEW";
std::string def_tleSetnameVisual = "VISUAL";
std::string def_tleSetnameWeather = "WEATHER";

// Serial Port Settings
std::string def_serPort = "/dev/ttyS0";
std::string def_serBaud = "9600";

// Observer Settings
std::string def_obsLat = "-27.5598";
std::string def_obsLon = "151.9507";
std::string def_obsAlt = "0.7";

#endif
