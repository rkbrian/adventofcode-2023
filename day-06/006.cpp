#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * main: instruction at https://adventofcode.com/2023/day/6
 * - makefile: g++ -std=c++11 006.cpp -o 006
 * - run code: ./006
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
        string line;
        int flag = 0, j, multiplies = 1;
        vector<long> time_window, hist_records;
        while (getline(inputFile, line))
        {
                istringstream lineStream(line);
                string token;
                int i = 0;
                while (lineStream >> token)
                {
                        if (i > 0)
                        {
                                if (flag == 0)
                                {
                                        time_window.push_back(stol(token));
                                }
                                else if (flag == 1)
                                {
                                        hist_records.push_back(stol(token));
                                }
                        }
                        i++;
                }
                flag++;
        }
        for (j = 0; j < time_window.size(); j++)
        {
                int win_count = 0;
                long time_push = 0, length;
                while (time_push < time_window[j])
                {
                        length = time_push * (time_window[j] - time_push);
                        if (length > hist_records[j])
                        {
                                win_count++;
                        }
                        time_push++;
                }
                multiplies *= win_count;
        }
        cout << "Answer: " << multiplies << endl;
        inputFile.close();
        return 0;
}