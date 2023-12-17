#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int max_value(vector<int> v)
{
        int a = v[0], i = 0;
        while (i < v.size())
        {
                if (v[i] > a)
                        a = v[i];
                i++;
        }
        return a;
}

int hand_has_pair(vector<int> v)
{
        int two_counter = 0, i = 0;
        while (i < v.size())
        {
                if (v[i] == 2)
                        two_counter += 1;
                i++;
        }
        return two_counter;
}

/**
 * main: instruction at https://adventofcode.com/2023/day/7
 * - makefile: g++ -std=c++11 007.cpp -o 007
 * - run code: ./007
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
        string line, card_order = "AKQJT98765432";
        vector<int> card_survey; // A hand's A's count, K's count, Q's count...
        map<long, int> ranksys_bids; // My ranking system index & corresponding bids 
        map<char, int> dict; // Dictionary to look for card number's index in card_order, for quick search
        for (int i = 0; i < card_order.length(); i++) // Initialization
        {
                card_survey.push_back(0);
                dict[card_order[i]] = i;
        }
        while (getline(inputFile, line))
        {
                istringstream lineStream(line);
                string token;
                int i = 0;
                long ranksys = 0;
                card_survey.assign(card_order.length(), 0); // Clear content
                while (lineStream >> token)
                {
                        if (i == 0)
                        {
                                for (int j = 0; j < 5; j++)
                                {
                                        card_survey[dict[token[j]]] += 1; // Collect hand's card survey
                                        ranksys = ranksys * 100 + (dict.size() - dict[token[j]]); // Second ranking system: ranked by card's labels in order
                                }
                                if (max_value(card_survey) == 5) // First ranking system: ranked by type strength
                                        ranksys += 70000000000;
                                else if (max_value(card_survey) == 4)
                                        ranksys += 60000000000;
                                else if (max_value(card_survey) == 3 && hand_has_pair(card_survey) == 1)
                                        ranksys += 50000000000;
                                else if (max_value(card_survey) == 3 && hand_has_pair(card_survey) == 0)
                                        ranksys += 40000000000;
                                else if (hand_has_pair(card_survey) == 2)
                                        ranksys += 30000000000;
                                else if (hand_has_pair(card_survey) == 1)
                                        ranksys += 20000000000;
                                else
                                        ranksys += 10000000000;
                        }
                        else if (i == 1)
                        {
                                ranksys_bids[ranksys] = stoi(token);
                        }
                        i++;
                }
        }
        int total_win = 0, counter = 1;
        for (const auto& pair : ranksys_bids) // Sort map by ranking system index ascending
        {
                total_win += counter * pair.second;
                counter++; // The real rank index
        }
        cout << "Answer: " << total_win << endl;
        inputFile.close();
        return 0;
}