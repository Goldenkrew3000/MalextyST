#ifndef SFILEHANDLER_HPP_INCLUDED
#define SFILEHANDLER_HPP_INCLUDED

std::string sFileHandler_ReadConfigFile();
bool sFileHandler_makeTempFolder();
bool sFileHandler_removeTempFolder();
bool sFileHandler_checkSatDBExist();
bool sFileHandler_deleteSatDB();
bool sFileHandler_checkConfigExists();
bool sFileHandler_deleteConfig();
bool sFileHandler_writeConfig();

#endif
