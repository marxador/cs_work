#ifndef __SOUND_H
#define __SOUND_H

#include <iostream>
#include <vector>
using namespace std;

class Sound {
private:
    string coverUrl;
    string webVideoUrl;
    long int views;
    string songTitle;
    string songArtist;
    string songId;

public:
    Sound(string coverUrl, string webVideoUrl, long int views, string songTitle, string songArtist, string songId)
        : coverUrl(coverUrl), webVideoUrl(webVideoUrl), views(views), songTitle(songTitle), songArtist(songArtist), songId(songId) {}

    // Getter methods
    string getCoverUrl() const { return coverUrl; }
    string getWebVideoUrl() const { return webVideoUrl; }
    long int getViews() const { return views; }
    string getSongTitle() const { return songTitle; }
    string getSongArtist() const { return songArtist; }
    string getSongId() const { return songId; }

    // Define the operator< to compare Sound objects
    bool operator<(const Sound& other) const {
        if (views != other.views) {
            return views > other.views; // Sort by views in descending order
        }
        return songId < other.songId; // If views are equal, sort by songId in ascending order
    }
};

#endif
