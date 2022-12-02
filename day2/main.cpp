#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    std::ifstream data;
    std::string line;

    data.open("input.txt");
    int score = 0;

    if (data.is_open()) {
        while (std::getline(data, line)) {
            char opponent = line.at(0);
            char ending = line.at(2);
            char me = 'Z';

            //A rock > Z scissors
            //B paper > X Rock
            //C scissors > Y paper

            //loose
            if ('X' == ending) {
                if ('A' == opponent) me = 'Z';
                if ('B' == opponent) me = 'X';
                if ('C' == opponent) me = 'Y';
            } 
            //draw
            if ('Y' == ending) {
                if ('A' == opponent) me = 'X';
                if ('B' == opponent) me = 'Y';
                if ('C' == opponent) me = 'Z';
            }
            //win
            if ('Z' == ending) {
                if ('A' == opponent) me = 'Y';
                if ('B' == opponent) me = 'Z';
                if ('C' == opponent) me = 'X';
            }

            //default points
            if ('Y' == me) score += 2; //paper
            if ('X' == me) score += 1; //rock
            if ('Z' == me) score += 3; //scissors

            if ('A' == opponent) {
                if ('Y' == me) score += 6;
                if ('X' == me) score += 3;
            }
            if ('B' == opponent) {
                if ('Z' == me) score += 6;
                if ('Y' == me) score += 3;
            }
            if ('C' == opponent) {
                if ('X' == me) score += 6;
                if ('Z' == me) score += 3;
            }
        }
        data.close();
    }

    std::cout << "solution: " << score << std::endl;

    return 0;
}