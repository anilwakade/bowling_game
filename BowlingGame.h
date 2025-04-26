#ifndef BOWLING_GAME_H
#define BOWLING_GAME_H

#include <vector>

struct Frame
{
    int first = 0;
    int second = 0;
    int third = 0; // Only used for 10th frame
    bool isStrike = false;
    bool isSpare = false;
    bool isTenth = false;
};

class BowlingGame
{
private:
    std::vector<int> rolls_;

public:
    void roll(int pins);
    int score() const;

private:
    std::vector<Frame> buildFrames() const;
};

#endif // BOWLING_GAME_H
