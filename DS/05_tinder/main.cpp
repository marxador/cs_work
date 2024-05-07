#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "user.h"

// calculate the distance between two coordinates using Haversine formula
float calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    const float radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    float dLat = lat2 - lat1;
    float dLon = lon2 - lon1;
    float a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    float c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    float distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    float distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}

// Formatting for add user info to the output string
void addInfo(std::string &output, User* &temp)
{
	std::stringstream ss;

    if (!output.empty())
    {
        ss << "\n";
    }

    ss << temp->name << " " << temp->age << "\n";

    if (temp->job != "Undisclosed")
    {
        std::replace(temp->job.begin(), temp->job.end(), '_', ' ');
        ss << temp->job << "\n";
    }

    if (temp->school != "Undisclosed")
    {
        std::replace(temp->school.begin(), temp->school.end(), '_', ' ');
        ss << temp->school << "\n";
    }

    output += ss.str();

}

// Finds all users that match the passed phone number prefrences
std::string profile(const std::string &telephone, User* &usersHead)
{
	std::string output = "";

	// Finds prefrences of passed user
	User* temp = usersHead;
	int minAge, maxAge, maxDist;
	std::string sexuality;
	float lati, longi;
	while(temp != NULL)
	{	
		if (temp->phone == telephone)
		{
			minAge = temp->minAge;
			maxAge = temp->maxAge;
			maxDist = temp->maxDist;
			sexuality = temp->sexuality;
			lati = temp->lati;
			longi = temp->longi;
			break;
		}
		temp = temp->next;
	}


	temp = usersHead;
	bool isNotFound = true;
	while (temp != NULL)
	{
		// Finds important info for checking matches
		int dist = calculateDistance(lati, longi, temp->lati, temp->longi);
		bool isGender = (sexuality == "Both");
		if (!isGender && sexuality == temp->gender){
			isGender = true;
		}

		// Prints info if user is a potental match
		if (minAge <= temp->age && temp->age <= maxAge && dist < maxDist && isGender && telephone != temp->phone && telephone != temp->blocked)
		{
			addInfo(output, temp);
			isNotFound = false;
		}
		temp = temp->next;
	}

	if (isNotFound){
		return "There are no users matching with your preference at this moment.\n";
	}
	return output;
}

// A custom comparison function for sorting matched users
bool compareMatchedUsers(const User* user1, const User* user2) {
    return user1->phone < user2->phone;
}

// Gets a list of users that have match with said user
std::string match(const std::string &telephone, User* &usersHead)
{
	std::string output = "";

	// Makes a vector for all liked users
	User* temp = usersHead;
	std::vector<std::string> roster;
	while(temp != NULL)
	{	
		if (temp->phone == telephone)
		{
			for (unsigned int i = 0; i < temp->roster.length(); i += 13)
			{
				roster.push_back(temp->roster.substr(i, 12));
			}
			break;
		}
		temp = temp->next;
	}

	// Prints out user if they also match with passed user
	temp = usersHead;
	std::vector<User*> finalRoster;
	while (temp != NULL)
	{
		// Finds users that were swiped right
		if (std::count(roster.begin(), roster.end(), temp->phone) > 0)
		{
			// Checks if the swiped user also swiped right
			bool isMatch = (temp->roster.find(telephone) != std::string::npos);

			// Prints info of user if they matched
			if (isMatch){
				finalRoster.push_back(temp);
			}
		}
		temp = temp->next;
	}

	// Returns now if no users are found
	if (finalRoster.size() == 0){
		return "You do not have any matches at this moment.\n";
	}

	// Sorts list then outputs all matches
	std::sort(finalRoster.begin(), finalRoster.end(), compareMatchedUsers);
	for (unsigned int i = 0; i < finalRoster.size(); ++i)
	{
		addInfo(output, finalRoster[i]);
	}

	return output;
}

// Shows premium users who liked them
std::string like(const std::string &telephone, User* &usersHead)
{
	std::string output = "";

	User* temp = usersHead;
	bool isNotFound = true;
	while (temp != NULL)
	{	
		if (temp->phone == telephone && !temp->isPremium){
			return "Only premium users can view who liked you.";
		}
		else if (temp->roster.find(telephone) != std::string::npos)
		{
			addInfo(output, temp);
			isNotFound = false;
		}
		temp = temp->next;
	}

	if (isNotFound){
		return "You have not received any likes so far.";
	}
	return output;
}

// Unmatches two users from eachother
std::string unmatch(const std::string &phone1, User* &usersHead, const std::string &phone2)
{
	bool update1 = false;
	bool update2 = false;
	std::string person1 = "";
	std::string person2 = "";

	// Removes the matches from each user
	User* temp = usersHead;
	while (temp != NULL && (!update1 || !update2))
	{
		if (temp->phone == phone1)
		{
			update1 = true;
			person1 += temp->name + "'s match list:\n\n";
			for (unsigned int i = 0; i < temp->roster.length(); i += 13)
			{
				if (temp->roster.substr(i, 12) == phone2){
					temp->roster.erase(i, 13);
					i -= 13;
				}
			}
		}
		else if (temp->phone == phone2)
		{
			update2 = true;
			person2 += temp->name + "'s match list:\n\n";
			for (unsigned int i = 0; i < temp->roster.length(); i += 13)
			{
				if (temp->roster.substr(i, 12) == phone1){
					temp->roster.erase(i, 13);
					i -= 13;
				}
			}
		}
		temp = temp->next;
	}

	person1 += match(phone1, usersHead);
	person2 += match(phone2, usersHead);

	return person1 + "\n======\n\n" + person2;
}

// Allows a user to block another user
std::string block(const std::string &phone1, User* &usersHead, const std::string &phone2)
{
	bool update1 = false;
	bool update2 = false;
	std::string person1 = "profiles shown to ";
	std::string person2 = "profiles shown to ";

	// Blocks users from eachother
	User* temp = usersHead;
	while (temp != NULL && (!update1 || !update2))
	{
		if (temp->phone == phone1)
		{
			update1 = true;
			person1 += temp->name + ":\n\n";
			temp->blocked = phone2;
		}
		else if (temp->phone == phone2)
		{
			update2 = true;
			person2 += temp->name + ":\n\n";
			temp->blocked = phone1;
		}
		temp = temp->next;
	}

	person1 += profile(phone1, usersHead);
	person2 += profile(phone2, usersHead);

	return person1 + "\n======\n\n" + person2;
}

// Deletes linked list
void destroy_list(User* &usersHead) 
{
  	User* next;
  	while (usersHead != NULL) 
  	{
     	next = usersHead->next;
     	delete usersHead;
     	usersHead = next;
  	}
}

int main(int argc, char const *argv[])
{
	// Opens input file
	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open()){
        std::cerr << "Failed to open " << argv[1] << std::endl;
        return 1;
    }

    // Opens output file
    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()){
        std::cerr << "Failed to open " << argv[2] << std::endl;
        return 1;
    }

    // Linked list Head and Tail
    User* usersHead = NULL;
    User* usersTail = NULL;

    std::string name, gender, phone, job, school, sexuality, roster, age1, minAge1, maxAge1, maxDist1, lati1, longi1, isPremium1;
    while (inputFile >> name >> age1 >> gender >> phone >> job >> school >> lati1 >> longi1 >> isPremium1 >> minAge1 >> maxAge1 >> maxDist1 >> sexuality >> roster)
	{	
    	// Convert info to needed types
		int age = std::stoi(age1);
		int minAge = std::stoi(minAge1);
		int maxAge = std::stoi(maxAge1);
		int maxDist = std::stoi(maxDist1);
    	float lati = std::stof(lati1);
		float longi = std::stof(longi1);
    	bool isPremium = (isPremium1 == "true");

    	// Stores info
    	User* newUser = new User(name, age, gender, phone, job, school, lati, longi, isPremium, minAge, maxAge, maxDist, sexuality, roster);

		if (usersHead == NULL){
			usersHead = newUser;
			usersTail = newUser;
		}
		else{
			usersTail->next = newUser;
			usersTail = newUser;
		}
    }

    // Runs specified command
    std::string outputText;
    std::string command = argv[4];
    if (command == "profile"){
    	outputText = profile(argv[3], usersHead);
    }
    else if (command == "match"){
    	outputText = match(argv[3], usersHead);
    }
    else if (command == "like"){
    	outputText = like(argv[3], usersHead);
    }
    else if (command == "unmatch"){
		outputText = unmatch(argv[3], usersHead, argv[5]);
    }
    else if (command == "block"){
		outputText = block(argv[3], usersHead, argv[5]);
    }
	
    // Displays output text
    outputFile << outputText;

    destroy_list(usersHead);
	return 0;
}