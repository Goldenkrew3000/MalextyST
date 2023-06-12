// C++ Imports
#include <iostream>
#include <string>

// Custom Library Imports
#include "colorManager.hpp"
#include "commonFunctions.hpp"
#include "json.hpp"

// Program Parts Imports
#include "sConfigHandler.hpp"
#include "sFileHandler.hpp"

// Other initialization stuff
using json = nlohmann::json;

// Variables
// Serial Port Variables
std::string jSerialPort = "";
std::string jBaudrate = "";

// Observer Variables
std::string jObsAltitude = "";
std::string jObsLatitude = "";
std::string jObsLongitude = "";

// TLE URLs Variables
std::string jTleUrlNasabare = "";
std::string jTleUrlAmateur = "";
std::string jTleUrlCubesat = "";
std::string jTleUrlGalileo = "";
std::string jTleUrlGloops = "";
std::string jTleUrlGpsops = "";
std::string jTleUrlIridium = "";
std::string jTleUrlIridiumnext = "";
std::string jTleUrlMolniya = "";
std::string jTleUrlNoaa = "";
std::string jTleUrlScience = "";
std::string jTleUrlTlenew = "";
std::string jTleUrlVisual = "";
std::string jTleUrlWeather = "";

// TLE Filenames Variables
std::string jTleFilenameNasabare = "";
std::string jTleFilenameAmateur = "";
std::string jTleFilenameCubesat = "";
std::string jTleFilenameGalileo = "";
std::string jTleFilenameGloops = "";
std::string jTleFilenameGpsops = "";
std::string jTleFilenameIridium = "";
std::string jTleFilenameIridiumnext = "";
std::string jTleFilenameMolniya = "";
std::string jTleFilenameNoaa = "";
std::string jTleFilenameScience = "";
std::string jTleFilenameTlenew = "";
std::string jTleFilenameVisual = "";
std::string jTleFilenameWeather = "";

// TLE Setnames Variables
std::string jTleSetnameNasabare = "";
std::string jTleSetnameAmateur = "";
std::string jTleSetnameCubesat = "";
std::string jTleSetnameGalileo = "";
std::string jTleSetnameGloops = "";
std::string jTleSetnameGpsops = "";
std::string jTleSetnameIridium = "";
std::string jTleSetnameIridiumnext = "";
std::string jTleSetnameMolniya = "";
std::string jTleSetnameNoaa = "";
std::string jTleSetnameScience = "";
std::string jTleSetnameTlenew = "";
std::string jTleSetnameVisual = "";
std::string jTleSetnameWeather = "";

// TLE Settings Variables
std::string jTleSettingsTempFolder = "";
std::string jTleSettingsDBName = "";

// Config File JSON Parser
void sConfigHandler_ParseConfig()
{
    // Receive Raw Config File JSON
    std::string sConfigJson = sFileHandler_ReadConfigFile();

    // Parse Config JSON
    json oConfigJson = json::parse(sConfigJson);

    // Extract Serial Port Settings from JSON
    jSerialPort = oConfigJson["SERIAL"]["PORT"];
    jBaudrate = oConfigJson["SERIAL"]["BAUDRATE"];

    // Extract Observer Settings from JSON
    jObsAltitude = oConfigJson["OBSERVER"]["ALTITUDE"];
    jObsLatitude = oConfigJson["OBSERVER"]["LATITUDE"];
    jObsLongitude = oConfigJson["OBSERVER"]["LONGITUDE"];

    // Extract TLE URLs from JSON
    jTleUrlNasabare = oConfigJson["TLE"]["URLS"]["NASABARE"];
    jTleUrlAmateur = oConfigJson["TLE"]["URLS"]["AMATEUR"];
    jTleUrlCubesat = oConfigJson["TLE"]["URLS"]["CUBESAT"];
    jTleUrlGalileo = oConfigJson["TLE"]["URLS"]["GALILEO"];
    jTleUrlGloops = oConfigJson["TLE"]["URLS"]["GLOOPS"];
    jTleUrlGpsops = oConfigJson["TLE"]["URLS"]["GPSOPS"];
    jTleUrlIridium = oConfigJson["TLE"]["URLS"]["IRIDIUM"];
    jTleUrlIridiumnext = oConfigJson["TLE"]["URLS"]["IRIDIUMNEXT"];
    jTleUrlMolniya = oConfigJson["TLE"]["URLS"]["MOLNIYA"];
    jTleUrlNoaa = oConfigJson["TLE"]["URLS"]["NOAA"];
    jTleUrlScience = oConfigJson["TLE"]["URLS"]["SCIENCE"];
    jTleUrlTlenew = oConfigJson["TLE"]["URLS"]["TLENEW"];
    jTleUrlVisual = oConfigJson["TLE"]["URLS"]["VISUAL"];
    jTleUrlWeather = oConfigJson["TLE"]["URLS"]["WEATHER"];

    // Extract TLE Filenames from JSON
    jTleFilenameNasabare = oConfigJson["TLE"]["FILENAMES"]["NASABARE"];
    jTleFilenameAmateur = oConfigJson["TLE"]["FILENAMES"]["AMATEUR"];
    jTleFilenameCubesat = oConfigJson["TLE"]["FILENAMES"]["CUBESAT"];
    jTleFilenameGalileo = oConfigJson["TLE"]["FILENAMES"]["GALILEO"];
    jTleFilenameGloops = oConfigJson["TLE"]["FILENAMES"]["GLOOPS"];
    jTleFilenameGpsops = oConfigJson["TLE"]["FILENAMES"]["GPSOPS"];
    jTleFilenameIridium = oConfigJson["TLE"]["FILENAMES"]["IRIDIUM"];
    jTleFilenameIridiumnext = oConfigJson["TLE"]["FILENAMES"]["IRIDIUMNEXT"];
    jTleFilenameMolniya = oConfigJson["TLE"]["FILENAMES"]["MOLNIYA"];
    jTleFilenameNoaa = oConfigJson["TLE"]["FILENAMES"]["NOAA"];
    jTleFilenameScience = oConfigJson["TLE"]["FILENAMES"]["SCIENCE"];
    jTleFilenameTlenew = oConfigJson["TLE"]["FILENAMES"]["TLENEW"];
    jTleFilenameVisual = oConfigJson["TLE"]["FILENAMES"]["VISUAL"];
    jTleFilenameWeather = oConfigJson["TLE"]["FILENAMES"]["WEATHER"];

    // Extract TLE Setnames from JSON
    jTleSetnameNasabare = oConfigJson["TLE"]["SETNAMES"]["NASABARE"];
    jTleSetnameAmateur = oConfigJson["TLE"]["SETNAMES"]["AMATEUR"];
    jTleSetnameCubesat = oConfigJson["TLE"]["SETNAMES"]["CUBESAT"];
    jTleSetnameGalileo = oConfigJson["TLE"]["SETNAMES"]["GALILEO"];
    jTleSetnameGloops = oConfigJson["TLE"]["SETNAMES"]["GLOOPS"];
    jTleSetnameGpsops = oConfigJson["TLE"]["SETNAMES"]["GPSOPS"];
    jTleSetnameIridium = oConfigJson["TLE"]["SETNAMES"]["IRIDIUM"];
    jTleSetnameIridiumnext = oConfigJson["TLE"]["SETNAMES"]["IRIDIUMNEXT"];
    jTleSetnameMolniya = oConfigJson["TLE"]["SETNAMES"]["MOLNIYA"];
    jTleSetnameNoaa = oConfigJson["TLE"]["SETNAMES"]["NOAA"];
    jTleSetnameScience = oConfigJson["TLE"]["SETNAMES"]["SCIENCE"];
    jTleSetnameTlenew = oConfigJson["TLE"]["SETNAMES"]["TLENEW"];
    jTleSetnameVisual = oConfigJson["TLE"]["SETNAMES"]["VISUAL"];
    jTleSetnameWeather = oConfigJson["TLE"]["SETNAMES"]["WEATHER"];
    
    // Extract TLE Settings from JSON
    jTleSettingsTempFolder = oConfigJson["TLE"]["SETTINGS"]["TEMPFOLDER"];
    jTleSettingsDBName = oConfigJson["TLE"]["SETTINGS"]["DBNAME"];
}

/* --------------------
// Serial Port Settings
   -------------------- */
// Serial Port Name
std::string sConfigHandler_ReadSerialPort()
{
    return jSerialPort;
}

// Serial Port Baudrate
std::string sConfigHandler_ReadBaudrate()
{
    return jBaudrate;
}

/* -----------------
// Observer Settings
   ----------------- */
// Observer Altitude
std::string sConfigHandler_Observer_Altitude()
{
    return jObsAltitude;
}

// Observer Latitude
std::string sConfigHandler_Observer_Latitude()
{
    return jObsLatitude;
}

// Observer Longitude
std::string sConfigHandler_Observer_Longitude()
{
    return jObsLongitude;
}

/* ----------------
// TLE URLs Returns
   ---------------- */
// Nasabare URL
std::string sConfigHandler_TLEURL_Nasabare()
{
    return jTleUrlNasabare;
}

// Amateur URL
std::string sConfigHandler_TLEURL_Amateur()
{
    return jTleUrlAmateur;
}

// Cubesat URL
std::string sConfigHandler_TLEURL_Cubesat()
{
    return jTleUrlCubesat;
}

// Galileo URL
std::string sConfigHandler_TLEURL_Galileo()
{
    return jTleUrlGalileo;
}

// Gloops URL
std::string sConfigHandler_TLEURL_Gloops()
{
    return jTleUrlGloops;
}

// Gpsops URL
std::string sConfigHandler_TLEURL_Gpsops()
{
    return jTleUrlGpsops;
}

// Iridium URL
std::string sConfigHandler_TLEURL_Iridium()
{
    return jTleUrlIridium;
}

// Iridium-NEXT URL
std::string sConfigHandler_TLEURL_Iridiumnext()
{
    return jTleUrlIridiumnext;
}

// Molniya URL
std::string sConfigHandler_TLEURL_Molniya()
{
    return jTleUrlMolniya;
}

// NOAA URL
std::string sConfigHandler_TLEURL_Noaa()
{
    return jTleUrlNoaa;
}

// Science URL
std::string sConfigHandler_TLEURL_Science()
{
    return jTleUrlScience;
}

// TLENEW URL
std::string sConfigHandler_TLEURL_Tlenew()
{
    return jTleUrlTlenew;
}

// Visual URL
std::string sConfigHandler_TLEURL_Visual()
{
    return jTleUrlVisual;
}

// Weather URL
std::string sConfigHandler_TLEURL_Weather()
{
    return jTleUrlWeather;
}

/* ---------------------
// TLE Filenames Returns
   --------------------- */
// Nasabare Filename
std::string sConfigHandler_TLENAME_Nasabare()
{
    return jTleFilenameNasabare;
}

// Amateur Filename
std::string sConfigHandler_TLENAME_Amateur()
{
    return jTleFilenameAmateur;
}

// Cubesat Filename
std::string sConfigHandler_TLENAME_Cubesat()
{
    return jTleFilenameCubesat;
}

// Galileo Filename
std::string sConfigHandler_TLENAME_Galileo()
{
    return jTleFilenameGalileo;
}

// Gloops Filename
std::string sConfigHandler_TLENAME_Gloops()
{
    return jTleFilenameGloops;
}

// Gpsops Filename
std::string sConfigHandler_TLENAME_Gpsops()
{
    return jTleFilenameGpsops;
}

// Iridium Filename
std::string sConfigHandler_TLENAME_Iridium()
{
    return jTleFilenameIridium;
}

// Iridium-NEXT Filename
std::string sConfigHandler_TLENAME_Iridiumnext()
{
    return jTleFilenameIridiumnext;
}

// Molniya Filename
std::string sConfigHandler_TLENAME_Molniya()
{
    return jTleFilenameMolniya;
}

// NOAA Filename
std::string sConfigHandler_TLENAME_Noaa()
{
    return jTleFilenameNoaa;
}

// Science Filename
std::string sConfigHandler_TLENAME_Science()
{
    return jTleFilenameScience;
}

// Tlenew Filename
std::string sConfigHandler_TLENAME_Tlenew()
{
    return jTleFilenameTlenew;
}

// Visual Filename
std::string sConfigHandler_TLENAME_Visual()
{
    return jTleFilenameVisual;
}

// Weather Filename
std::string sConfigHandler_TLENAME_Weather()
{
    return jTleFilenameWeather;
}


/* --------------------
// TLE Setnames Returns
   -------------------- */
// Nasabare Setname
std::string sConfigHandler_SETNAME_Nasabare()
{
    return jTleSetnameNasabare;
}

// Amateur Setname
std::string sConfigHandler_SETNAME_Amateur()
{
    return jTleSetnameAmateur;
}

// Cubesat Setname
std::string sConfigHandler_SETNAME_Cubesat()
{
    return jTleSetnameCubesat;
}

// Galileo Setname
std::string sConfigHandler_SETNAME_Galileo()
{
    return jTleSetnameGalileo;
}

// Gloops Setname
std::string sConfigHandler_SETNAME_Gloops()
{
    return jTleSetnameGloops;
}

// Gpsops Setname
std::string sConfigHandler_SETNAME_Gpsops()
{
    return jTleSetnameGpsops;
}

// Iridium Setname
std::string sConfigHandler_SETNAME_Iridium()
{
    return jTleSetnameIridium;
}

// Iridium-NEXT Setname
std::string sConfigHandler_SETNAME_Iridiumnext()
{
    return jTleSetnameIridiumnext;
}

// Molniya Setname
std::string sConfigHandler_SETNAME_Molniya()
{
    return jTleSetnameMolniya;
}

// NOAA Setname
std::string sConfigHandler_SETNAME_Noaa()
{
    return jTleSetnameNoaa;
}

// Science Setname
std::string sConfigHandler_SETNAME_Science()
{
    return jTleSetnameScience;
}

// Tlenew Setname
std::string sConfigHandler_SETNAME_Tlenew()
{
    return jTleSetnameTlenew;
}

// Visual Setname
std::string sConfigHandler_SETNAME_Visual()
{
    return jTleSetnameVisual;
}

// Weather Setname
std::string sConfigHandler_SETNAME_Weather()
{
    return jTleSetnameWeather;
}

/* --------------------
// TLE Settings Returns
   -------------------- */
// Temp Folder Name Setting
std::string sConfigHandler_TLESETTING_TempFolderName()
{
    return jTleSettingsTempFolder;
}

// Satellite Database Name Setting
std::string sConfigHandler_TLESETTING_DBName()
{
    return jTleSettingsDBName;
}
