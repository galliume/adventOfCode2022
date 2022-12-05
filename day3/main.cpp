#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

std::vector<char>findCommon(const std::string& line)
{
    std::vector<char>common{};
    std::string firstHalf = line.substr(0, line.length() / 2);
    std::string secondHalf = line.substr(line.length() / 2);
    bool found = false;

    for (int i = 0; i < firstHalf.length(); i++) {
        for (int j = 0; j < secondHalf.length(); j++) {
            if (firstHalf[i] == secondHalf[j] && !found) {
                common.emplace_back(firstHalf[i]);
                found = true;
                break;
            }
        }
    }
    return common;
}

int main(int argc, char** argv)
{
    std::ifstream data;
    std::string line;

    data.open("input.txt");
    std::vector<char> common;
    std::vector<std::string> lines{};
    std::vector<char> part2;
    int count = 0;

    if (data.is_open()) {
        while (std::getline(data, line)) {
            
            std::vector<char>tmp = findCommon(line);
            common.insert(common.begin(), tmp.begin(), tmp.end());
            lines.emplace_back(line);
            count += 1;

             if (count == 3 || count == 6) {
                bool found = false;

                for (int i = 0; i < lines.at(0).length(); i++) {
                    for (int j = 0; j < lines.at(1).length(); j++) {
                        for (int k = 0; k < lines.at(2).length(); k++) {
                            if (lines.at(0)[i] == lines.at(1)[j] && lines.at(0)[i] == lines.at(2)[k] && !found) {
                                part2.emplace_back(lines.at(0)[i]);
                                found = true;
                                break;
                            }
                        }
                    }
                }
                lines.clear();
                if (count == 6) count = 0;
            }
        }
        data.close();
    }

    int score = 0;
    for (auto c : common) {
        std::string s{};
        s.push_back(c);
        if (std::regex_match(s, std::regex("[a-z]"))) {
            score += int(c) - 97 + 1;
        } else if (std::regex_match(s, std::regex("[A-Z]"))) {
            score += int(c) - 65 + 1 + 26;
        }
    }

    int score2 = 0;
    for (auto c : part2) {
        std::string s{};
        s.push_back(c);
        if (std::regex_match(s, std::regex("[a-z]"))) {
            score2 += int(c) - 97 + 1;
        }
        else if (std::regex_match(s, std::regex("[A-Z]"))) {
            score2 += int(c) - 65 + 1 + 26;
        }
    }
    std::cout << "solution: " << score << std::endl;
    std::cout << "solution2: " << score2 << std::endl;

    return 0;
}
