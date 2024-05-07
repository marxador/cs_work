#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

// Submitty code
// Function to parse an HTML file and extract links to local files
std::list<std::string> extractLinksFromHTML(const std::string& fileContent) 
{
    // Implementation remains the same
}

// Function to parse an HTML file and extract links to local files
std::set<std::string> extractTermsFromHTML(const std::string& fileContent, const std::map<std::string, std::set<std::string>>& invertedIndex) 
{
    // Implementation remains the same
}

// Function to recursively crawl HTML files and build an inverted index
void webCrawler(const std::string& filePath, std::map<std::string, std::set<std::string>>& invertedIndex, std::set<std::string>& visitedFiles) 
{
    // Implementation remains the same
}

// Function to search the inverted index for a query
std::set<std::string> querySearch(const std::string& query, const std::map<std::string, std::set<std::string>>& invertedIndex)
{
    // Implementation remains the same
}

// Function to find the title of an HTML file
std::string getTitle(const std::string& filename) 
{
    // Implementation remains the same
}

// Function to find the description of an HTML file
std::string getDescription(const std::string& filename) 
{
    // Implementation remains the same
}

std::string getSnippet(const std::string& filename, const std::string& query) 
{
    // Implementation remains the same
}

// Function to calculate keyword density score
double calculateKeywordDensityScore(const std::string& filename, const std::map<std::string, std::set<std::string>>& invertedIndex, int totalContentLength) 
{
    int totalKeywordOccurrences = 0;
    std::set<std::string> terms = extractTermsFromHTML(filename, invertedIndex);
    for (const std::string& term : terms) {
        std::map<std::string, std::set<std::string>>::const_iterator it = invertedIndex.find(term);
        if (it != invertedIndex.end()) {
            totalKeywordOccurrences += it->second.count(filename);
        }
    }
    double keywordDensityAcrossAllDocuments = static_cast<double>(totalKeywordOccurrences) / totalContentLength;
    return static_cast<double>(totalKeywordOccurrences) / (totalContentLength * keywordDensityAcrossAllDocuments);
}

// Function to calculate backlinks score
int calculateBacklinksScore(const std::string& filename, const std::map<std::string, std::set<std::string>>& invertedIndex) 
{
    return invertedIndex.count(filename); // Number of documents linking to this document
}

// Function to calculate page score based on the given formula
double calculatePageScore(const std::string& filename, const std::map<std::string, std::set<std::string>>& invertedIndex, int totalContentLength) 
{
    double keywordDensityScore = calculateKeywordDensityScore(filename, invertedIndex, totalContentLength);
    int backlinksScore = calculateBacklinksScore(filename, invertedIndex);
    return 0.5 * keywordDensityScore + 0.5 * backlinksScore;
}

// Custom comparison function for sorting files based on page scores
bool comparePageScores(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) 
{
    return a.second > b.second; // Sort in descending order of page scores
}

int main(int argc, char const *argv[])
{
    // Initialization remains the same

    // Loop through each query term
    int count = 1;
    std::string term;
    while (getline(inputFile, term))
    {
        // Query Search current term
        std::set<std::string> result = querySearch(term, invertedIndex);

        // Calculate total content length
        // For simplicity, let's assume it's the sum of lengths of all documents' content
        int totalContentLength = 0;
        for (const auto& pair : invertedIndex) {
            std::ifstream file(pair.first);
            if (file.is_open()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                totalContentLength += buffer.str().length();
                file.close();
            }
        }

        // Calculate page scores for each document
        std::map<std::string, double> pageScores;
        for (const std::string& file : result) 
        {
            pageScores[file] = calculatePageScore(file, invertedIndex, totalContentLength);
        }

        // Sort documents based on page scores
        std::vector<std::pair<std::string, double>> sortedFiles(pageScores.begin(), pageScores.end());
        std::sort(sortedFiles.begin(), sortedFiles.end(), comparePageScores);

        // Output sorted results
        std::ofstream outputFile("out" + std::to_string(count) + ".txt");
        if (!outputFile.is_open()) 
        {
            std::cerr << "Unable to open output file" << std::endl;
            return 1;
        }

        if (!result.empty())
        {
            outputFile << "Matching documents:\n";
            for (const std::pair<std::string, double>& pair : sortedFiles) {
                const std::string& file = pair.first;
                // Output information about each document
                outputFile << "\nTitle: " << getTitle(file) << std::endl;
                outputFile << "URL: " << file << std::endl;                
                outputFile << "Description: " << getDescription(file) << std::endl;
                outputFile << "Snippet: " << getSnippet(file, term) << std::endl;
            }
        }
        else
        {
            outputFile << "Your search - " << term << " - did not match any documents.";
        }

        outputFile.close();
        count++;
    }

    return 0;
}
