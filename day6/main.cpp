#include <fstream>
#include <iostream>
#include <string>
#include <set>
int main(int argc, char** argv)
{
    std::ifstream data;
    std::string line;
    int position = 0;
    data.open("input.txt");
 
    if (data.is_open()) {
  
        while (std::getline(data, line)) {
            std::set<char>markers;
            int count = 0;

            for (int i = 0; i < line.length(); i++) {
                markers.insert(line[i]);
                count += 1;

                if (count == 14 && markers.size() == 14) {
                    position = i+1;
                    break;
                }
                else if (count == 14) {
                    count = 0;
                    i = i - 13;
                    markers.clear();
                }
            }
        }
    }
    data.close();

    std::cout << "solution: " << position << std::endl;
    return 0;
}