#include <iostream>
#include <string>

struct Score {
    unsigned int zerosScore = 0;
    unsigned int crossesScore = 0;
    unsigned int draws = 0;

    std::string toString() {
        std::string result = "GAME SCORE\n";
        result.append("Crosses: " + std::to_string(crossesScore) + "\n");
        result.append("Zeros: " + std::to_string(zerosScore) + "\n");
        result.append("Draws: " + std::to_string(draws) + "\n");
        return result;
    }
};