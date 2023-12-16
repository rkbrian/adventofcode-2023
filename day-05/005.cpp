#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include <cstdlib>
#include <algorithm>

using namespace std;

/**
 * main: instruction at https://adventofcode.com/2023/day/5
 * - makefile: g++ -std=c++11 005.cpp -o 005
 * - run code: ./005
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
        int action_flag = -1;
        string line, string_short_name[] = {"seed", "soil", "fert", "wate", "ligh", "temp", "humi"};
        vector<long long> num_list;
        while (getline(inputFile, line))
        {
                if (action_flag < 0) // Record number list
                {
                        istringstream lineStream(line);
                        string token;
                        int i = 0;
                        while (lineStream >> token)
                        {
                                if (i > 0)
                                {
                                        num_list.push_back(stoll(token));
                                }
                                i++;
                        }
                        action_flag++;
                }
                else if (line.compare(0, 4, string_short_name[action_flag]) == 0) // Found action indicator
                {
                        action_flag++;
                }
                else if (isdigit(line[0]))
                {
                        istringstream lineStream(line);
                        string token;
                        int i = 0;
                        long long dest = 0, src = 0, size = 0;
                        while (lineStream >> token)
                        {
                                if (i == 0)
                                {
                                        dest = stoll(token);
                                }
                                else if (i == 1)
                                {
                                        src = stoll(token);
                                }
                                else
                                {
                                        size = stoll(token);
                                }
                                i++;
                        }
                        for (int j = 0; j < num_list.size(); j++)
                        {
                                if ((num_list[j] >= src) && (num_list[j] < src + size))
                                        num_list[j] = num_list[j] - src + dest;
                        }
                }
        }
        auto loca = min_element(num_list.begin(), num_list.end());
        int location = *loca;
        cout << "Answer: " << location << endl;
        inputFile.close();
}
