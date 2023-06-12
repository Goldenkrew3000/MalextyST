#ifndef PREDICT_HPP_INCLUDED
#define PREDICT_HPP_INCLUDED

void predictSatInfo(std::string TLE_Name, std::string TLE_LineA, std::string TLE_LineB);

std::string retNextPassStart();
std::string retNextPassEnd();
std::string retPassTimeMin();
std::string retTimeUntilPassMin();
std::string retSatMaxElev();

#endif
