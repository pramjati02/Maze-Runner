#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>  // for remove function

// Function to clean the maze
void cleanMaze(const string& inputFileName, const string& outputFileName) {
	// importing file into code
    ifstream inputFile(inputFileName);

    // Cannot open file
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the input file." << endl;
        return;
    }

    // Outputting a file
    ofstream outputFile(outputFileName);

    // Output file cannot open
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the output file." << endl;
        inputFile.close();
        return;
    }

    // Initializing a string for each line in the file
    string line;

    // Getting each line from the input file
    while (getline(inputFile, line)) {
    	// If the line is empty, continue
        if (line.empty()) {
            continue;
        }

        // Remove square brackets and commas
        line.erase(remove(line.begin(), line.end(), '['), line.end());
        line.erase(remove(line.begin(), line.end(), ']'), line.end());
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        // Write the cleaned line to the output file
        outputFile << line << endl;
    }

    // closing both input and output files
    inputFile.close();
    outputFile.close();

    // printing out a saved text file with cleaned maze
    cout << "Maze cleaned and saved to '" << outputFileName << "'" << endl;
}


// Function to parse the maze data from a text file
vector<vector<int>> parseMazeFromFile(const string& filename) {
    vector<vector<int>> maze; // vector for maze
    ifstream file(filename); // importing the file
    string line; // Initializing a string for each line in the maze

    // Get each line in the text file
    while (getline(file, line)) {
        vector<int> row; // Initializing a row vector
        istringstream iss(line); // converting each line of text into a stream of values
        int value; // Intializing an integer value variable

        // Reading values from from iss variable and appends them to the row vector
        while (iss >> value) {
            row.push_back(value);
        }

        // row vector is then appended to the maze vector
        maze.push_back(row);
    }

    return maze; // maze is returned
}
