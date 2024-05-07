#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

void solvePuzzleRecursive(std::vector<std::vector<char>>& board, const std::vector<std::string>& present, const size_t wordsPlaced, const bool& findAll, std::vector<std::vector<std::vector<char>>>& solutions, const std::vector<std::string>& absent); 

// Function to print the board in ASCII representation
// O(wh)
void printBoard(const std::vector<std::vector<char>>& board, std::ostream& outputFile) 
{
	outputFile << "Board:" << std::endl;
    for (const std::vector<char>& row : board) 
    {
    	outputFile << "  ";
        for (const char& cell : row) 
        {
            outputFile << cell;
        }
        outputFile << std::endl;
    }
}

// Function that looks for words that shouldn't be on the board
// O(8^l)
bool negativeSearch(std::vector<std::vector<char>>& board, const int row, const int col, const int& rowLen, const int& colLen, std::string word, int pos, const int& x, const int& y)
{
    // base case
    if (pos >= (signed)word.length())
        return true;

    // if cell is already visited or on the board
    if (row < 0 || row >= rowLen || col < 0 || col >= colLen)
        return false;

    // if val at curr cell doesn't match with char of word
    if (board[row][col] != word[pos])
        return false;

    // direction coordinates of all four directions
    std::vector<int> dx = {-1, 0, 1, 0, -1, 1, 1, -1};
    std::vector<int> dy = {0, 1, 0, -1, -1, 1, -1, 1};

    if (pos > 0)
    {
        int newRow = row + x;
        int newCol = col + y;
        if(negativeSearch(board, newRow, newCol, rowLen, colLen, word, pos + 1, x, y))
            return true;
    }
    else
    {
        // explore all the eight directions
        for (int k = 0; k < 8; k++)
        {
            int newRow = row + dx[k];
            int newCol = col + dy[k];
            if (negativeSearch(board, newRow, newCol, rowLen, colLen, word, pos + 1, dx[k], dy[k]))
                return true;
        }
    }

    return false;
}

// Helper function to check if negative words exist on the board
// O(whf * 8^l)
bool isNegative(std::vector<std::vector<char>>& board, const int row, const int col, const std::vector<std::string>& absent) 
{
    int rowLen = board.size();
    int colLen = board[0].size();

    // call negativeSearch for every cell
    for (const std::string& word : absent)
    {
        if (negativeSearch(board, row, col, rowLen, colLen, word, 0, 0, 0))
           return true;
    }

    return false;
}

// Helper function to confirm there are no negative words one last time
// O(whfl * 8^l)
bool isNegativeFinal(std::vector<std::vector<char>>& board, const std::vector<std::string>& absent)
{
    int rowLen = board.size();
    int colLen = board[0].size();

    // call negativeSearch for every cell
    for (int row = 0; row < rowLen; ++row)
    {
        for (int col = 0; col < colLen; ++col)
        {
            for (const std::string& word : absent)
            {
                if (negativeSearch(board, row, col, rowLen, colLen, word, 0, 0, 0))
                   return true;
            }
        }
    }

    return false;
}

// Function to place the word on the grid in the specified orientation
// Also checks to see if a placed letter makes a negative word
// O(lwhf * 8^l)
bool placeWord(std::vector<std::vector<char>>& board, const int row, const int col, const std::string& word, const std::string& orientation, const std::vector<std::string>& absent) 
{
    int len = word.size();

    if (orientation == "forward") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row][col + i] = word[i];
            if (isNegative(board, row, (col + i), absent))
                return false;
        }
        return true;
    } 
    else if (orientation == "backward") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row][col - i] = word[i];
            if (isNegative(board, row, (col - i), absent))
                return false;
        }
        return true;
    } 
    else if (orientation == "up") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row - i][col] = word[i];
            if (isNegative(board, (row - i), col, absent))
                return false;
        }
        return true;
    } 
    else if (orientation == "down") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row + i][col] = word[i];
            if (isNegative(board, (row + i), col, absent))
                return false;
        }
        return true;
    }
    else if (orientation == "forwardDiagonal") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row - i][col - i] = word[i];
            if (isNegative(board, (row - i), (col - i), absent))
                return false;
        }
        return true;
    } 
    else if (orientation == "forwardDiagonalReverse") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row + i][col + i] = word[i];
            if (isNegative(board, (row + i), (col + i), absent))
                return false;
        }
        return true;
    }
    else if (orientation == "backDiagonal") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row + i][col - i] = word[i];
            if (isNegative(board, (row + i), (col - i), absent))
                return false;
        }
        return true;
    }
    else if (orientation == "backDiagonalReverse") 
    {
        for (int i = 0; i < len; ++i) 
        {
            board[row - i][col + i] = word[i];
            if (isNegative(board, (row - i), (col + i), absent))
                return false;
        }
        return true;
    }
    else
        return false;
}

// Function to check if placing the word in the specified orientation is valid
// Also places the word to check and see if negative words are created in placement
// O(l^2 * whf * 8^l)
bool isValidPlacement(std::vector<std::vector<char>>& board, const int row, const int col, const std::string& word, const std::string& orientation, const std::vector<std::string>& absent) 
{
    int len = (signed)word.size();
    int rowLen = (signed)board.size();
    int colLen = (signed)board[0].size();

    // Check if the word fits within the board boundaries
    if (orientation == "forward" && col + len > colLen)
        return false;
    if (orientation == "backward" && col - len + 1 < 0)
        return false;
    if (orientation == "up" && row - len + 1 < 0)
        return false;
    if (orientation == "down" && row + len > rowLen)
        return false;
    if (orientation == "forwardDiagonal" && (row - len + 1 < 0 || col - len + 1 < 0))
        return false;
    if (orientation == "forwardDiagonalReverse" && (row + len > rowLen || col + len > colLen))
        return false;
    if (orientation == "backDiagonal" && (row + len > rowLen || col - len + 1 < 0))
        return false;
    if (orientation == "backDiagonalReverse" && (row - len + 1 < 0 || col + len > colLen))
        return false;

    // Check for conflicts with existing characters
    for (int i = 0; i < len; ++i) 
    {
        char currentCell;

        if (orientation == "forward")
            currentCell = board[row][col + i];
        else if (orientation == "backward")
            currentCell = board[row][col - i];
        else if (orientation == "up")
            currentCell = board[row - i][col];
        else if (orientation == "down")
            currentCell = board[row + i][col];
        else if (orientation == "forwardDiagonal")
            currentCell = board[row - i][col - i];
        else if (orientation == "forwardDiagonalReverse")
            currentCell = board[row + i][col + i];
        else if (orientation == "backDiagonal")
            currentCell = board[row + i][col - i];
        else if (orientation == "backDiagonalReverse")
            currentCell = board[row - i][col + i];
        else
            return false;  // Invalid orientation

        // Check for conflicts with existing characters
        if (currentCell != '.' && currentCell != word[i])
            return false;
    }

    // Place the word on the board
    return placeWord(board, row, col, word, orientation, absent);
}

// Function to do final checks on if the board is solved
// O(whfl * 8^l)
bool isBoardSolved(std::vector<std::vector<char>>& board, const std::vector<std::string>& present, const size_t wordsPlaced, const std::vector<std::string>& absent, std::vector<std::vector<std::vector<char>>>& solutions)
{
    if (wordsPlaced == present.size())
    {
        return !isNegativeFinal(board, absent);
    }
    else
        return false; // Didn't get all the words in yet
}

// Recursive function to find solutions
// O(8^(rwh) * l^2 * whf * 8^l)
void solvePuzzleRecursive(std::vector<std::vector<char>>& board, const std::vector<std::string>& present, const size_t wordsPlaced, const bool& findAll, std::vector<std::vector<std::vector<char>>>& solutions, const std::vector<std::string>& absent) 
{
    // Base case: All words have been successfully placed
    if (isBoardSolved(board, present, wordsPlaced, absent, solutions)) 
    {
        bool noHoles = true;
        for (size_t row = 0; row < board.size(); ++row) 
        {
            for (size_t col = 0; col < board[0].size(); ++col) 
            {
                if (board[row][col] == '.')
                {
                    noHoles = false;
                    std::string letters = "abcdefghijklmnopqrstuvwxyz";
                    for (int i = 0; i < 26; ++i)
                    {
                        std::string letter(1, letters[i]);
                        if (placeWord(board, row, col, letter, "forward", absent))
                            solvePuzzleRecursive(board, present, wordsPlaced, findAll, solutions, absent);
                    }
                }
            }
        }


        // Store the solution in the solutions vector
        if (noHoles && std::find(solutions.begin(), solutions.end(), board) == solutions.end())
            solutions.push_back(board);

        // If 'one_solution' is specified and a solution is found, stop the search
        if (!findAll) 
            return;
    }

    // Iterate over the positions on the board
    for (size_t row = 0; row < board.size(); ++row) 
    {
        for (size_t col = 0; col < board[0].size(); ++col) 
        {
            for (const std::string orientation : {"forward", "backward", "up", "down", "forwardDiagonal", "forwardDiagonalReverse", "backDiagonal", "backDiagonalReverse"}) 
            {
                std::vector<std::vector<char>> tempBoard = board;
                
                // Check if placing the word in this position and orientation is valid
                if (isValidPlacement(board, row, col, present[wordsPlaced], orientation, absent)) 
                {
                    // Recur to place the next word
                    solvePuzzleRecursive(board, present, wordsPlaced + 1, findAll, solutions, absent);
                }

                // Backtrack: Remove the word if the recursion did not lead to a solution
                board = tempBoard;
            }
        }
    }
}

// Wrapper function for solvePuzzleRecursive
std::vector<std::vector<std::vector<char>>> solvePuzzle(const std::vector<std::string>& present, const int& width, const int& height, const bool& findAll, const std::vector<std::string>& absent) 
{
    // Initialize the board
    std::vector<std::vector<char>> board(height, std::vector<char>(width, '.'));

    // Vector to store solutions
    std::vector<std::vector<std::vector<char>>> solutions;

    // Call the recursive function starting from the first word
    solvePuzzleRecursive(board, present, 0, findAll, solutions, absent);

    return solutions;
}
// O(8^(r) * l^2 * whfs * 8^l)
int main(int argc, char const *argv[])
{
	// Opens input file
	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open()){
        std::cerr << "Failed to open " << argv[1] << std::endl;
        return 1;
    }

    // Opens output file
    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()){
        std::cerr << "Failed to open " << argv[2] << std::endl;
        return 1;
    }

    // Initialize grid and read input file
    int height = 2, width = 3;
    std::vector<std::string> present, absent;

    std::string line;
    while(getline(inputFile, line))
    {
    	if (line[0] == '+')
    	{
    		std::string word = line.substr(2);
            
            // Remove spaces from the word
            word.erase(std::remove(word.begin(), word.end(), ' '), word.end());

    		present.push_back(word);
    	}
    	else if (line[0] == '-')
    	{
    		std::string word = line.substr(2);
            
            // Remove spaces from the word
            word.erase(std::remove(word.begin(), word.end(), ' '), word.end());

    		absent.push_back(word);
            reverse(word.begin(), word.end());
            absent.push_back(word);
    	}
    	else if (line.find(' ') != std::string::npos) 
        {
            // Parse width and height
            auto pos = line.find(' ');
            width = std::stoi(line.substr(0, pos));
            height = std::stoi(line.substr(pos + 1));
        }
    }

    // Runs specified command
    std::string command = argv[3];
    if (command == "one_solution")
    {
    	// Call the solvePuzzle function to find all solutions
    	std::vector<std::vector<std::vector<char>>> allSolutions = solvePuzzle(present, width, height, false, absent);
    	if(!allSolutions.empty())
	        printBoard(allSolutions[0], outputFile);
    	else
    		outputFile << "No solutions found" << std::endl;
    }
    else if (command == "all_solutions")
    {
    	// Call the solvePuzzle function to find all solutions
    	std::vector<std::vector<std::vector<char>>> allSolutions = solvePuzzle(present, width, height, true, absent);
    	if(!allSolutions.empty())
    	{
    		outputFile << allSolutions.size() << " solution(s)" << std::endl;

    		// Print each solution
	        for (const std::vector<std::vector<char>>& solution : allSolutions) 
	        {
	            printBoard(solution, outputFile);
	        }
    	}
    	else
    		outputFile << "No solutions found" << std::endl;
    }
	return 0;
}