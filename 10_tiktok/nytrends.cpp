#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include "sound.h"
#include "hashtag.h"
using namespace std;

// Custom comparator function for sorting sounds in the vector
struct CompareSound {
    bool operator()(const vector<Sound>& a, const vector<Sound>& b) const {
        // Calculate total views for each vector
        long int totalViewsA = 0, totalViewsB = 0;
        for (const Sound& sound : a) {
            totalViewsA += sound.getViews();
        }
        for (const Sound& sound : b) {
            totalViewsB += sound.getViews();
        }
        // Sort by total views
        if (totalViewsA != totalViewsB) {
            return totalViewsA < totalViewsB;
        }
        // If total views are equal, sort by song ID
        return a[0].getSongId() > b[0].getSongId();
    }
};

// Custom JSON parser function
Hashtag parseJsonHashtag(const string& json) {
    // Find and extract relevant fields from JSON string
    size_t coverUrlPos = json.find("\"coverUrl\": \"");
    size_t webVideoUrlPos = json.find("\"webVideoUrl\": \"");
    size_t playCountPos = json.find("\"playCount\": ");
    size_t textPos = json.find("\"text\": \"");

    if (coverUrlPos != string::npos && webVideoUrlPos != string::npos && playCountPos != string::npos &&
        textPos != string::npos) {
        // Extract cover URL
        size_t coverUrlStart = coverUrlPos + 13; // length of "\"coverMediumUrl\": \""
        size_t coverUrlEnd = json.find("\",", coverUrlStart);
        string coverUrl = json.substr(coverUrlStart, coverUrlEnd - coverUrlStart);

        // Extract web video URL
        size_t webVideoUrlStart = webVideoUrlPos + 16; // length of "\"webVideoUrl\": \""
        size_t webVideoUrlEnd = json.find("\"", webVideoUrlStart);
        string webVideoUrl = json.substr(webVideoUrlStart, webVideoUrlEnd - webVideoUrlStart);

        // Extract play count (views)
        size_t playCountStart = playCountPos + 12; // length of "\"playCount\": "
        size_t playCountEnd = json.find(",", playCountStart);
        long int views = stoi(json.substr(playCountStart, playCountEnd - playCountStart));

        // Extract text
        size_t textStart = textPos + 9; // length of "\"text\": \""
        size_t textEnd = json.find("\"", textStart);
        string text = json.substr(textStart, textEnd - textStart);

        // Extract hashtags from text hashtags.push_back(hashtag);
        vector<string> hashtags;
        // define a regular expression to match hashtags
        std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");

        // create an iterator for matching
        std::sregex_iterator hashtagIterator(text.begin(), text.end(), hashtagRegex);
        std::sregex_iterator endIterator;

        // iterate over the matches and extract the hashtags
        while (hashtagIterator != endIterator) {
            std::smatch match = *hashtagIterator;
            std::string hashtag = match.str(1);  // extract the first capturing group
        // this line will print each hash tag
        // if you want to do more with each hash tag, do it here. for example, store all hash tags in your container.
            hashtags.push_back(hashtag);

            ++hashtagIterator;
        }

        // Return Hashtag object
        return Hashtag(coverUrl, webVideoUrl, views, hashtags);
    } else {
        cerr << "Error: Required fields not found in JSON." << endl;
        return Hashtag("", "", 0, vector<string>());
    }
}

// Custom JSON parser function
Sound parseJsonSound(const string& json) {
    // Find and extract relevant fields from JSON string
    size_t coverUrlPos = json.find("\"coverUrl\": \"");
    size_t webVideoUrlPos = json.find("\"webVideoUrl\": \"");
    size_t playCountPos = json.find("\"playCount\": ");
    size_t musicNamePos = json.find("\"musicName\": \"");
    size_t musicAuthorPos = json.find("\"musicAuthor\": \"");
    size_t musicIdPos = json.find("\"musicId\": ");

    if (coverUrlPos != string::npos && webVideoUrlPos != string::npos && playCountPos != string::npos &&
        musicNamePos != string::npos && musicAuthorPos != string::npos && musicIdPos != string::npos) {
        // Extract cover URL
        size_t coverUrlStart = coverUrlPos + 13; // length of "\"coverMediumUrl\": \""
        size_t coverUrlEnd = json.find("\",", coverUrlStart);
        string coverUrl = json.substr(coverUrlStart, coverUrlEnd - coverUrlStart);

        // Extract web video URL
        size_t webVideoUrlStart = webVideoUrlPos + 16; // length of "\"webVideoUrl\": \""
        size_t webVideoUrlEnd = json.find("\"", webVideoUrlStart);
        string webVideoUrl = json.substr(webVideoUrlStart, webVideoUrlEnd - webVideoUrlStart);

        // Extract play count (views)
        size_t playCountStart = playCountPos + 12; // length of "\"playCount\": "
        size_t playCountEnd = json.find(",", playCountStart);
        int views = stoi(json.substr(playCountStart, playCountEnd - playCountStart));

        // Extract song title
        size_t musicNameStart = musicNamePos + 14; // length of "\"musicName\": \""
        size_t musicNameEnd = json.find("\",", musicNameStart);
        string songTitle = json.substr(musicNameStart, musicNameEnd - musicNameStart);

        // Extract song artist
        size_t musicAuthorStart = musicAuthorPos + 16; // length of "\"musicAuthor\": \""
        size_t musicAuthorEnd = json.find("\",", musicAuthorStart);
        string songArtist = json.substr(musicAuthorStart, musicAuthorEnd - musicAuthorStart);

        // Extract song ID
        size_t musicIdStart = musicIdPos + 12; // length of "\"musicId\": "
        size_t musicIdEnd = json.find("\"},", musicIdStart);
        string songId = json.substr(musicIdStart, musicIdEnd - musicIdStart);

        // Return Product object
        return Sound(coverUrl, webVideoUrl, views, songTitle, songArtist, songId);
    } else {
        cerr << "Error: Required fields not found in JSON." << endl;
        // Return an empty/invalid Product object
        return Sound("", "", 0, "", "", "");
    }
}

// Function to calculate the total views for a vector of sounds
long int getTotalViews(const vector<Sound>& sounds) {
    long int totalViews = 0;
    for (const Sound& sound : sounds) {
        totalViews += sound.getViews();
    }
    return totalViews;
}

// Comparator function for sorting sounds in the vector
bool compareSound(const Sound& a, const Sound& b) {
    // Sort by total views
    if (a.getViews() != b.getViews()) {
        return a.getViews() > b.getViews();
    }
    // If views are equal, sort by music ID
    return a.getSongId() < b.getSongId();
}

// Custom comparator function for sorting hashtags in the vector
bool compareHashtag(const pair<string, vector<Hashtag>>& a, const pair<string, vector<Hashtag>>& b) {
    // Sort by total usage count of the hashtag
    if (a.second.size() != b.second.size()) {
        return a.second.size() < b.second.size();
    }
    // If usage counts are equal, sort by total view count of associated videos
    long int totalViewsA = 0, totalViewsB = 0;
    for (const Hashtag& hashtag : a.second) {
        totalViewsA += hashtag.getViews();
    }
    for (const Hashtag& hashtag : b.second) {
        totalViewsB += hashtag.getViews();
    }
    if (totalViewsA != totalViewsB) {
        return totalViewsA < totalViewsB;
    }
    // If total view counts are equal, break the tie by comparing the hashtag names
    return a.first > b.first;
}

int main(int argc, char const *argv[])
{
    // Stores command line info
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    string trendType = argv[3];

    // Opens JSON file
    ifstream jsonFile(inputFileName);
    if (!jsonFile.is_open()) 
    {
        std::cerr << "Failed to open the JSON file." << std::endl;
        return 1;
    }

    // Runs specific command
    if (trendType == "hashtag")
    {
        unordered_map<string, vector<Hashtag>> tagMap;

        // Parses data into a hashtable
        string line;
        while(getline(jsonFile, line))
        {
            Hashtag video = parseJsonHashtag(line);
            vector<string> hashtags = video.getHashtags();
            for (size_t i = 0; i < hashtags.size(); ++i)
            {
                tagMap[hashtags[i]].push_back(video);
            }
        }

        // Priority queue to hold the sorted vectors of hashtags
        priority_queue<pair<string, vector<Hashtag>>, vector<pair<string, vector<Hashtag>>>, bool(*)(const pair<string, vector<Hashtag>>&, const pair<string, vector<Hashtag>>&)> pq(&compareHashtag);

        // Input sorted vectors into priority queue
        for (const pair<string, vector<Hashtag>> pair : tagMap) 
        {
            pq.push(pair);
        }

        // Write the hashtag map to the output file
        ofstream outputFile(outputFileName);
        if (!outputFile.is_open()) {
            cerr << "Failed to open the output file." << endl;
            return 1;
        }

        outputFile << "trending hashtags:\n" << endl;
        for (int i = 0; i < 10 && !pq.empty(); ++i) {
            pair<string, vector<Hashtag>> topPair = pq.top();
            pq.pop();

            outputFile << "========================" << endl;
            outputFile << "#" << topPair.first << endl;
            outputFile << "used " << topPair.second.size() << " times" << endl;

            // Sort videos associated with the hashtag by view count
            sort(topPair.second.begin(), topPair.second.end(), [](const Hashtag& a, const Hashtag& b) {
                return a.getViews() > b.getViews();
            });

            long int totalViews = 0;
            for (const Hashtag& video : topPair.second) {
                totalViews += video.getViews();
            }
            outputFile << totalViews << " views" << endl;

            // Output top 3 videos for the hashtag
            outputFile << endl;
            for (size_t j = 0; j < min<size_t>(3, topPair.second.size()); ++j) {
                Hashtag video = topPair.second[j];
                outputFile << "cover url: " << video.getCoverUrl() << endl;
                outputFile << "web video url: " << video.getWebVideoUrl() << endl;
            }
            outputFile << "========================" << endl;
        }
    }
    else if (trendType == "sound") {
        unordered_map<string, vector<Sound>> soundMap;

        string line;
        while (getline(jsonFile, line)) {
            Sound video = parseJsonSound(line);
            soundMap[video.getSongId()].push_back(video);
        }

        // Sort each vector based on total view count and music ID
        for (unordered_map<string, vector<Sound>>::iterator it = soundMap.begin(); it != soundMap.end(); ++it) {
            sort(it->second.begin(), it->second.end(), compareSound);
        }

        /// Priority queue to hold the sorted vectors
        priority_queue<vector<Sound>, vector<vector<Sound>>, CompareSound> pq;

        // Input sorted vectors into priority queue
        for (unordered_map<string, vector<Sound>>::const_iterator it = soundMap.cbegin(); it != soundMap.cend(); ++it) {
            pq.push(it->second);
        }

        // Write the sound map to the output file
        ofstream outputFile(outputFileName);
        if (!outputFile.is_open()) {
            cerr << "Failed to open the output file." << endl;
            return 1;
        }

        // Output trending sounds and associated videos
        outputFile << "trending sounds:\n" << endl;
        for (int i = 0; i < 10 && !pq.empty(); ++i) {
            vector<Sound> sounds = pq.top();
            pq.pop();

            outputFile << "========================" << endl;
            outputFile << sounds[0].getSongTitle() << endl;
            outputFile << getTotalViews(sounds) << " views" << endl;
            outputFile << sounds[0].getSongArtist() << endl;
            outputFile << "music id: " << sounds[0].getSongId() << endl;

            // Output top 3 videos for the sound
            outputFile << endl;
            for (size_t j = 0; j < min<size_t>(3, sounds.size()); ++j) {
                Sound video = sounds[j];
                outputFile << "cover url: " << video.getCoverUrl() << endl;
                outputFile << "web video url: " << video.getWebVideoUrl() << endl;
            }
            outputFile << "========================" << endl;
        }
    }
	return 0;
}