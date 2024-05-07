#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include "comment.h"

template <class T> 
struct TreeNode 
{
	TreeNode() : left(nullptr), right(nullptr) {}
	TreeNode(const T& init) : value(init), left(nullptr), right(nullptr) {}

	T value;
	TreeNode* left;
	TreeNode* right;
};

// Function to insert a new comment into the tree
template <class T>
void insertComment(TreeNode<T>*& root, const T& comment) 
{
    if (root == nullptr) 
    {
        root = new TreeNode<T>(comment);
        return;
    }

    // Check if the comment is a reply to another comment
    if (comment.getParentCommentId() != "") 
    {
        // Find the parent comment in the tree
        TreeNode<T>* parent = searchComment(root, comment.getParentCommentId());
        if (parent != nullptr) 
        {
            // Check if the parent already has replies
            if (parent->left != nullptr) 
            {
                // Find the last sibling comment in the parent's replies
                TreeNode<T>* lastSibling = parent->left;
                while (lastSibling->right != nullptr) 
                {
                    lastSibling = lastSibling->right;
                }

                // Insert the new comment as the right sibling of the last sibling
                lastSibling->right = new TreeNode<T>(comment);
            } 
            else 
            {
                // If the parent doesn't have any replies yet, insert the new comment as its first child
                parent->left = new TreeNode<T>(comment);
            }
        } 
        else 
        {
            std::cerr << "Parent comment with ID " << comment.getParentCommentId() << " not found." << std::endl;
        }
    } 
    else 
    {
        // If it's not a reply, insert as a sibling comment
        insertSiblingComment(root, comment);
    }
}

// Function to insert a comment as a sibling
template <class T>
void insertSiblingComment(TreeNode<T>*& root, const T& comment) 
{
    if (root == nullptr) 
    {
        root = new TreeNode<T>(comment);
        return;
    }

    // Find the last sibling comment in the tree
    TreeNode<T>* lastSibling = root;
    while (lastSibling->right != nullptr) 
    {
        lastSibling = lastSibling->right;
    }

    // Insert the new comment as the right sibling of the last sibling
    lastSibling->right = new TreeNode<T>(comment);
}

// Function to search for a comment in the tree
template <class T>
TreeNode<T>* searchComment(TreeNode<T>* root, const std::string& commentId) {
    if (root == nullptr || root->value.getCommentId() == commentId) {
        return root;
    }

    TreeNode<T>* leftResult = searchComment(root->left, commentId);
    if (leftResult != nullptr) {
        return leftResult;
    }

    return searchComment(root->right, commentId);
}

template <class T>
void deleteSubtree(TreeNode<T>* node)
{
    if (node == nullptr) {
        return;
    }

    // Delete the left subtree
    deleteSubtree(node->left);

    // Delete the right subtree
    deleteSubtree(node->right);

    // Delete the current node
    delete node;
}

template <class T>
void replyVideo(TreeNode<T>* root, std::vector<std::string> command)
{
    if (command.size() < 4) {
        //std::cerr << "Invalid command format for reply_to_video." << std::endl;
        return;
    }

    std::string commentId = command[1];
    std::string userName = command[2];
    std::string content = command[3];

    Comment replyComment(commentId, userName, content);

    insertComment(root, replyComment);
}

template <class T>
void replyComment(TreeNode<T>* root, std::vector<std::string> command)
{
    std::string parentCommentId = command[1];
    std::string commentId = command[2];
    std::string userName = command[3];
    std::string content = command[4];

    Comment replyComment(commentId, userName, content, parentCommentId);

    TreeNode<T>* parentComment = searchComment(root, parentCommentId);

    if (parentComment != nullptr) {
        parentComment->value.incrementReply();
        insertComment(root, replyComment);
    } else {
        std::cerr << "Parent comment with ID " << parentCommentId << " not found." << std::endl;
    }
}

template <class T>
void likeComment(TreeNode<T>* root, std::vector<std::string> command)
{
    if (command.size() < 2) {
        //std::cerr << "Invalid command format for like_comment." << std::endl;
        return;
    }

    std::string commentId = command[1];

    TreeNode<T>* likedComment = searchComment(root, commentId);

    if (likedComment != nullptr) {
        likedComment->value.incrementLikes();
    } else {
        //std::cerr << "Comment with ID " << commentId << " not found." << std::endl;
    }
}

template <class T>
void deleteComment(TreeNode<T>*& root, std::vector<std::string> command)
{
    if (command.size() < 2) {
        //std::cerr << "Invalid command format for delete_comment." << std::endl;
        return;
    }

    std::string commentId = command[1];

    TreeNode<T>* commentToDelete = searchComment(root, commentId);

    if (commentToDelete != nullptr) {
        deleteSubtree(commentToDelete);
        //std::cout << "Comment with ID " << commentId << " and its descendants have been deleted." << std::endl;
    } else {
        //std::cerr << "Comment with ID " << commentId << " not found." << std::endl;
    }
}

template <class T>
void displayComment(TreeNode<T>* root, std::ofstream& outputFile, const std::string& id, int depth = 0, bool isFirstTime = true)
{
    if (root == nullptr) {
        return;
    }

    if (depth == 0 && isFirstTime)
    {
    	root = searchComment(root, id);
    }


    // Display the current comment with proper indentation
    outputFile << std::string(depth * 4, ' ') << root->value.getAuthor() << " " << root->value.getPublishedDate() << std::endl;
    outputFile << std::string(depth * 4, ' ') << root->value.getCommentText() << std::endl;
    outputFile << std::string(depth * 4, ' ') << "\U0001F44D " << root->value.getLikeCount() << std::endl;
    if (root->value.getReplyCount() > 0)
    {
    	if (root->value.getReplyCount() > 1)
    		outputFile << std::string(depth * 4, ' ') << root->value.getReplyCount() << " replies" << std::endl;
    	else
			outputFile << std::string(depth * 4, ' ') << root->value.getReplyCount() << " reply" << std::endl;
	}

    // Display the left subtree (children comments) with increased depth
    displayComment(root->left, outputFile, id, depth + 1, false);

    // Display the right subtree (siblings comments) with the same depth as the parent
    if (!isFirstTime)
	    displayComment(root->right, outputFile, id, depth, false);
}

int main(int argc, char const *argv[])
{
	std::string inputFile1 = argv[1];
	std::string inputFile2 = argv[2];
	std::string output = argv[3];


	// JSON parseing
	// assume inputFile is a std::string, containing the file name of the input file.
    std::ifstream jsonFile(inputFile1);
    if (!jsonFile.is_open()) 
    {
        std::cerr << "Failed to open the JSON file." << std::endl;
        exit(1);
    }

    TreeNode<Comment>* root = nullptr;

    std::string line;
    while (std::getline(jsonFile, line)) 
    {
        Comment parsedComment(line);
        insertComment(root, parsedComment);
    }
    // don't need this json file anymore, as the content is read into json_content.
    jsonFile.close();
    line = "";

    // OPS file parseing
    // assume inputFile is a std::string, containing the file name of the input file.
    std::ifstream opsFile(inputFile2);
    if (!opsFile.is_open()) 
    {
        std::cerr << "Failed to open the OPS file." << std::endl;
        exit(1);
    }

    std::string command, parent_id, id, user, comment;
    std::vector<std::vector<std::string>> commands;

    std::ofstream outputFile(output);
    if (!outputFile.is_open())
    {
    	std::cerr << "Failed to open the output file." << std::endl;
        exit(1);
    }

    while (std::getline(opsFile, line)) 
	{
	    std::istringstream iss(line);
	    // Read the command from the line
	    iss >> command;

	    // Process the command based on its value
	    if (command == "reply_to_video")
    	{
			iss >> id;
			iss >> user;
			// skip any whitespace to get to the next non-whitespace character
			iss >> std::ws;
			// now, read the comment
			if (iss.peek() == '"') 
			{
				// if the field starts with a double quote, read it as a whole string
				iss.get();  // consume the opening double quote
				std::getline(iss, comment, '"');  // read until the closing double quote
				std::vector<std::string> inputs = {command, id, user, comment};
				replyVideo(root, inputs);
			}
    	}
    	else if (command == "reply_to_comment")
    	{
    		iss >> parent_id;
			iss >> id;
			iss >> user;
			// skip any whitespace to get to the next non-whitespace character
			iss >> std::ws;
			// now, read the comment
			if (iss.peek() == '"') 
			{
				// if the field starts with a double quote, read it as a whole string
				iss.get();  // consume the opening double quote
				std::getline(iss, comment, '"');  // read until the closing double quote
				//iss >> comment;  // read the quoted field
				//std::cout << comment << "\n";
				std::vector<std::string> inputs = {command, parent_id, id, user, comment};
				replyComment(root, inputs);
			}
    	}
	    else if (command == "like_comment")
	    {
	        // Read other parameters for like_comment command
	        iss >> id;
	        // Process the like_comment command
	        std::vector<std::string> inputs = {command, id};
	        likeComment(root, inputs);
	    }
	    else if (command == "delete_comment")
	    {
	        // Read other parameters for delete_comment command
	        iss >> id;
	        // Process the delete_comment command
	        std::vector<std::string> inputs = {command, id};
	        deleteComment(root, inputs);
	    }
	    else if (command == "display_comment")
	    {
	        // Read other parameters for display_comment command
	        iss >> id;
	        // Process the display_comment command
	        displayComment(root, outputFile, id);
	    }
	}

	// Free the memory allocated for the tree
    deleteSubtree(root);

	return 0;
}