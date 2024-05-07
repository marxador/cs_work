#ifndef __COMMENT_H
#define __COMMENT_H
#include <iostream>
#include <vector>

class Comment {
private:
    std::string video_id;
    std::string author;
    std::string comment_id;
    int like_count;
    int reply_count;
    bool is_reply;
    std::string parent_comment_id;
    std::string published_date;
    std::string crawled_date;
    bool is_video_owner;
    std::string comment_text;

public:
    Comment(const std::string& text);
    Comment(const std::string& comment_id1, const std::string& author1, const std::string& comment_text1, const std::string& parent_comment_id1);
    Comment(const std::string& comment_id1, const std::string& author1, const std::string& comment_text1);

    // Getters
    std::string getVideoId() const { return video_id; }
    std::string getAuthor() const { return author; }
    std::string getCommentId() const { return comment_id; }
    int getLikeCount() const { return like_count; }
    int getReplyCount() const { return reply_count; }
    bool getIsReply() const { return is_reply; }
    std::string getParentCommentId() const { return parent_comment_id; }
    std::string getPublishedDate() const { return published_date; }
    std::string getCrawledDate() const { return crawled_date; }
    bool getIsVideoOwner() const { return is_video_owner; }
    std::string getCommentText() const { return comment_text; }

    void incrementLikes() { like_count++; }
    void incrementReply() { reply_count++; }
};
#endif