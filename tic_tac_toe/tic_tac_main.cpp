#include <iostream>
#include "tic_tac_toe.cpp"

int main() {
    TicTacToe ticTacToe;
    Score* score = ticTacToe.getScore();
    while ((*score).crossesScore < 3 && (*score).zerosScore < 3)
    {
        ticTacToe.play();
    }
    return 0;
}