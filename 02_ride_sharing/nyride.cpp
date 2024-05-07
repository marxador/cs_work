#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "driver.h"
#include "rider.h"

// Opens a input file for the past string
std::ifstream iFileOpen(const std::string& fileName)
{
	// creates a std::ifstream object for the playlist and opens the file
    std::ifstream file(fileName);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open " << fileName << std::endl;
        exit(1);
    }
    return file; 	
}

// Opens a input file for the past string
std::ofstream oFileOpen(const std::string& fileName)
{
	// creates a std::ifstream object for the playlist and opens the file
    std::ofstream file(fileName);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open " << fileName << std::endl;
        exit(1);
    }
    return file; 	
}

// Following function is from Submitty
// calculate the distance between two coordinates using Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}

// Finds closest driver to rider
void closestDriver(const Rider& rider, const std::vector<Driver>& qualified, Driver& hired, float& minDistance)
{
    float distance;
    for (long unsigned int j = 0; j < qualified.size(); ++j)
    {
        distance = int(calculateDistance(rider.getPickupLat(), rider.getPickupLong(), qualified[j].getLatitude(), qualified[j].getLongitude()) * 10) / 10.0;
        if (minDistance > distance)
        {
            hired = qualified[j];
            minDistance = distance;
        }
    }
}

// Allows a rider to request a driver
bool request(const std::string& phone, std::vector<Driver>& drivers, std::vector<Rider>& riders)
{
    std::ofstream output0 = oFileOpen("output0.txt"); // Opens output text
    // Checks for invalid phone number
    if (phone[3] != '-' || phone[7] != '-' || phone.length() != 12)
    {
        output0 << "Phone number is invalid.";
        output0.close();
        return false;
    }

    // Looks for riders phone number
    for (long unsigned int i = 0; i < riders.size(); ++i)
    {
        // If found checks if they can request a ride
        if (riders[i].getRiderPhone() == phone)
        {   
            // If they can request, looks for driver
            // Otherwise tells them why they can't request
            if (riders[i].getState() == "Ready_to_request")
            {
                std::vector<Driver> qualified;
                for (long unsigned int j = 0; j < drivers.size(); ++j)
                {
                    // Adds each qualified driver to a vector
                    if (drivers[j].getState() == "Available" && drivers[j].getVehicle() == riders[i].getVehicle())
                    {
                        qualified.push_back(drivers[j]);
                    }
                }

                // Dumb submitty error for a or an
                std::string article = "a";
                if (riders[i].getVehicle() == "Economy")
                {
                    article = "an";
                }

                // If there is a driver available, finds the closest one, prints, and updates info
                // Otherwise prints out a message
                if (qualified.size() != 0)
                {
                    // Finds closest driver
                    Driver hired = qualified[0];
                    float minDistance = int(calculateDistance(riders[i].getPickupLat(), riders[i].getPickupLong(), qualified[0].getLatitude(), qualified[0].getLongitude()) * 10) / 10.0;
                    closestDriver(riders[i], qualified, hired, minDistance);

                    // Printing
                    output0 << "Ride requested for rider " << riders[i].getRiderFirst() << ", looking for " << article << " " << riders[i].getVehicle() << " vehicle.\n";
                    output0 << "Pick Up Location: " << riders[i].getPickupName() << ", Drop Off Location: " << riders[i].getDropoffName() << ".\n";
                    output0 << "We have found the closest driver " << hired.getDriverFirst() << "(" << hired.getRating() << ") for you.\n";
                    output0 << hired.getDriverFirst() << " is now " << minDistance << " miles away from you.";

                    // Updating
                    riders[i].setState("Driver_on_the_way");
                    riders[i].setDriverFirst(hired.getDriverFirst());
                    riders[i].setDriverLast(hired.getDriverLast());
                    riders[i].setDriverPhone(hired.getDriverPhone());
                    
                    for (long unsigned int j = 0; j < drivers.size(); ++j)
                    {
                        // Adds each qualified driver to a vector
                        if (drivers[j].getDriverPhone() == hired.getDriverPhone())
                        {
                            drivers[j].setState("On_the_way_to_pickup");
                            drivers[j].setRiderFirst(riders[i].getRiderFirst());
                            drivers[j].setRiderLast(riders[i].getRiderLast());
                            drivers[j].setRiderPhone(riders[i].getRiderPhone());
                        }
                    }
                    
                    output0.close();
                    return true;
                }
                else
                {
                    output0 << "Ride requested for rider " << riders[i].getRiderFirst() << ", looking for " << article <<" " << riders[i].getVehicle() << " vehicle.\n";
                    output0 << "Pick Up Location: " << riders[i].getPickupName() << ", Drop Off Location: " << riders[i].getDropoffName() << ".\n";
                    output0 << "Sorry we can not find a driver for you at this moment.";
                }
            }
            else if (riders[i].getState() == "Driver_on_the_way")
            {
                output0 << "You have already requested a ride and your driver is on the way to the pickup location.";               
            }
            else if (riders[i].getState() == "During_the_trip")
            {
                output0 << "You can not request a ride at this moment as you are already on a trip.";
            }
            output0.close();
            return false;
        }
    }
    // If nothing is found then it must not exist
    output0 << "Account does not exist.";
    output0.close();
    return false;
}

// Allows drivers and riders to cancel their request if in the right state
bool cancel(const std::string& phone, std::vector<Driver>& drivers, std::vector<Rider>& riders)
{
    std::ofstream output0 = oFileOpen("output0.txt"); // Opens output text
    // Looks to see if the phone belongs to a rider
    for (long unsigned int i = 0; i < riders.size(); ++i)
    {
        if (riders[i].getRiderPhone() == phone)
        {
            // If found checks to see if they can cancel a request
            if (riders[i].getState() != "Driver_on_the_way")
            {
                output0 << "You can only cancel a ride request if your driver is currently on the way to the pickup location.";
                output0.close();
                return false;
            }

            // Otherwise looks for the cooresponding driver
            for (long unsigned int j = 0; j < drivers.size(); ++j)
            {   
                // After its found, updates info and prints a message
                if (riders[i].getRiderPhone() == drivers[j].getRiderPhone())
                {   
                    // Printing
                    output0 << "Ride request for rider " << riders[i].getRiderFirst() << " is now canceled by the rider.";

                    // Updating
                    riders[i].setState("Ready_to_request");
                    riders[i].setDriverFirst("null");
                    riders[i].setDriverLast("null");
                    riders[i].setDriverPhone("null");
                        
                    drivers[j].setState("Available");
                    drivers[j].setRiderFirst("null");
                    drivers[j].setRiderLast("null");
                    drivers[j].setRiderPhone("null");

                    output0.close();
                    return true;
                }
            }
        }
    }

    // Looks to see if the phone belongs to a driver
    for (long unsigned int i = 0; i < drivers.size(); ++i)
    {
        if (drivers[i].getDriverPhone() == phone)
        {
            // If found checks to see if they can cancel a request
            if (drivers[i].getState() != "On_the_way_to_pickup")
            {
                output0 << "You can only cancel a ride request if you are currently on the way to the pickup location.";
                output0.close();
                return false;
            }

            // Otherwise looks for the cooresponding rider
            for (long unsigned int j = 0; j < riders.size(); ++j)
            {   
                // After its found, attempts finds a new driver
                if (drivers[i].getDriverPhone() == riders[j].getDriverPhone())
                {
                    std::vector<Driver> qualified;
                    for (long unsigned int k = 0; k < drivers.size(); ++k)
                    {
                        // Adds each qualified driver to a vector
                        if (drivers[k].getState() == "Available" && drivers[k].getVehicle() == riders[j].getVehicle())
                        {
                            qualified.push_back(drivers[k]);
                        }
                    }
    
                    // Finds closest driver
                    Driver hired = qualified[0];
                    float minDistance = int(calculateDistance(riders[j].getPickupLat(), riders[j].getPickupLong(), qualified[0].getLatitude(), qualified[0].getLongitude()) * 10) / 10.0;
                    closestDriver(riders[j], qualified, hired, minDistance);

                    // Printing
                    output0 << "Your driver " << drivers[i].getDriverFirst() << " has canceled the ride request. We will now find a new driver for you.\n";
                    output0 << "Ride requested for rider " << riders[j].getRiderFirst() << ", looking for a " << riders[j].getVehicle() << " vehicle.\n";
                    output0 << "Pick Up Location: " << riders[j].getPickupName() << ", Drop Off Location: " << riders[j].getDropoffName() << ".\n";
                    output0 << "We have found the closest driver " << hired.getDriverFirst() << "(" << hired.getRating() << ") for you.\n";
                    output0 << hired.getDriverFirst() << " is now " << minDistance << " miles away from you.";

                    // Updating
                    riders[j].setState("Driver_on_the_way");
                    riders[j].setDriverFirst(hired.getDriverFirst());
                    riders[j].setDriverLast(hired.getDriverLast());
                    riders[j].setDriverPhone(hired.getDriverPhone());
                    
                    for (long unsigned int k = 0; k < drivers.size(); ++k)
                    {
                        // Adds each qualified driver to a vector
                        if (drivers[k].getDriverPhone() == hired.getDriverPhone())
                        {
                            drivers[k].setState("On_the_way_to_pickup");
                            drivers[k].setRiderFirst(riders[j].getRiderFirst());
                            drivers[k].setRiderLast(riders[j].getRiderLast());
                            drivers[k].setRiderPhone(riders[j].getRiderPhone());
                        }
                    }

                    drivers[i].setState("Available");
                    drivers[i].setRiderFirst("null");
                    drivers[i].setRiderLast("null");
                    drivers[i].setRiderPhone("null");
                    
                    output0.close();
                    return true;
                }
            }
        }
    }

    // If nothing is found then it must not exist
    output0 << "Account does not exist.";
    output0.close();
    return false;
}

int main(int argc, char const *argv[])
{   
    // Checks if the command is recongized
    std::string command = argv[argc - 1];
    if (command != "request" && command != "cancel")
    {
        std::cerr << "Command not recongized" << command << std::endl;
        exit(1);
    }

    // Opens driver file
    std::string fileName = argv[1];
    std::ifstream driverFile = iFileOpen(fileName);
    // Creates variables to collect info from the driver file
    std::vector<Driver> drivers;
    std::string driverFirst, driverLast, gender, driverPhone, vehicle, state, riderFirst, riderLast, riderPhone;
    int age;
    float rating, latitude, longitude;
    // Collects info from file and adds it to the driver vector
    while ( driverFile
        >> driverFirst
        >> driverLast
        >> gender
        >> age
        >> driverPhone
        >> rating
        >> latitude
        >> longitude
        >> vehicle
        >> state
        >> riderFirst
        >> riderLast
        >> riderPhone )
    {
        Driver driver(driverFirst, driverLast, gender, age, driverPhone, rating, 
            latitude, longitude, vehicle, state, riderFirst, riderLast, riderPhone);
        drivers.push_back(driver);
    }
    driverFile.close();

    // Opens rider file
    fileName = argv[2];
    std::ifstream riderFile = iFileOpen(fileName);
    // Creates variables to collect info from the rider file
    std::vector<Rider> riders;
    std::string pickupName, dropoffName;
    float pickupLat, pickupLong, dropoffLat, dropoffLong;
    // Collects info from file and adds it to the rider vector
    while ( riderFile
        >> riderFirst
        >> riderLast
        >> gender
        >> age
        >> riderPhone
        >> rating
        >> pickupName
        >> pickupLat
        >> pickupLong
        >> dropoffName
        >> dropoffLat
        >> dropoffLong
        >> vehicle
        >> state
        >> driverFirst
        >> driverLast
        >> driverPhone )
    {
        Rider rider(riderFirst, riderLast, gender, age, riderPhone, rating, pickupName, pickupLat, pickupLong, 
            dropoffName, dropoffLat, dropoffLong, vehicle, state, driverFirst, driverLast, driverPhone);
        riders.push_back(rider);
    }
    riderFile.close();
    // Runs specified command and checks if other info needs to be outputted
    bool isUpdated = false;
    std::string phone = argv[argc - 2];
    if (command == "request")
    {
        isUpdated = request(phone, drivers, riders);
    }
    else if (command == "cancel")
    {
        isUpdated = cancel(phone, drivers, riders);
    }
    // Does more outputs if needed
    if (isUpdated)
    {
        // Write updated drivers into output1.txt
        std::ofstream output1 = oFileOpen("output1.txt");
        for (long unsigned int i = 0; i < drivers.size(); ++i)
        {
            output1 << drivers[i].getDriverFirst() << " ";
            output1 << drivers[i].getDriverLast() << " ";
            output1 << drivers[i].getGender() << " ";
            output1 << drivers[i].getAge() << " ";
            output1 << drivers[i].getDriverPhone() << " ";
            output1 << drivers[i].getRating() << " ";
            output1 << drivers[i].getLatitude() << " ";
            output1 << drivers[i].getLongitude() << " ";
            output1 << drivers[i].getVehicle() << " ";
            output1 << drivers[i].getState() << " ";
            output1 << drivers[i].getRiderFirst() << " ";
            output1 << drivers[i].getRiderLast() << " ";
            output1 << drivers[i].getRiderPhone() << "\n";
        }
        output1.close();
        // Write updated riders into output2.txt
        std::ofstream output2 = oFileOpen("output2.txt");
        for (long unsigned int i = 0; i < riders.size(); ++i)
        {
            output2 << riders[i].getRiderFirst() << " ";
            output2 << riders[i].getRiderLast() << " ";
            output2 << riders[i].getGender() << " ";
            output2 << riders[i].getAge() << " ";
            output2 << riders[i].getRiderPhone() << " ";
            output2 << riders[i].getRating() << " ";
            output2 << riders[i].getPickupName() << " ";
            output2 << riders[i].getPickupLat() << " ";
            output2 << riders[i].getPickupLong() << " ";
            output2 << riders[i].getDropoffName() << " ";
            output2 << riders[i].getDropoffLat() << " ";
            output2 << riders[i].getDropoffLong() << " ";
            output2 << riders[i].getVehicle() << " ";
            output2 << riders[i].getState() << " ";
            output2 << riders[i].getDriverFirst() << " ";
            output2 << riders[i].getDriverLast() << " ";
            output2 << riders[i].getDriverPhone() << "\n";
        }
        output2.close();
    }
	return 0;
}