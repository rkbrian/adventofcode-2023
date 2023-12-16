#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * main: instruction at https://adventofcode.com/2023/day/4
 * - makefile: g++ -std=c++11 004.cpp -o 004
 * - run code: ./004
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
        int sum = 0, start_i = 2;
        string line;
        while (getline(inputFile, line))
        {
                istringstream lineStream(line);
                string token;
                int i = 0, win_points = 0, compare_flag = 0;
                vector<int> win_num;
                while (lineStream >> token)
                {
                        if (i >= start_i && token != "|" && compare_flag == 0) // Make the winnning number list
                                win_num.push_back(stoi(token));
                        else if (token == "|") // Switch to compare mode
                                compare_flag = 1;
                        else if (compare_flag == 1)
                        {
                                int temp = stoi(token), j = 0;
                                while (temp != win_num[j] && j < win_num.size()) // Compare current number with the list
                                        j++;
                                if (j < win_num.size() && win_points == 0) // Found the winning number for the 1st time in the card
                                        win_points += 1;
                                else if (j < win_num.size()) // Found more winning numbers and double the points
                                        win_points *= 2;
                        }
                        i++;
                }
                sum += win_points;
        }
        cout << "Answer: " << sum << endl;
        inputFile.close();
        return 0;
}
