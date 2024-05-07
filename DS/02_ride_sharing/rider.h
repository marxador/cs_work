#ifndef __RIDER_H
#define __RIDER_H
#include <iostream>

class Rider{
public:
	// Constructors
	Rider();
	Rider(std::string aRiderFirst, std::string aRiderLast, std::string aGender, int aAge, std::string aRiderPhone, float aRating, 
        std::string aPickupName, float aPickupLat, float aPickupLong, std::string aDropoffName, float aDropoffLat, float aDropoffLong, 
        std::string aVehicle, std::string aState, std::string aDriverFirst, std::string aDriverLast, std::string aDriverPhone);

	// Getters const
	std::string getRiderFirst() const;
    std::string getRiderLast() const;
    std::string getGender() const;
    int getAge() const;
    std::string getRiderPhone() const;
    float getRating() const;
    std::string getPickupName() const;
    float getPickupLat() const;
    float getPickupLong() const;
    std::string getDropoffName() const;
    float getDropoffLat() const;
    float getDropoffLong() const;
    std::string getVehicle() const;
    std::string getState() const;
    std::string getDriverFirst() const;
    std::string getDriverLast() const;
    std::string getDriverPhone() const;

	// Setters
    void setState(std::string aState);
    void setDriverFirst(std::string aDriverFirst);
    void setDriverLast(std::string aDriverLast);
    void setDriverPhone(std::string aDriverPhone);

private:
	// Member varibales
	std::string riderFirst;
    std::string riderLast;
    std::string gender;
    int age;
    std::string riderPhone;
    float rating;
    std::string pickupName;
    float pickupLat;
    float pickupLong;
    std::string dropoffName;
    float dropoffLat;
    float dropoffLong;
    std::string vehicle;
    std::string state;
    std::string driverFirst;
    std::string driverLast;
    std::string driverPhone;
};

#endif