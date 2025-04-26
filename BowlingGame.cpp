#include "BowlingGame.h"

#include <iostream>
#include <utility>

namespace
{

    int calculateStrikeBonus(size_t currentFrameIndex, const std::vector<Frame> &frames)
    {
        // No bonus for last frame or not enough frames
        if (currentFrameIndex + 1 >= frames.size())
        {
            return 0;
        }

        const auto &nextFrame = frames[currentFrameIndex + 1];

        // next frame is also a strike
        if (nextFrame.isStrike && currentFrameIndex + 2 < frames.size())
        {
            return nextFrame.first + frames[currentFrameIndex + 2].first;
        }

        return nextFrame.first + nextFrame.second;
    }

    int calculateSpareBonus(size_t currentFrameIndex, const std::vector<Frame> &frames)
    {
        if (currentFrameIndex + 1 < frames.size())
        {
            return frames[currentFrameIndex + 1].first;
        }
        return 0;
    }

    std::pair<Frame, size_t> processTenthFrame(const std::vector<int> &rolls, size_t startIndex)
    {
        size_t i = startIndex;

        if (i + 1 >= rolls.size())
        {
            throw std::logic_error("Incomplete 10th frame: second roll missing.");
        }

        Frame frame;
        frame.isTenth = true;
        frame.first = rolls[i++];
        frame.second = rolls[i++];

        frame.isStrike = (frame.first == 10);
        frame.isSpare = (!frame.isStrike && (frame.first + frame.second == 10));

        if (frame.isStrike || frame.isSpare)
        {
            if (i >= rolls.size())
            {
                throw std::logic_error("10th frame bonus roll missing.");
            }
            frame.third = rolls[i++];
        }

        if (i != rolls.size())
        {
            throw std::logic_error("Unexpected extra rolls after valid 10th frame.");
        }

        return {frame, i};
    }
}

void BowlingGame::roll(int pins)
{
    if (pins < 0 || pins > 10)
    {
        std::cout << "input pins: " << pins << "\n";
        throw std::invalid_argument("Invalid number of pins. Must be between 0 and 10.");
    }

    rolls_.emplace_back(pins);
}

int BowlingGame::score() const
{
    int totalScore = 0;
    const auto frames = buildFrames();

    for (size_t i = 0U; i < frames.size(); ++i)
    {
        const auto &frame = frames[i];

        if (frame.isStrike)
        {
            totalScore += (i == 9)
                              ? 10 + frame.second + frame.third
                              : 10 + calculateStrikeBonus(i, frames);
        }
        else if (frame.isSpare)
        {
            totalScore += (i == 9)
                              ? 10 + frame.third
                              : 10 + calculateSpareBonus(i, frames);
        }
        else
        {
            totalScore += frame.first + frame.second;
        }

        std::cout << "Frame " << i + 1 << ": Current Frame score = "
                  << frame.first + frame.second + (frame.isTenth ? frame.third : 0) << "\n";
        std::cout << "Total Score so far = " << totalScore << "\n";
    }

    return totalScore;
}

std::vector<Frame> BowlingGame::buildFrames() const
{
    std::vector<Frame> frames;
    size_t i = 0;

    while (i < rolls_.size() && frames.size() < 10)
    {
        if (frames.size() == 9)
        {
            auto [tenthFrame, newIndex] = processTenthFrame(rolls_, i);
            frames.emplace_back(std::move(tenthFrame));
            i = newIndex;
            break;
        }

        Frame frame;
        frame.first = rolls_[i++];

        if (frame.first == 10)
        {
            frame.isStrike = true;
            frame.second = 0;
        }
        else
        {
            if (i >= rolls_.size())
            {
                throw std::logic_error("Incomplete frame: second roll missing.");
            }

            frame.second = rolls_[i++];
            const int sum = frame.first + frame.second;

            if (sum > 10)
            {
                throw std::logic_error("Frame cannot have more than 10 pins.");
            }

            frame.isSpare = (sum == 10);
        }

        frames.emplace_back(frame);
    }

    if (frames.size() < 10 && i != rolls_.size())
    {
        throw std::logic_error("Rolls remaining but less than 10 frames built.");
    }

    return frames;
}
