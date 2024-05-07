#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include "business.h"

// Code from submitty to get business names
std::string getName(const std::string& line)
{
    int start = 48;
    size_t end = line.find("\"", start);

    return line.substr(start, end - start);
}

// Code from submitty to get categories
std::string getCategories(const std::string& line)
{
    size_t start = line.find("categories");

    start += 13;
    size_t end = line.find("\"", start);

    return line.substr(start, end - start);
}

// Code from submitty to get ratings
float getRating(const std::string& line)
{
    size_t start = line.find("stars");

    start += 7;
    size_t end = line.find("\"", start);

    return std::stof(line.substr(start, end - start - 1));
}

// Code from submitty to get price
int getPrice(const std::string& line)
{
    size_t start = line.find("RestaurantsPriceRange2");

    // if not found, return an empty string
    if(start == std::string::npos){
            return -1;
    }

    start += 25;
    size_t end = line.find("\"", start);

    return std::stoi(line.substr(start, end - start));
}

// gets the city on a line - used submitty code to make
std::string getCity(const std::string& line)
{
    size_t start = line.find("city");

    start += 7;
    size_t end = line.find("\"", start);

    return line.substr(start, end - start);
}

// gets the number of reviews on a line - used submitty code to make
int getReviews(const std::string& line)
{
    size_t start = line.find("review_count");

    start += 14;
    size_t end = line.find("\"", start);

    return std::stoi(line.substr(start, end - start));
}

// gets the postal code on a line - used submitty code to make
std::string getPostalCode(const std::string& line)
{
    size_t start = line.find("postal_code");

    start += 14;
    size_t end = line.find("\"", start);

    return line.substr(start, end - start);
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

    // Stores other important info
    std::string categories[argc - 4];
    for (int i = 0; i < argc - 4; ++i){
        categories[i] = argv[i + 4];
    }

    // Creates a list to store all the businesses
    std::list<Business> businesses;
    std::string line;

    while(getline(inputFile, line))
    {
        if (argv[3] == getPostalCode(line))
        {
            std::string tempCategories = getCategories(line);
            for (const std::string &category : categories)
            {
                if (tempCategories.find(category) != std::string::npos)
                {
                    // Makes an business object and adds it to the list
                    businesses.emplace_back(getName(line), tempCategories, getRating(line), getPrice(line), getCity(line), getReviews(line));
                    break;
                }
            }
        }
    }


    // Prints info into output file
    if (businesses.size() == 0){
        outputFile << "Sorry, we couldn't find any results";
    }
    else
    {
        // Sorts list by rating
        businesses.sort();
        int number = 1;
        for(const Business &business : businesses)
        {
            outputFile << "=====================\n";
            // Helpful variables
            float rating = business.getRating();
            int stars = rating;

            outputFile << number << ". " << business.getName() << std::endl;
            
            for (int i = 0; i < stars; ++i){
                outputFile << "\u2605";
            }
            if (stars < rating){
                outputFile << "\u00BD";
            }
            outputFile << " " << rating << " (" << business.getReviews() << " reviews)\n";

            outputFile << business.getCity() << " ";
            for (int i = 0; i < business.getPrice(); ++i){
                outputFile << '$';
            }
            outputFile << std::endl;

            outputFile << business.getCategories() << std::endl; 
            ++number;
        }
        outputFile << "=====================";
    }
    return 0;
}