#include "business.h"
#include <iostream>

// Constructors
Business::Business(const std::string &aName, const std::string &aCategories, const float &aRating,
		const int &aPrice, const std::string &aCity, const int &aReviews)
{
	name = aName;
    categories = aCategories;
    rating = aRating;
    price = aPrice;
    city = aCity;
    reviews = aReviews;
}
// Operatorsc const
bool Business::operator <(Business const &other) const
{
	return other.rating < rating;
}