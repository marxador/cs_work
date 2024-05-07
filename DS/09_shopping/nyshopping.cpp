#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "product.h"
#include "BPlusTree.h"
using namespace std;


// Custom JSON parser function
Product parseJson(const string& json) 
{
    // Find and extract relevant fields from JSON string
    size_t titlePos = json.find("\"title\": \"");
    size_t ratingPos = json.find("\"average_rating\": ");
    size_t ratingNumberPos = json.find("\"rating_number\": ");
    size_t imagePos = json.find("\"thumb\": \"");
    size_t pricePos = json.find("\"price\": ");

    if (titlePos != string::npos && ratingPos != string::npos && ratingNumberPos != string::npos &&
        imagePos != string::npos && pricePos != string::npos) 
    {
        // Extract title
        size_t titleStart = titlePos + 10; // length of "\"title\": \""
        size_t titleEnd = json.find("average_rating", titleStart);
        string title = json.substr(titleStart, titleEnd - titleStart - 4);

        // Extract rating
        size_t ratingStart = ratingPos + 18; // length of "\"average_rating\": "
        size_t ratingEnd = json.find(",", ratingStart);
        double rating = stod(json.substr(ratingStart, ratingEnd - ratingStart));

        // Extract rating number
        size_t ratingNumberStart = ratingNumberPos + 17; // length of "\"rating_number\": "
        size_t ratingNumberEnd = json.find(",", ratingNumberStart); 
        int ratingNumber = stoi(json.substr(ratingNumberStart, ratingNumberEnd - ratingNumberStart));

        // Extract image URL
        size_t imageStart = imagePos + 10; // length of "\"thumb\": \""
        size_t imageEnd = json.find("\"", imageStart);
        string imageUrl = json.substr(imageStart, imageEnd - imageStart);

        // Extract price
        size_t priceStart = pricePos + 9; // length of "\"price\": "
        size_t priceEnd = json.find(",", priceStart);
        string strPrice = json.substr(priceStart, priceEnd - priceStart);
        if (strPrice == "null")
        {
        	// Return an invalid Product object
        	return Product(title, rating, ratingNumber, imageUrl, -1.0);
        }
		double price = stod(strPrice);

        // Return Product object
        return Product(title, rating, ratingNumber, imageUrl, price);
    } 
    else 
    {
        cerr << "Error: Required fields not found in JSON." << endl;
        // Return an empty/invalid Product object
        return Product("", 0.0, 0, "", -1.0);
    }
}

int main(int argc, char** argv)
{
	// Stores command line info
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	double minPrice = stod(argv[3]);
	double maxPrice = stod(argv[4]);

	// JSON parseing + making B+ tree
	BPlusTree bptree(minPrice, maxPrice);

	ifstream jsonFile(inputFileName);
    if (!jsonFile.is_open()) 
    {
        std::cerr << "Failed to open the JSON file." << std::endl;
        return 1;
    }

    string line;
    while(getline(jsonFile, line))
    {
    	Product product = parseJson(line);
    	if (product.getPrice() != -1.0)
    	{
    		bptree.insert(product); // Stores each product into the B+ tree
    	}
    }

    // Completes Range Search and stores it in result
    vector<Product> result = bptree.collectInRange(minPrice, maxPrice);
    sort(result.begin(), result.end());
	
    // Outputs results into output file
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
    	std::cerr << "Failed to open the output file." << std::endl;
        return 1;
    }

	for (Product product : result)
	{
        outputFile << product.getTitle() << endl;
        outputFile << product.getAverageRating() << endl;
        outputFile << product.getRatingNumber() << endl;
        outputFile << product.getImageUrl() << endl;
        outputFile << "$" << product.getPrice() << endl;
	}

    bptree.deleteBPlusTree();
    return 0;
}