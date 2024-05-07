#ifndef __PRODUCT_H
#define __PRODUCT_H
#include <iostream>
using namespace std;

class Product {
private:
    string title;
    double averageRating;
    int ratingNumber;
    string imageUrl;
    double price;

public:
    // Constructor
    Product() : title(""), averageRating(0.0), ratingNumber(0), imageUrl(""), price(-1.0) {}
    Product(const string& title, const double& averageRating, const int& ratingNumber, const string& imageUrl, const double& price)
        : title(title), averageRating(averageRating), ratingNumber(ratingNumber), imageUrl(imageUrl), price(price) {}

    // Getters
    string getTitle() const { return title; }
    double getAverageRating() const { return averageRating; }
    int getRatingNumber() const { return ratingNumber; }
    string getImageUrl() const { return imageUrl; }
    double getPrice() const { return price; }

    bool operator<(const Product& o) const
    {
        if (o.averageRating != averageRating)
            return o.averageRating < averageRating;
        if (o.price != price)
            return o.price > price;
        return o.title > title;
    }
};
#endif