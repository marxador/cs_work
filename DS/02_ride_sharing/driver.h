#ifndef __DRIVER_H
#define __DRIVER_H
#include <iostream>

class Driver{
public:
	// Constructors
	Driver();
	Driver(std::string aDriverFirst, std::string aDriverLast, std::string aGender, int aAge, 
		std::string aDriverPhone, float aRating, float aLatitude, float aLongitude, 
		std::string aVehicle, std::string aState, std::string aRiderFirst, std::string aRiderLast, std::string aRiderPhone);

	// Getters const
	std::string getDriverFirst() const;
	std::string getDriverLast() const;
	std::string getGender() const;
	int getAge() const;
	std::string getDriverPhone() const;
	float getRating() const;
	float getLatitude() const;
	float getLongitude() const;
	std::string getVehicle() const;
	std::string getState() const;
	std::string getRiderFirst() const;
	std::string getRiderLast() const;
	std::string getRiderPhone() const;

	// Setters
	void setState(std::string aState);
	void setRiderFirst(std::string aRiderFirst);
	void setRiderLast(std::string aRiderLast);
	void setRiderPhone(std::string aRiderPhone);

private:
	// Member varibales
	std::string driverFirst;
	std::string driverLast;
	std::string gender;
	int age;
	std::string driverPhone;
	float rating;
	float latitude;
	float longitude;
	std::string vehicle;
	std::string state;
	std::string riderFirst;
	std::string riderLast;
	std::string riderPhone;
};

#endif