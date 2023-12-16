#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

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
        }
        int action_flag = -1;
        string line, string_short_name[] = {"seed", "soil", "fert", "wate", "ligh", "temp", "humi"};
        vector<long long> num_list, dest, src, size;
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
                        cout << string_short_name[action_flag] << " to next:" << endl;
                        action_flag++;
                }
                else if (isdigit(line[0]))
                {
                        istringstream lineStream(line);
                        string token;
                        int i = 0;
                        while (lineStream >> token)
                        {
                                if (i == 0)
                                {
                                        dest.push_back(stoll(token));
                                }
                                else if (i == 1)
                                {
                                        src.push_back(stoll(token));
                                }
                                else if (i == 2)
                                {
                                        size.push_back(stoll(token));
                                }
                                i++;
                        }
                }
                else if (line.compare(0, 4, "xxxx") == 0)
                {
                        for (int j = 0; j < num_list.size(); j++)
                        {
                                long long changer = 0;
                                for (int k = 0; k < src.size(); k++)
                                {
                                        if ((num_list[j] >= src[k]) && (num_list[j] < src[k] + size[k]))
                                        {
                                                changer = changer - src[k] + dest[k];
                                        }
                                }
                                num_list[j] += changer;
                                cout << num_list[j] << ", ";
                        }
                        cout << endl;
                        dest.clear(), src.clear(), size.clear();
                }
        }
        long long min_value = num_list[0];
        for (long long x : num_list)
        {
                if (x < min_value)
                        min_value = x;
        }
        cout << endl << "Answer: " << min_value << endl;
        inputFile.close();
        return 0;
}
