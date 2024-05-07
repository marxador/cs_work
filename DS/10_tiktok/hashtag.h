#ifndef __HASHTAG_H
#define __HASHTAG_H

#include <iostream>
#include <vector>
using namespace std;

class Hashtag {
private:
    string coverUrl;
    string webVideoUrl;
    long int views;
    vector<string> hashtags;

public:
    Hashtag(string coverUrl, string webVideoUrl, long int views, vector<string> hashtags)
        : coverUrl(coverUrl), webVideoUrl(webVideoUrl), views(views), hashtags(hashtags) {}

    // Getter methods
    string getCoverUrl() const { return coverUrl; }
    string getWebVideoUrl() const { return webVideoUrl; }
    long int getViews() const { return views; }
    vector<string> getHashtags() const { return hashtags; }
};

#endif