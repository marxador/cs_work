#include <iostream>
#include <vector>
#include <fstream>

// Opens the file for the past string
std::ifstream iFileOpen(std::string fileName)
{
	// creates a std::ifstream object for the playlist and opens the file
    std::ifstream file(fileName);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open one of the input file." << std::endl;
        exit(1);
    }
    	return file; 	
}

// Adds the passed song to the end of the passed playlist
void add(std::string title, std::string fileName, std::vector<std::string> &playlist)
{
	std::ifstream libraryFile = iFileOpen(fileName);
	std::string addLine = " ";

	// Trys to find the song in the library file
	std::string line;
	while ( getline(libraryFile, line) )
	{
		if ( line.find(title, 1) == 1 )
		{
			addLine = line;
			break;
		}
	}
	libraryFile.close();

	// Checks if the song was found and makes changes to the playlist if the song was found
	if (addLine == " ")
	{
		std::cerr << "Couldn't find the song in the library file" << std::endl;
        exit(1);
	}
	playlist.push_back(addLine);
}

// Removes the passed song from the passed playlist
void remove(std::string title, std::vector<std::string> &playlist)
{
	// Finds where the song is in the vector and checks if a song was found
	int position = -1;
	for (int i = 0; i < int(playlist.size()); ++i)
	{
		if ( playlist[i].find(title, 1) == 1 )
		{
			position = i;
			break;
		} 
	}
	if (position == -1)
	{
		std::cerr << "Couldn't find the song in the playlist" << std::endl;
        exit(1);
	}

	playlist.erase(playlist.begin() + position);
}

// Moves the passed song to the passed postition in the passed playlist
void move(std::string title, int positionNew, std::vector<std::string> &playlist)
{
	// Finds where the song is in the vector and checks if a song was found
	int positionOld = -1;
	for (int i = 0; i < int(playlist.size()); ++i)
	{
		if ( playlist[i].find(title, 1) == 1 )
		{
			positionOld = i;
			break;
		} 
	}
	if (positionOld == -1)
	{
		std::cerr << "Couldn't find the song in the playlist" << std::endl;
        exit(1);
	}

	// Moves the song to its new position
	std::string temp = playlist[positionOld];
	playlist.erase(playlist.begin() + positionOld);
	playlist.insert(playlist.begin() + positionNew, temp);
}

int main(int argc, char const *argv[])
{
	if (argc < 6)
	{
		std::cerr << "Not enough arguments to run any command" << std::endl;
        exit(1);
	}
    std::string command = std::string(argv[4]);

    // Gets the last position of the title
    int titleEnd = argc;
    if (command == "move")
    {
    	if (argc < 7)
		{
			std::cerr << "Not enough arguments to run the move command" << std::endl;
        	exit(1);
		}
    	titleEnd = argc - 1;
    }
	
    // Combines the title into one string
    std::string title;
    for (int i = 5; i < titleEnd; ++i)
    {
    	std::string temp = argv[i];

    	// Code from submitty, next three lines
    	size_t quotePos;
        if( (quotePos = temp.find('"')) != std::string::npos )
        {
        	// remove the double quote character at the found position
        	// here number 1 as the second argument means erasing 1 character.
            temp.erase(quotePos, 1);
        }

        // Adds the tmp string to the title string
        if (5 < i && i < titleEnd)
        {
        	title += " " + temp;
        }
        else
        {
        	title += temp;
        }
    }

    // Adds all the songs from the current playlist into a vector
    std::vector<std::string> playlist;
    std::ifstream playlistFile = iFileOpen( std::string(argv[1]) );
    std::string line;
    while ( getline(playlistFile, line) )
    {
    	playlist.push_back(line);
    }
    playlistFile.close();
    
    // Runs specified command
    if (command == "add")
    {
    	std::string libraryName = std::string(argv[2]);
    	add(title, libraryName, playlist);
    }
    else if (command == "remove")
    {
    	remove(title, playlist);
    }
    else if (command == "move")
    {
    	move(title, atoi(argv[argc - 1]) - 1, playlist);
    }
    else
    {
    	std::cerr << "Command not recognized" << std::endl;
        exit(1);
    }
    
    // Prints new playlist into the output file
    std::string outputName = std::string(argv[3]);
    std::ofstream outputFile(outputName);
    if (!outputFile.is_open()) 
    {
        std::cerr << "Failed to open the output file." << std::endl;
        exit(1);
    }

    for (int i = 0; i < int(playlist.size()); ++i)
    {
    	if (i == int(playlist.size() - 1))
    	{
    		outputFile << playlist[i];
    	}
    	else
    	{
    		outputFile << playlist[i] << "\n";
    	}
    }
    outputFile.close();

	return 0;
}