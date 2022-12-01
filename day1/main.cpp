#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char** argv)
{
    std::ifstream data;
    std::string line;

    data.open("input.txt");

    int max = 0;
    int tmp = 0;
    std::vector<int> top;

    if (data.is_open()) {
        while (std::getline(data, line)) {
            if (!line.empty()) {
                tmp += std::stoi(line);
            } else {
                if (max < tmp) {
                    max = tmp;
                }
                top.emplace_back(tmp);
                tmp = 0;
            }
        }
        data.close();
        std::cout << "Solution: " << max << std::endl;
    }

    std::sort(top.begin(), top.end(), std::greater<int>());
    std::cout << "Solution: " << top[0] << " " << top[1] << " " << top[2] << " total:" << top[0] + top[1] + top[2] << std::endl;

    return 0;
}