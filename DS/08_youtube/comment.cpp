#include "comment.h"
#include <iostream>
#include <sstream>
#include <string>

std::string trim(const std::string& str) {
    size_t start = 0;
    while (start < str.size() && std::isspace(str[start])) {
        ++start;
    }

    size_t end = str.size();
    while (end > start && std::isspace(str[end - 1])) {
        --end;
    }

    return str.substr(start, end - start);
}

// Constructors/Destructor
Comment::Comment(const std::string& text) {
    std::istringstream iss(text);

    std::string key, value;
    while (std::getline(iss, key, ':')) {
        // Trim whitespace and remove quotes from key
        key = trim(key);
        key = key.substr(1, key.size() - 2);

        // Read the value
        if (key == "comment")
        {
            std::getline(iss, value, '}'); // Trim at ", \""
            value = trim(value);
        }
        else
        {
            std::getline(iss, value, ','); // Trim at ", \""
            value = trim(value);
        }
        
        if (key != "like_count" && key != "reply_count")
            value = value.substr(1, value.size() - 2);
        

        // Assign values to corresponding fields
        if (key == "video_id")
            video_id = value;
        else if (key == "author")
            author = value;
        else if (key == "comment_id")
            comment_id = value;
        else if (key == "like_count")
            like_count = std::stoi(value);
        else if (key == "reply_count")
            reply_count = std::stoi(value);
        else if (key == "is_reply")
            is_reply = (value == "true");
        else if (key == "parent_comment_id")
            parent_comment_id = value;
        else if (key == "published_date")
            published_date = value;
        else if (key == "crawled_date")
            crawled_date = value;
        else if (key == "is_video_owner")
            is_video_owner = (value == "true");
        else if (key == "comment")
            comment_text = value;
    }
}

Comment::Comment(const std::string& comment_id1, const std::string& author1, const std::string& comment_text1, const std::string& parent_comment_id1)
{
    video_id = "";
    author = author1;
    comment_id = comment_id1;
    like_count = 0;
    reply_count = 0;
    is_reply = true;
    parent_comment_id = parent_comment_id1;
    published_date = "0 seconds ago";
    crawled_date = "2023-10-29T22:51:46.227795";
    is_video_owner = false;
    comment_text = comment_text1;
}

Comment::Comment(const std::string& comment_id1, const std::string& author1, const std::string& comment_text1)
{
    video_id = "";
    author = author1;
    comment_id = comment_id1;
    like_count = 0;
    reply_count = 0;
    is_reply = false;
    parent_comment_id = "";
    published_date = "0 seconds ago";
    crawled_date = "2023-10-29T22:51:46.227795";
    is_video_owner = false;
    comment_text = comment_text1;
}
