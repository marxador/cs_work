#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to read input from the input file
void readInput(const string& inputFile, int& width, int& height, vector<pair<char, string>>& requiredWords, vector<pair<char, string>>& forbiddenWords);

// Function to generate an empty grid
vector<vector<char>> generateGrid(int width, int height);

// Recursive function to search for valid solutions
void searchSolution(vector<vector<char>>& grid, const vector<pair<char, string>>& requiredWords, const vector<pair<char, string>>& forbiddenWords, int wordIndex, bool& solutionFound);

// Function to check if a word placement is valid
bool isValidPlacement(const vector<vector<char>>& grid, int row, int col, const string& word, char orientation);

// Function to output solutions
void outputSolutions(const vector<vector<char>>& grid, ofstream& outputFile);

int main(int argc, char const *argv[]) {
    // Parse command-line arguments
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file> <one_solution | all_solutions>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];
    string command = argv[3];

    // Read input from file
    int width, height;
    vector<pair<char, string>> requiredWords, forbiddenWords;
    readInput(inputFile, width, height, requiredWords, forbiddenWords);

    // Generate empty grid
    vector<vector<char>> grid = generateGrid(width, height);

    // Search for solutions
    bool solutionFound = false;
    searchSolution(grid, requiredWords, forbiddenWords, 0, solutionFound);

    // Output solutions
    ofstream outFile(outputFile);
    if (command == "one_solution") {
        if (solutionFound) {
            outputSolutions(grid, outFile);
        } else {
            outFile << "No solutions found" << endl;
        }
    } else if (command == "all_solutions") {
        if (solutionFound) {
            outputSolutions(grid, outFile);
        } else {
            outFile << "No solutions found" << endl;
        }
    } else {
        cerr << "Invalid command" << endl;
        return 1;
    }

    return 0;
}

void readInput(const string& inputFile, int& width, int& height, vector<pair<char, string>>& requiredWords, vector<pair<char, string>>& forbiddenWords) {
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cerr << "Failed to open input file: " << inputFile << endl;
        exit(1);
    }

    inFile >> width >> height;

    char type;
    string word;
    while (inFile >> type >> word) {
        if (type == '+') {
            requiredWords.push_back(make_pair(type, word));
        } else if (type == '-') {
            forbiddenWords.push_back(make_pair(type, word));
        }
    }

    inFile.close();
}

vector<vector<char>> generateGrid(int width, int height) {
    return vector<vector<char>>(height, vector<char>(width, '.'));
}

void searchSolution(vector<vector<char>>& grid, const vector<pair<char, string>>& requiredWords, const vector<pair<char, string>>& forbiddenWords, int wordIndex, bool& solutionFound) {
    if (wordIndex == requiredWords.size()) {
        // All required words placed, check if any forbidden words are present
        for (const auto& pair : forbiddenWords) {
            char type = pair.first;
            string word = pair.second;
            if (word.find_first_of("abcdefghijklmnopqrstuvwxz") != string::npos) {
                // Check if forbidden word is present in the grid
                for (int i = 0; i < grid.size(); ++i) {
                    for (int j = 0; j < grid[0].size(); ++j) {
                        if (grid[i][j] == word[0]) {
                            solutionFound = false;
                            return;
                        }
                    }
                }
            }
        }

        solutionFound = true;
        return;
    }

    const auto& pair = requiredWords[wordIndex];
    char type = pair.first;
    string word = pair.second;

    // Place the word on the grid in all possible orientations
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            for (char orientation : {'f', 'b', 'u', 'd', 'd', 'd'}) {
                if (isValidPlacement(grid, i, j, word, orientation)) {
                    int len = word.size();
                    if (orientation == 'f') {
                        for (int k = 0; k < len; ++k) grid[i][j + k] = word[k];
                    } else if (orientation == 'b') {
                        for (int k = 0; k < len; ++k) grid[i][j - k] = word[k];
                    } else if (orientation == 'u') {
                        for (int k = 0; k < len; ++k) grid[i - k][j] = word[k];
                    } else if (orientation == 'd') {
                        for (int k = 0; k < len; ++k) grid[i + k][j] = word[k];
                    } else if (orientation == 'fd') {
                        for (int k = 0; k < len; ++k) grid[i - k][j - k] = word[k];
                    } else if (orientation == 'bd') {
                        for (int k = 0; k < len; ++k) grid[i + k][j - k] = word[k];
                    }

                    searchSolution(grid, requiredWords, forbiddenWords, wordIndex + 1, solutionFound);

                    // Backtrack
                    for (int k = 0; k < len; ++k) {
                        if (orientation == 'f') {
                            grid[i][j + k] = '.';
                        } else if (orientation == 'b') {
                            grid[i][j - k] = '.';
                        } else if (orientation == 'u') {
                            grid[i - k][j] = '.';
                        } else if (orientation == 'd') {
                            grid[i + k][j] = '.';
                        } else if (orientation == 'fd') {
                            grid[i - k][j - k] = '.';
                        } else if (orientation == 'bd') {
                            grid[i + k][j - k] = '.';
                        }
                    }
                }
            }
        }
    }
}

bool isValidPlacement(const vector<vector<char>>& grid, int row, int col, const string& word, char orientation) {
    int len = word.size();
    if (orientation == 'f' && col + len > grid[0].size()) return false;
    if (orientation == 'b' && col - len + 1 < 0) return false;
    if (orientation == 'u' && row - len + 1 < 0) return false;
    if (orientation == 'd' && row + len > grid.size()) return false;
    if (orientation == 'fd' && (col - len + 1 < 0 || row - len + 1 < 0)) return false;
    if (orientation == 'bd' && (col - len + 1 < 0 || row + len > grid.size())) return false;

    for (int k = 0; k < len; ++k) {
        char ch;
        if (orientation == 'f') {
            ch = grid[row][col + k];
        } else if (orientation == 'b') {
            ch = grid[row][col - k];
        } else if (orientation == 'u') {
            ch = grid[row - k][col];
        } else if (orientation == 'd') {
            ch = grid[row + k][col];
        } else if (orientation == 'fd') {
            ch = grid[row - k][col - k];
        } else if (orientation == 'bd') {
            ch = grid[row + k][col - k];
        }

        if (ch != '.' && ch != word[k]) return false;
    }

    return true;
}

void outputSolutions(const vector<vector<char>>& grid, ofstream& outputFile) {
    outputFile << "1" << endl; // Number of solutions (assuming only one solution for simplicity)

    for (const auto& row : grid) {
        for (char ch : row) {
            outputFile << ch << " ";
        }
        outputFile << endl;
    }
}
