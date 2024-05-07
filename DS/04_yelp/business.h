#ifndef __BUSINESS_H
#define __BUSINESS_H
#include <iostream>

class Business
{
private:
	// Member variables
	std::string name;
    std::string categories;
    float rating;
    int price;
    std::string city;
    int reviews;

public:
	// Constuctor
	Business(const std::string &aName, const std::string &aCategories, const float &aRating,
		const int &aPrice, const std::string &aCity, const int &aReviews);

	// Getters const
	std::string getName() const { return name; }
	std::string getCategories() const { return categories; }
	float getRating() const { return rating; }
	int getPrice() const { return price; }
	std::string getCity() const { return city; }
	int getReviews() const { return reviews; }

	// Operators const
	bool operator <(Business const &other) const;
};
#endif