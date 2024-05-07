#include "rider.h"

// Constructors
Rider::Rider() 
{
	riderFirst = "";
    riderLast = "";
    gender = "";
    age = 0;
    riderPhone = "";
    rating = 0;
    pickupName = "";
    pickupLat = 0;
    pickupLong = 0;
    dropoffName = "";
    dropoffLat = 0;
    dropoffLong = 0;
    vehicle = "";
    state = "";
    driverFirst = "";
    driverLast = "";
    driverPhone = "";
}
Rider::Rider(std::string aRiderFirst, std::string aRiderLast, std::string aGender,
		int aAge, std::string aRiderPhone, float aRating, std::string aPickupName, 
		float aPickupLat, float aPickupLong, std::string aDropoffName, float aDropoffLat, 
		float aDropoffLong, std::string aVehicle, std::string aState, 
		std::string aDriverFirst, std::string aDriverLast, std::string aDriverPhone)
{
	riderFirst = aRiderFirst;
    riderLast = aRiderLast;
    gender = aGender;
    age = aAge;
    riderPhone = aRiderPhone;
    rating = aRating;
    pickupName = aPickupName;
    pickupLat = aPickupLat;
    pickupLong = aPickupLong;
    dropoffName = aDropoffName;
    dropoffLat = aDropoffLat;
    dropoffLong = aDropoffLong;
    vehicle = aVehicle;
    state = aState;
    driverFirst = aDriverFirst;
    driverLast = aDriverLast;
    driverPhone = aDriverPhone;
}

// Getters const
std::string Rider::getRiderFirst() const
{
	return riderFirst;
}
std::string Rider::getRiderLast() const
{
	return riderLast;
}
std::string Rider::getGender() const
{
	return gender;
}
int Rider::getAge() const
{
	return age;
}
std::string Rider::getRiderPhone() const
{
	return riderPhone;
}
float Rider::getRating() const
{
	return rating;
}
std::string Rider::getPickupName() const
{
	return pickupName;
}
float Rider::getPickupLat() const
{
	return pickupLat;
}
float Rider::getPickupLong() const
{
	return pickupLong;
}
std::string Rider::getDropoffName() const
{
	return dropoffName;
}
float Rider::getDropoffLat() const
{
	return dropoffLat;
}
float Rider::getDropoffLong() const
{
	return dropoffLong;
}
std::string Rider::getVehicle() const
{
	return vehicle;
}
std::string Rider::getState() const
{
	return state;
}
std::string Rider::getDriverFirst() const
{
	return driverFirst;
}
std::string Rider::getDriverLast() const
{
	return driverLast;
}
std::string Rider::getDriverPhone() const
{
	return driverPhone;
}

// Setters
void Rider::setState(std::string aState)
{
    state = aState;
}
void Rider::setDriverFirst(std::string aDriverFirst)
{
    driverFirst = aDriverFirst;
}
void Rider::setDriverLast(std::string aDriverLast)
{
    driverLast = aDriverLast;
}
void Rider::setDriverPhone(std::string aDriverPhone)
{
    driverPhone = aDriverPhone;
}