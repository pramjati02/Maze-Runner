
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>  // for remove function

// Function to clean the maze
void cleanMaze(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the input file." << endl;
        return;
    }

    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the output file." << endl;
        inputFile.close();
        return;
    }

    string line;
    while (getline(inputFile, line)) {
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

    inputFile.close();
    outputFile.close();

    cout << "Maze cleaned and saved to '" << outputFileName << "'" << endl;
}

// Function to parse the maze data from a text file
vector<vector<int>> parseMazeFromFile(const string& filename) {
    vector<vector<int>> maze;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<int> row;
        istringstream iss(line);
        int value;

        while (iss >> value) {
            row.push_back(value);
        }

        maze.push_back(row);
    }

    return maze;
}

