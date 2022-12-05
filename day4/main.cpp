#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main(int argc, char** argv)
{
    std::ifstream data;
    std::string line;

    data.open("input.txt");
    int score = 0;
    int score2 = 0;

    if (data.is_open()) {
        std::regex rgx("([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)");

        while (std::getline(data, line)) {

            std::smatch matches;
            if (std::regex_search(line, matches, rgx)) {
                int firstStart = stoi(matches[1]);
                int firstEnd = stoi(matches[2]);
                int secondStart = stoi(matches[3]);
                int secondEnd = stoi(matches[4]);

                if (firstStart <= secondStart && firstEnd >= secondEnd) {
                    score += 1;
                    score2 += 1;
                } else if (secondStart <= firstStart && secondEnd >= firstEnd) {
                    score += 1;
                    score2 += 1;
                } else if ((secondStart >= firstStart && secondStart <= firstEnd) || (secondEnd >= firstStart && secondEnd <= firstEnd)) {
                    score2 += 1;
                }
            }
        }
        data.close();
    }

    std::cout << "solution: " << score << std::endl;
    std::cout << "solution2: " << score2 << std::endl;

    return 0;
}
