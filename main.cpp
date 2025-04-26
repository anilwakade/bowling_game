#include "BowlingGame.h"

#include <cassert>
#include <iostream>

int main()
{
    BowlingGame game;

    std::vector<int> inputRolls = {
        1, 4,   // Frame 1
        4, 5,   // Frame 2
        6, 4,   // Frame 3
        5, 5,   // Frame 4
        10,     // Frame 5
        0, 1,   // Frame 6
        7, 3,   // Frame 7
        6, 4,   // Frame 8
        10,     // Frame 9
        2, 8, 6 // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    assert(total == 133);
    std::cout << "Final Total Score: " << total << std::endl;

    return 0;
}
