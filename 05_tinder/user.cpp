#include "user.h"

// Constructors/Destructor
User::User( std::string &name,  int &age, const std::string &gender, const std::string &phone,
	const std::string &job, const std::string &school, const float &lati, const float &longi, const bool &isPremium,
	const int &minAge, const int &maxAge, const int &maxDist, const std::string &sexuality, const std::string &roster)
{
	this->name = name;
	this->age = age;
	this->gender = gender;
	this->phone = phone;
	this->job = job;
	this->school = school;
	this->lati = lati;
	this->longi = longi;
	this->isPremium = isPremium;
	this->minAge = minAge;
	this->maxAge = maxAge;
	this->maxDist = maxDist;
	this->sexuality = sexuality;
	this->roster = roster;
	this->next = NULL;
	this->blocked = "";
}
