#include <iostream>
#include <cstdlib>
#include "score.cpp"

struct TicTacToe
{
private:
    const char EMPTY_FIELD = ' ';
    const char CROSS = 'x';
    const char ZERO = 'o';

    char** table;
    size_t size;
    size_t moves;
    Score score;

    // check main and secondary diagonals
    bool checkDiagonals(char item)
    {
        bool fillMain = true;
        bool fillSecondary = true;
        for (int i = 0; i < size; i++)
            if (table[i][i] != item)
            {
                fillMain = false;
                break;
            }

        for (int i = 0; i < size; i++)
            if (table[i][size - i - 1] != item)
            {
                fillSecondary = false;
                break;
            };
        return fillMain || fillSecondary;
    }

    // check all horizontal and vertical lines
    bool checkLines(char item)
    {
        for (int i = 0; i < size; i++)
        {
            bool inHorizontal = true;
            for (int j = 0; j < size; j++)
                if (table[i][j] != item)
                {
                    inHorizontal = false;
                    break;
                }
            if (inHorizontal)
                return true;
        }
        for (int i = 0; i < size; i++)
        {
            bool inVertical = true;
            for (int j = 0; j < size; j++)
                if (table[j][i] != item)
                {
                    inVertical = false;
                    break;
                }
            if (inVertical)
                return true;
        }
        return false;
    }

    void playerMove()
    {
        int turn = moves % 2; // 1 or 0
        // if player 1 turn, he plays with crosses, else if player 2 turn, he plays with zeros
        char item = turn ? ZERO : CROSS;
        printf("Player %d move %c\n", turn + 1, item);
        // positions from 1 to size * size, for example
        // canonical tic tac toe 3x3 positions from 1 to 9 (3 * 3)
        int minPos = 1, maxPos = size * size;
        while (true)
        {
            printf("Input item position %c:", item);
            int pos;
            std::cin >> pos;
            if (pos <= maxPos && pos >= minPos)
            {
                int i = (pos - 1) / size;
                int j = (pos - 1) % size;

                if (table[i][j] == EMPTY_FIELD)
                {
                    table[i][j] = item;
                    moves++;
                    printf("Player %d set %c on %d\n", turn + 1, item, pos);
                    break;
                }
                else
                {
                    printf("Position is not free, try again\n");
                }
            }
            else
            {
                printf("Invalid position. Position must be between %d and %d\n", minPos, maxPos);
            }
        }
    }

public:
    TicTacToe(size_t size = 3) : size(size)
    {
        if (size < 3)
            throw "minimal board size is 3x3";
        moves = 0;
        table = new char *[size];
        // on start fill table with empty items (spaces)
        for (int i = 0; i < size; i++)
        {
            table[i] = new char[size];
            for (int j = 0; j < size; j++)
                table[i][j] = EMPTY_FIELD;
        }
    }

    ~TicTacToe()
    {
        for (int i = 0; i < size; i++)
            delete[] table[i];
        delete[] table;
    }

    Score *getScore() { return &score; }

    void printTable()
    {
        // Output the top border of the table
        std::cout << "+";
        for (int j = 0; j < size; j++)
            std::cout << "---+";
        std::cout << std::endl;

        // Output the rows of the table
        for (int i = 0; i < size; i++)
        {
            std::cout << "|";
            for (int j = 0; j < size; j++)
                std::cout << " " << table[i][j] << " |";
            std::cout << std::endl;

            // Output the separator line between rows
            std::cout << "+";
            for (int j = 0; j < size; j++)
                std::cout << "---+";
            std::cout << std::endl;
        }
    }

    void play()
    {
        while (moves < size * size)
        {
            playerMove();
            printTable();
            bool crossWin = checkDiagonals(CROSS) || checkLines(CROSS);
            bool zerosWin = checkDiagonals(ZERO) || checkLines(ZERO);
            if (crossWin)
            {
                std::cout << "Player 1 win" << std::endl;
                score.crossesScore++;
                break;
            }
            else if (zerosWin)
            {
                std::cout << "Player 2 win" << std::endl;
                score.zerosScore++;
                break;
            }
            else if (moves == size * size)
            {
                std::cout << "Draw" << std::endl;
                score.draws++;
                break;
            }
            // else continue our game
        }
        std::cout << "Game Over" << std::endl;
        std::cout << score.toString() << std::endl; // print total game score
        clear(); // clear table and moves
    }

    void clear()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                table[i][j] = EMPTY_FIELD;
        moves = 0;
    }
};