#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

bool isInteger(const string& str)
{
        for (char c : str)
        {
                if (!isdigit(c))
                {
                        return false;
                }
        }
        return true;
}

/**
 * main: instruction at https://adventofcode.com/2023/day/2
 * - makefile: g++ -std=c++11 002.cpp -o 002
 * - run code: ./002
 */
int main()
{
        string filename = "file.txt";
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
                cerr << "Error opening file: " << filename << endl;
                return 1; // Return an error code
        };
        string line;
        string words[] = {"red", "green", "blue"};
        map<string, int> max_dict;
        max_dict[words[0]] = 12, max_dict[words[1]] = 13, max_dict[words[2]] = 14;
        int sum = 0;
        while (getline(inputFile, line))
        {
                size_t found = line.find_first_of(":;,"); // Remove ':' ';' and ','
                while (found != string::npos)
                {
                        line.erase(found, 1); // Erase one character at the found position
                        found = line.find_first_of(":;,", found);
                }
                // Line checkers initialization
                int game_id = 0, impossible_count = 0, index = 0, temp_qty = 0;
                istringstream lineStream(line);
                string token;
                while (lineStream >> token)
                {
                        if (index == 1 && game_id == 0)
                        {
                                game_id = stoi(token), temp_qty = 0; // Get game ID
                        }
                        else if (game_id > 0)
                        {
                                if (isInteger(token))
                                {
                                        temp_qty = stoi(token); // Get quantity of the later color
                                }
                                else
                                {
                                        if (max_dict[token] < temp_qty) // Compare grabbed color quantity with the nominal color total
                                        {
                                                impossible_count++;
                                        }
                                        temp_qty = 0;
                                }
                        }
                        index++;
                }
                if (impossible_count == 0)
                {
                        sum += game_id;
                }
        }
        cout << "Answer: " << sum << endl;
        inputFile.close();
        return 0;
}
