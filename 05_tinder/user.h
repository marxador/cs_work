#ifndef __USER_H
#define __USER_H
#include <iostream>

class User
{
public:
	// Member Variables
    std::string name, gender, phone, job, school, sexuality, roster, blocked;
    int age, minAge, maxAge, maxDist;
    float lati, longi;
    bool isPremium;

   	User *next;

   	// Constructors/Destructor
   	User( std::string &name,  int &age, const std::string &gender, const std::string &phone,
	const std::string &job, const std::string &school, const float &lati, const float &longi, const bool &isPremium,
	const int &minAge, const int &maxAge, const int &maxDist, const std::string &sexuality, const std::string &roster);
};
#endif