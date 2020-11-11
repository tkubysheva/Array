#pragma once
#include "strategy.h"
#include <iostream>
#include <vector>

class STFT : public Strategy {
public:
    char choice(int, std::vector<std::vector<char>> &) override;
    std::string name() override;
};

Strategy *createSTFT();