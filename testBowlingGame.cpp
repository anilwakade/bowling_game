#include "BowlingGame.h"

#include <gtest/gtest.h>

TEST(BowlingGameTest, NegativeRollThrows)
{
    BowlingGame game;
    EXPECT_THROW(game.roll(-1), std::invalid_argument);
}

TEST(BowlingGameTest, MoreThanTenPinsThrows)
{
    BowlingGame game;
    EXPECT_THROW(game.roll(11), std::invalid_argument);
}

TEST(BowlingGameTest, InvalidFrameScoreOverTen)
{
    BowlingGame game;
    game.roll(7);
    EXPECT_NO_THROW(game.roll(4));
    EXPECT_THROW(game.score(), std::logic_error);
}

TEST(BowlingGameTest, Invalid10thFrame)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        5, 5,   // Frame 1
        0, 0,   // Frame 2
        0, 0,   // Frame 3
        4, 6,   // Frame 4
        0, 0,   // Frame 5
        0, 0,   // Frame 6
        0, 0,   // Frame 7
        0, 0,   // Frame 8
        0, 0,   // Frame 9
        0, 0, 5 // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    EXPECT_THROW(game.score(), std::logic_error);
}

TEST(BowlingGameTest, ScoreOfIncompleteGame)
{
    BowlingGame game;
    game.roll(10);
    game.roll(10);
    game.roll(10);
    EXPECT_NO_THROW(game.score());
}

TEST(BowlingGameTest, BasicCorrectness)
{
    BowlingGame game;

    std::vector<int> inputRolls = {
        1, 1, // Frame 1
        1, 1, // Frame 2
        1, 1, // Frame 3
        1, 1, // Frame 4
        1, 1, // Frame 5
        1, 1, // Frame 6
        1, 1, // Frame 7
        1, 1, // Frame 8
        1, 1, // Frame 9
        1, 1  // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 20);
}

TEST(BowlingGameTest, exampleInProblemStatement)
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
    EXPECT_EQ(total, 133);
}

TEST(BowlingGameTest, AllStrikes)
{
    BowlingGame game;
    std::vector<int> inputRolls(12, 10); // 12 strikes
    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 300);
}

TEST(BowlingGameTest, AllSpares)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        5, 5,   // Frame 1
        5, 5,   // Frame 2
        5, 5,   // Frame 3
        5, 5,   // Frame 4
        5, 5,   // Frame 5
        5, 5,   // Frame 6
        5, 5,   // Frame 7
        5, 5,   // Frame 8
        5, 5,   // Frame 9
        5, 5, 0 // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 145);
}

TEST(BowlingGameTest, GutterGame)
{
    BowlingGame game;
    std::vector<int> inputRolls(20, 0); // 20 rolls with 0 pins

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 0);
}

TEST(BowlingGameTest, SparesInMiddle)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        5, 5, // Frame 1
        0, 0, // Frame 2
        0, 0, // Frame 3
        4, 6, // Frame 4
        0, 0, // Frame 5
        0, 0, // Frame 6
        0, 0, // Frame 7
        0, 0, // Frame 8
        0, 0, // Frame 9
        0, 0  // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 20);
}

TEST(BowlingGameTest, SparesInMiddleAndSpareAt10thFrame)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        5, 5,   // Frame 1
        0, 0,   // Frame 2
        0, 0,   // Frame 3
        4, 6,   // Frame 4
        0, 0,   // Frame 5
        0, 0,   // Frame 6
        0, 0,   // Frame 7
        0, 0,   // Frame 8
        0, 0,   // Frame 9
        3, 7, 9 // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 39);
}

TEST(BowlingGameTest, SparesInMiddleAndStrikeAt10thFrame)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        5, 5,      // Frame 1
        0, 0,      // Frame 2
        0, 0,      // Frame 3
        4, 6,      // Frame 4
        0, 0,      // Frame 5
        0, 0,      // Frame 6
        0, 0,      // Frame 7
        0, 0,      // Frame 8
        0, 0,      // Frame 9
        10, 10, 10 // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 50);
}

TEST(BowlingGameTest, StrikesInMiddleAndStrikeAt10thFrame)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        10,        // Frame 1
        0, 0,      // Frame 2
        3, 5,      // Frame 3
        0, 0,      // Frame 4
        0, 0,      // Frame 5
        0, 0,      // Frame 6
        0, 0,      // Frame 7
        0, 9,      // Frame 8
        10,        // Frame 9
        10, 10, 10 // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 87);
}

TEST(BowlingGameTest, StrikesInMiddleAndSpareAt10thFrame)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        10,     // Frame 1
        0, 0,   // Frame 2
        0, 0,   // Frame 3
        0, 0,   // Frame 4
        10,     // Frame 5
        0, 0,   // Frame 6
        0, 0,   // Frame 7
        0, 0,   // Frame 8
        10,     // Frame 9
        3, 7, 9 // Frame 10
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 59);
}

TEST(BowlingGameTest, StrikesFor10FramesDifferentValueForTwoMoreRolls)
{
    BowlingGame game;
    std::vector<int> inputRolls = {
        10, 10, 10, 10, 10, 10, 10, 10, 10, // First 9 strikes
        10, 2, 8                            // 10th frame with strike and two more rolls
    };

    for (int pins : inputRolls)
    {
        game.roll(pins);
    }

    int total = game.score();
    EXPECT_EQ(total, 282);
}
