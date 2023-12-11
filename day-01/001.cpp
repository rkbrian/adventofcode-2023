#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * main: instruction at https://adventofcode.com/2023/day/1
 * - makefile: g++ -std=c++11 001.cpp -o 001
 * - run code: ./001
 */
int main()
{
        string filename = "file.txt";
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
                std::cerr << "Error opening file: " << filename << std::endl;
                return 1; // Return an error code
        };
        string line;
        int sum = 0;
        while (getline(inputFile, line))
        {
                int first_digit = 0, last_digit = 0;
                bool get_first_digit = false;
                for (char c : line)
                {
                        if (isdigit(c))
                        {
                                last_digit = c - '0';
                                if (!get_first_digit)
                                {
                                        first_digit = last_digit;
                                        get_first_digit = true;
                                }
                        }
                }
                sum += first_digit * 10 + last_digit;
        }
        cout << "Answer: " << sum << endl;
        inputFile.close();
        return 0;
}
