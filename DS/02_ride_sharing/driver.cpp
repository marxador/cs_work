#include "driver.h"

// Constructors
Driver::Driver() 
{
	driverFirst = "";
	driverLast = "";
	gender = "";
	age = 0;
	driverPhone = "";
	rating = 0;
	latitude = 0;
	longitude = 0;
	vehicle = "";
	state = "";
	riderFirst = "";
	riderLast = "";
	riderPhone = "";
}
Driver::Driver(std::string aDriverFirst, std::string aDriverLast, std::string aGender, int aAge, 
	std::string aDriverPhone, float aRating, float aLatitude, float aLongitude, 
	std::string aVehicle, std::string aState, std::string aRiderFirst, std::string aRiderLast, std::string aRiderPhone)
{
	driverFirst = aDriverFirst;
	driverLast = aDriverLast;
	gender = aGender;
	age = aAge;
	driverPhone = aDriverPhone;
	rating = aRating;
	latitude = aLatitude;
	longitude = aLongitude;
	vehicle = aVehicle;
	state = aState;
	riderFirst = aRiderFirst;
	riderLast = aRiderLast;
	riderPhone = aRiderPhone;
}

// Getters const
std::string Driver::getDriverFirst() const
{
	return driverFirst;
}
std::string Driver::getDriverLast() const
{
	return driverLast;
}
std::string Driver::getGender() const
{
	return gender;
}
int Driver::getAge() const
{
	return age;
}
std::string Driver::getDriverPhone() const
{
	return driverPhone;
}
float Driver::getRating() const
{
	return rating;
}
float Driver::getLatitude() const
{
	return latitude;
}
float Driver::getLongitude() const
{
	return longitude;
}
std::string Driver::getVehicle() const
{
	return vehicle;
}
std::string Driver::getState() const
{
	return state;
}
std::string Driver::getRiderFirst() const
{
	return riderFirst;
}
std::string Driver::getRiderLast() const
{
	return riderLast;
}
std::string Driver::getRiderPhone() const
{
	return riderPhone;
}

// Setters
void Driver::setState(std::string aState)
{
	state = aState;
}
void Driver::setRiderFirst(std::string aRiderFirst)
{
	riderFirst = aRiderFirst;
}
void Driver::setRiderLast(std::string aRiderLast)
{
	riderLast = aRiderLast;
}
void Driver::setRiderPhone(std::string aRiderPhone)
{
	riderPhone = aRiderPhone;
}