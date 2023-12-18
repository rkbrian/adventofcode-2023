#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

/**
 * main: instruction at https://adventofcode.com/2023/day/8
 * - makefile: g++ -std=c++11 008.cpp -o 008
 * - run code: ./008
 */
int main()
{
        string filename = "file.txt";
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
                cerr << "Error opening file: " << filename << endl;
                return 1; // Return an error code
        }
        string line, start_string = "AAA", end_string = "ZZZ";
        string directions = "LRRLRRLRRRLRLLRRRLLRRRLRLRRRLRLRRLRRRLRRRLRLRRRLRRRLRRLRRRLLLRLRRRLRRRLRRRLRLRLRRLLRRRLRLLRLRRRLRRLLRLRLRRLRRRLRRLLRLRRRLLRRLRRRLRLRRLLRRRLRRLLRRLRRRLRLRRRLRRLRRRLRRRLRRLRRRLRLRRLRRRLRRRLRRLLRLRRLRRLRRRLRLLLRRRLLRRRLRLRRRLRLRRLRRRLLLRLRRRLRLRRLRRRLRRRLRRLRLRLRRRR";
        unordered_map<string, string> parent_leftright; // Hash table structure, constant time unless collisions
        while (getline(inputFile, line)) // Get directions and build hash table
        {
                istringstream lineStream(line);
                string token, key_string, value_string;
                int i = 0;
                while (lineStream >> token)
                {
                        if (i == 0)
                        {
                                key_string = token;
                        }
                        else if (i == 2)
                        {
                                value_string = token;
                        }
                        else if (i == 3)
                        {
                                value_string += token;
                                parent_leftright[key_string] = value_string;
                        }
                        i++;
                }
        }
        long counter = 0, map_size = directions.size();
        while (start_string != end_string)
        {
                int modulo_index = counter % map_size;
                if (directions[modulo_index] == 'L')
                {
                        start_string = parent_leftright[start_string].substr(1, 3);
                }
                else if (directions[modulo_index] == 'R')
                {
                        start_string = parent_leftright[start_string].substr(5, 3);
                }
                counter++;
        }
        cout << "Answer: " << counter << endl;
        inputFile.close();
        return 0;
}