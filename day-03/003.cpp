#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
 * main: instruction at https://adventofcode.com/2023/day/3
 * - makefile: g++ -std=c++11 003.cpp -o 003
 * - run code: ./003
 */
int main()
{
        string filename = "file.txt";
        ifstream inputFile(filename), inputFileAgain(filename);
        if (!inputFile.is_open())
        {
                cerr << "Error opening file: " << filename << endl;
                return 1; // Return an error code
        };
        string symbols, line;
        vector<vector<int>> coordinate_table; // Find symbol coordinates
        while (getline(inputFile, symbols))
        {
                vector<int> symbol_row;
                for (int i = 0; i < symbols.length(); i++)
                {
                        if (symbols[i] != '.' && symbols[i] != '\r' && !isdigit(symbols[i]))
                                symbol_row.push_back(i);
                }
                if (symbol_row.empty())
                        coordinate_table.push_back({-5});
                else
                        coordinate_table.push_back(symbol_row);
        }
        int sum = 0, row_id = 0;
        while (getline(inputFileAgain, line))
        {
                for (int i = 0; i < line.length(); i++)
                {
                        if (isdigit(line[i])) // In each line, read consecutive digits to make integer
                        {
                                int temp_num = 0, num_start_i = i - 1;
                                bool is_valid_number = false;
                                while (isdigit(line[i]) && (i < line.length()))
                                        temp_num = temp_num * 10 + (line[i] - '0'), i++;
                                if ((row_id < coordinate_table.size() - 1) && (coordinate_table[row_id + 1][0] != -5)) // Symbol at bottom of the integer
                                {
                                        for (int j = 0; j < coordinate_table[row_id + 1].size(); j++)
                                        {
                                                if (num_start_i <= coordinate_table[row_id + 1][j] && coordinate_table[row_id + 1][j] <= i)
                                                {
                                                        is_valid_number = true;
                                                        break;
                                                }
                                        }
                                }
                                if ((row_id > 0) && (coordinate_table[row_id - 1][0] != -5)) // Symbol at top of the integer
                                {
                                        for (int j = 0; j < coordinate_table[row_id - 1].size(); j++)
                                        {
                                                if (num_start_i <= coordinate_table[row_id - 1][j] && coordinate_table[row_id - 1][j] <= i)
                                                {
                                                        is_valid_number = true;
                                                        break;
                                                }
                                        }
                                }
                                if (coordinate_table[row_id][0] != -5) // Symbol on the left and right sides
                                {
                                        for (int j = 0; j < coordinate_table[row_id].size(); j++)
                                        {
                                                if (coordinate_table[row_id][j] == num_start_i || coordinate_table[row_id][j] == i)
                                                {
                                                        is_valid_number = true;
                                                        break;
                                                }
                                        }
                                }
                                if (is_valid_number)
                                        sum += temp_num;
                        }
                }
                row_id++;
        }
        cout << "Answer: " << sum << endl;
        inputFile.close();
        inputFileAgain.close();
        return 0;
}
