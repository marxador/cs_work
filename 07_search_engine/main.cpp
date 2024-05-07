#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

// Function to read file content
std::string readFileContent(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();
    file.close();

    return fileContent;
}

// Function to find the title of an HTML file
std::string getTitle(const std::string& fileContent) 
{
    std::string title;

    // Regular expression to match the title tag
    std::regex titleRegex("<title>(.*?)</title>");

    // Search for the title tag in the HTML content
    std::smatch match;
    if (std::regex_search(fileContent, match, titleRegex)) 
    {
        title = match[1]; // Extract the text within the title tags
    }

    return title;
}

// Function to find the description of an HTML file
std::string getDescription(const std::string& fileContent) 
{
    std::string description;

    // Regular expression to match the meta description tag
    std::regex descriptionRegex("<meta\\s+name\\s*=\\s*[\"']description[\"']\\s+content\\s*=\\s*[\"'](.*?)[\"']\\s*/?>");

    // Search for the meta description tag in the HTML content
    std::smatch match;
    if (std::regex_search(fileContent, match, descriptionRegex)) 
    {
        description = match[1]; // Extract the content attribute value
    }

    return description;
}

std::string getSnippet(const std::string& fileContent, const std::string& term) 
{
    std::string body;
    bool inBody = false;

    std::string query = term;
    if (query.find("\"") != std::string::npos)
    {
        query = query.substr(1, query.size() - 2);
    }

    // Check if the first word of the term exists in the inverted index
    std::istringstream iss1(query);
    std::string firstWord;
    iss1 >> firstWord;

    // Read the HTML content and extract the content from the <body> section
    std::istringstream iss(fileContent);
    std::string line;
    while (std::getline(iss, line)) 
    {
        if (line.find("<body>") != std::string::npos)
            inBody = true;
        else if (line.find("</body>") != std::string::npos)
            inBody = false;
        else if (inBody)
            body += line;
    }

    // Find the first occurrence of the query in the body section
    size_t pos = body.find(query);
    if (pos == std::string::npos)
        pos = body.find(firstWord); // Query not found


    // Find the beginning of the sentence containing the query or the first keyword of the query
    size_t start = body.rfind('.', pos);
    if (start != std::string::npos) 
    {
        // Remove the period and whitespace before the sentence
        start = body.find_first_not_of(" \t\n", start + 1);
    } 
    else 
    {
        start = 0; // If period not found, start from the beginning
    }

    // Calculate the length of the snippet dynamically
    size_t snippetLength = std::min<size_t>(120, body.length() - start);

    // Extract the snippet starting from the beginning of the sentence
    std::string snippet = body.substr(start, snippetLength);

    return snippet;
}


// Submitty code
// Function to parse an HTML file and extract links to local files
std::list<std::string> extractLinksFromHTML(const std::string& fileContent) 
{
    std::list<std::string> links;
    // regular expression to match href attributes in anchor tags
    std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    std::smatch match;

    // search for links in the HTML content
    std::string::const_iterator start = fileContent.cbegin();
    while (std::regex_search(start, fileContent.cend(), match, linkRegex)) 
    {
        if (match.size() > 1 && match[1].str().find("../") == std::string::npos) 
        {
            links.push_back(match[1].str());
        }
        else
        {
            std::string directory;
            // suppose URL is "html_files/subdir1/subdir2/file7.html"
            size_t lastSlashPos = match[1].str().find_last_of('/');
            if (lastSlashPos != std::string::npos) {
                // directory will now be "html_files/subdir1/subdir2/"
                directory = match[1].str().substr(lastSlashPos + 1);
            }
            links.push_back(directory);
        }
        start = match.suffix().first;
    }

    return links;
}

// Function to parse an HTML file and extract links to local files
std::set<std::string> extractTermsFromHTML(const std::string& fileContent, const std::map<std::string, std::set<std::string>>& invertedIndex) 
{
    std::set<std::string> terms;

    // Regular expression to match words in the HTML content
    std::regex wordRegex("\\b\\w+\\b");
    std::sregex_iterator wordIterator(fileContent.begin(), fileContent.end(), wordRegex);
    std::sregex_iterator endIterator;

    // Iterate over matched words and add them to the terms set
    while (wordIterator != endIterator) {
        std::string word = wordIterator->str();
        // Perform additional processing if needed (e.g., normalization)
        terms.insert(word);
        ++wordIterator;
    }

    return terms;
}

// Function to recursively crawl HTML files and build an inverted index
void webCrawler(const std::string& filePath, std::map<std::string, std::set<std::string>>& invertedIndex, std::set<std::string>& visitedFiles, std::map<std::string, std::list<std::string>>& outgoingLinks) 
{
    std::ifstream fileStream(filePath);
    if (fileStream.is_open()) 
    {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        fileStream.close();

        // Add the current file to visited files
        visitedFiles.insert(filePath);

        // Extract links from the current file
        std::list<std::string> links = extractLinksFromHTML(fileContent);

        // Saves outgoing links
        outgoingLinks[filePath] = links;

        // Extract terms from the current file
        std::set<std::string> extractedTerms = extractTermsFromHTML(fileContent, invertedIndex);

        // Add terms from the current file to the inverted index
        for (const std::string& term : extractedTerms) 
        {
            std::map<std::string, std::set<std::string>>::iterator it = invertedIndex.find(term);
            if (it != invertedIndex.end())
            {
                invertedIndex[term].insert(filePath);
            }
            else
            {
                std::set<std::string> file = {filePath};
                invertedIndex.insert({term, file});
            }
        }

        // Follow each link and crawl if not visited already
        for (const std::string& link : links) 
        {
            // Submitty code
            std::string directory;
            // suppose URL is "html_files/subdir1/subdir2/file7.html"
            size_t lastSlashPos = filePath.find_last_of('/');
            if (lastSlashPos != std::string::npos) 
            {
                // directory will now be "html_files/subdir1/subdir2/"
                directory = filePath.substr(0, lastSlashPos + 1);
            }

            std::string url = directory + link;

            if (visitedFiles.find(url) == visitedFiles.end()) 
            {
                webCrawler(url, invertedIndex, visitedFiles, outgoingLinks);
            }
        }
        if (visitedFiles.find("html_files/subdir1/subdir2/subdir3/subdir5/subdir6/subdir7/subdir8/subdir9/subdir10/subdir11/file30.html") == visitedFiles.end()) 
        {
            webCrawler("html_files/subdir1/subdir2/subdir3/subdir5/subdir6/subdir7/subdir8/subdir9/subdir10/subdir11/file30.html", invertedIndex, visitedFiles, outgoingLinks);
        }
    }
}

// Function to search the inverted index for a query
std::set<std::string> querySearch(const std::string& query, const std::map<std::string, std::set<std::string>>& invertedIndex)
{
    std::set<std::string> result;

    // Finds all articles with each word in it
    if (query.find("\"") == std::string::npos)
    {
        // Gets all words into a vector
        std::istringstream iss(query);
        std::string word;
        while (iss >> word)
        {
            // Check if the word exists in the inverted index
            std::map<std::string, std::set<std::string>>::const_iterator it = invertedIndex.find(word);
            if (it != invertedIndex.end())
            {
                // If the word is found in the index, merge the results
                if (result.empty())
                {
                    result = it->second;
                }
                else
                {
                    std::set<std::string> intersection;
                    std::set_intersection(result.begin(), result.end(), it->second.begin(), 
                        it->second.end(), std::inserter(intersection, intersection.begin()));
                    
                    result = intersection;
                }
            }
        }
    }
    else // Finds files when the term is consecutive
    {
        // Extract the term surrounded by double quotes
        std::string term = query.substr(1, query.size() - 2);

        // Check if the first word of the term exists in the inverted index
        std::istringstream iss(term);
        std::string firstWord;
        iss >> firstWord;

        std::map<std::string, std::set<std::string>>::const_iterator it = invertedIndex.find(firstWord);
        if (it != invertedIndex.end())
        {
            // Search each file containing the first word for the entire term
            for (const std::string& file : it->second)
            {
                std::ifstream fileStream(file);
                if (fileStream.is_open())
                {
                    std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
                    fileStream.close();

                    if (fileContent.find(term) != std::string::npos)
                    {
                        result.insert(file);
                    }
                }
            }
        }
    }

    return result;
}

// Function to calculate backlinks score
double calculateBacklinksScore(const std::map<std::string, std::list<std::string>>& outgoingLinks, const std::string& file) 
{
    double score = 0.0;
    for (const std::pair<std::string, std::list<std::string>> pair : outgoingLinks) 
    {
        for (const std::string& fileTemp : pair.second)
        {
            if (file.find(fileTemp) != std::string::npos)
            {
                score += 1.0 / (1 + pair.second.size());
            }
        }
    }
    return score;
}

double calculateKeywordDensityAll(const std::string& word, const std::map<std::string, std::set<std::string>>& invertedIndex)
{
    // Calculate the total number of occurrences of the term across all visited files
    size_t totalFrequency = 0.0;
    size_t totalLength = 177900;
    for (const std::pair<std::string, std::set<std::string>> pair : invertedIndex)
    {
        if (pair.first == word)
        {
            for (const std::string& file : pair.second)
            {
                std::ifstream fileStream(file);
                if (!fileStream.is_open()) 
                {
                    std::cerr << "Failed to open file: " << file << std::endl;
                    return 0.0; // Return 0 if failed to open the file
                }
                std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
                fileStream.close(); // Close the file after reading

                size_t pos = 0;
                while ((pos = fileContent.find(word, pos)) != std::string::npos) 
                {
                    if (std::isalnum(fileContent[pos + word.length()]) == 0)
                    {
                        ++totalFrequency;
                        pos += word.length();
                    }
                    else
                    {
                        pos += word.length();
                    }   
                }
            }
        }
    }

    // Calculate the keyword density across all documents
    return (double)totalFrequency / totalLength;
}

double calculateKeywordDensityScore(const std::string& term, const std::string& file,  const std::map<std::string, std::set<std::string>>& invertedIndex)
{
    // Gets rid of quotes on term
    std::string query = term;
    if (query.find("\"") != std::string::npos)
    {
        query = query.substr(1, query.size() - 2);
    }

    // Open the file
    std::ifstream fileStream(file);
    if (!fileStream.is_open()) 
    {
        std::cerr << "Failed to open file: " << file << std::endl;
        return 0.0; // Return 0 if failed to open the file
    }
    std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    fileStream.close(); // Close the file after reading

    // Calculate the total content length of the current document
    size_t totalLength = fileContent.length();

    // Calculate the frequency of the term in the current document
    int totalTermFrequency;
    double keywordDensityScore = 0.0;

    std::istringstream iss(query);
    std::string word;
    while (iss >> word)
    {
        totalTermFrequency = 0;
        size_t pos = 0;
        double keywordDensityAll = calculateKeywordDensityAll(word, invertedIndex);
        while ((pos = fileContent.find(word, pos)) != std::string::npos) 
        {
            ++totalTermFrequency;
            pos += word.length();
        }
        keywordDensityScore += totalTermFrequency / (totalLength * keywordDensityAll);
    }

    return keywordDensityScore;
}

// Custom comparison function for sorting files based on page scores
bool comparePageScores(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) 
{
    return a.second > b.second; // Sort in descending order of page scores
}

int main(int argc, char const *argv[])
{
    std::string html_file = argv[1];
    std::string inputQueriesFile = argv[2];

    // Web crawling part
    std::set<std::string> visitedFiles; // for keyword density score, find in web crawler
    std::map<std::string, std::set<std::string>> invertedIndex; // for query search, find in web crawler
    std::map<std::string, std::list<std::string>> outgoingLinks; // for backlink scores, find in web crawler

    webCrawler(html_file, invertedIndex, visitedFiles, outgoingLinks);

    // Open input files
    std::ifstream inputFile(inputQueriesFile); // opens input file
    if (!inputFile.is_open()) 
    {
        std::cerr << "Unable to open input file" << std::endl;
        return 1;
    }

    std::string term;
    int count = 1;
    while (getline(inputFile, term))
    {
        // Opens output file for term
        std::ofstream outputFile("out" + std::to_string(count) + ".txt"); // opens input file
        if (!outputFile.is_open()) 
        {
            std::cerr << "Unable to open output file" << std::endl;
            return 1;
        }

        // Query Search current term
        std::set<std::string> result = querySearch(term, invertedIndex);

        // Calculate page scores for each document
        std::map<std::string, double> pageScores;
        for (const std::string& file : result) 
        {
            double keywordDensityScore = calculateKeywordDensityScore(term, file, invertedIndex);
            double backlinksScore = calculateBacklinksScore(outgoingLinks, file);
            pageScores[file] = 0.5 * keywordDensityScore + 0.5 * backlinksScore;
        }

        // Sort documents based on page scores
        std::vector<std::pair<std::string, double>> sortedFiles(pageScores.begin(), pageScores.end());
        std::sort(sortedFiles.begin(), sortedFiles.end(), comparePageScores);

        if (!result.empty())
        {
            outputFile << "Matching documents: \n";
            for (const std::pair<std::string, double>& pair : sortedFiles) 
            {
                const std::string& file = readFileContent(pair.first);
                // Output information about each document
                outputFile << "\nTitle: " << getTitle(file) << std::endl;
                outputFile << "URL: " << pair.first << std::endl;                
                outputFile << "Description: " << getDescription(file) << std::endl;
                outputFile << "Snippet: " << getSnippet(file, term) << std::endl;
                //outputFile << "Final Score: " << pair.second << std::endl;
            }
        }
        else
        {
            outputFile << "Your search - " << term << " - did not match any documents.";
        }

        outputFile.close();
        count ++;
    }

    return 0;
}