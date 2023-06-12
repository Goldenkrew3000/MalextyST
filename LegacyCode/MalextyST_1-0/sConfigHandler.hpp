#ifndef SCONFIGHANDLER_HPP_INCLUDED
#define SCONFIGHANDLER_HPP_INCLUDED

void sConfigHandler_ParseConfig();

// Serial Port Settings Returns
std::string sConfigHandler_ReadSerialPort();
std::string sConfigHandler_ReadBaudrate();

// Observer Settings Returns
std::string sConfigHandler_Observer_Altitude();
std::string sConfigHandler_Observer_Latitude();
std::string sConfigHandler_Observer_Longitude();

// TLE URLs Returns
std::string sConfigHandler_TLEURL_Nasabare();
std::string sConfigHandler_TLEURL_Amateur();
std::string sConfigHandler_TLEURL_Cubesat();
std::string sConfigHandler_TLEURL_Galileo();
std::string sConfigHandler_TLEURL_Gloops();
std::string sConfigHandler_TLEURL_Gpsops();
std::string sConfigHandler_TLEURL_Iridium();
std::string sConfigHandler_TLEURL_Iridiumnext();
std::string sConfigHandler_TLEURL_Molniya();
std::string sConfigHandler_TLEURL_Noaa();
std::string sConfigHandler_TLEURL_Science();
std::string sConfigHandler_TLEURL_Tlenew();
std::string sConfigHandler_TLEURL_Visual();
std::string sConfigHandler_TLEURL_Weather();

// TLE Filenames Returns
std::string sConfigHandler_TLENAME_Nasabare();
std::string sConfigHandler_TLENAME_Amateur();
std::string sConfigHandler_TLENAME_Cubesat();
std::string sConfigHandler_TLENAME_Galileo();
std::string sConfigHandler_TLENAME_Gloops();
std::string sConfigHandler_TLENAME_Gpsops();
std::string sConfigHandler_TLENAME_Iridium();
std::string sConfigHandler_TLENAME_Iridiumnext();
std::string sConfigHandler_TLENAME_Molniya();
std::string sConfigHandler_TLENAME_Noaa();
std::string sConfigHandler_TLENAME_Science();
std::string sConfigHandler_TLENAME_Tlenew();
std::string sConfigHandler_TLENAME_Visual();
std::string sConfigHandler_TLENAME_Weather();

// TLE Setnames Returns
std::string sConfigHandler_SETNAME_Nasabare();
std::string sConfigHandler_SETNAME_Amateur();
std::string sConfigHandler_SETNAME_Cubesat();
std::string sConfigHandler_SETNAME_Galileo();
std::string sConfigHandler_SETNAME_Gloops();
std::string sConfigHandler_SETNAME_Gpsops();
std::string sConfigHandler_SETNAME_Iridium();
std::string sConfigHandler_SETNAME_Iridiumnext();
std::string sConfigHandler_SETNAME_Molniya();
std::string sConfigHandler_SETNAME_Noaa();
std::string sConfigHandler_SETNAME_Science();
std::string sConfigHandler_SETNAME_Tlenew();
std::string sConfigHandler_SETNAME_Visual();
std::string sConfigHandler_SETNAME_Weather();

// TLE Settings Returns
std::string sConfigHandler_TLESETTING_TempFolderName();
std::string sConfigHandler_TLESETTING_DBName();

#endif
