#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>

int main(int argc, char** argv)
{
    std::ifstream data;
    std::string line;
    std::map<int, std::vector<std::string>> map;
    std::map<int, std::vector<int>> moves;
    std::vector<std::string> blocks;
    int size = 0;

    data.open("input.txt");
 
    if (data.is_open()) {
        std::regex rgx("^.+([0-9]+)\\s$");
        std::regex rgxMove("move ([0-9]+) from ([0-9]+) to ([0-9]+)");
        int moveIndex = 0;

        while (std::getline(data, line)) {
            std::smatch matches;
            if (std::regex_search(line, matches, rgxMove)) {
                moves[moveIndex] = { stoi(matches[1]), stoi(matches[2]), stoi(matches[3]) };
                moveIndex += 1;
            } else if (std::regex_search(line, matches, rgx)) {
                size = stoi(matches[1]);
            }  else 
                if  (!line.empty()) blocks.emplace_back(line);
            }
    }
    data.close();

    std::vector<std::string> tmp{};
    tmp.resize(size-1);
    std::fill(tmp.begin(), tmp.end(), "@");
    for (int i = 0; i < size; i++) {
        map[i] = tmp;
    }

    int moveIndex =0;
    for (auto block : blocks) {
        std::regex rgx("(    |[A-Z])");
        std::smatch matches;

        std::string::const_iterator searchStart(block.cbegin());

        int column = 0;
        while (std::regex_search(searchStart, block.cend(), matches, rgx))
        {
            searchStart = matches.suffix().first;
            if ("    " != matches[0]) {
                map[column][moveIndex] = matches[0];
            }
            column += 1;
        }
        moveIndex += 1;
    }

    for (const auto& move : moves) {
        std::vector<std::string> tmpBlocks;

        for (auto i = 0; i < move.second[0]; i++) {
            int from = move.second[1] - 1;
            for (auto& block : map[from]) {
                if (block != "@") {
                    tmpBlocks.insert(tmpBlocks.begin(), block);
                    block = "@";
                    break;
                }
            }
        }
        for (auto tmpBlock : tmpBlocks) {
            int to = move.second[2] - 1;
            bool inserted = false;
            for (int i = map[to].size() - 1; i >= 0; i--) {
                if (map[to][i] == "@") {
                    map[to][i] = tmpBlock;
                    inserted = true;
                    break;
                }
            }

            if (!inserted) {
                map[to].insert(map[to].begin(), tmpBlock);
            }
        }
    }

    for (auto blocks : map) {
        for (auto block : blocks.second) {
            if (block != "@") {
                std::cout << block;
                break;
            }
        }
    }
    return 0;
}