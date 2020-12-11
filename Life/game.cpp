#include "game.h"
#include "field.h"
#include <algorithm>
#include <string>
Game::Game()
    : begin_size_x(20),
      begin_size_y(20),
      FieldSize_x_(begin_size_x),
      FieldSize_y_(begin_size_y),
      alive_rules({2, 3}),
      dead_rules({3}),
      ThisField(begin_size_x * begin_size_y, false),
      NextField(begin_size_x * begin_size_y, false) {
}

size_t Game::x() const {
    return FieldSize_x_;
}

size_t Game::y() const {
    return FieldSize_y_;
}

void Game::set_x(size_t x) {
    FieldSize_x_ = x;
}

void Game::set_y(size_t y) {
    FieldSize_y_ = y;
}

std::string Game::alive_for_print() {
    std::string res;
    for (const auto &i : alive_rules) {
        res += std::to_string(i);
    }
    return res;
}
std::string Game::dead_for_print() {
    std::string res;
    for (const auto &i : dead_rules) {
        res += std::to_string(i);
    }
    return res;
}

void Game::change_size(size_t size, bool x) {
    if (x) {
        FieldSize_x_ = size;
        size *= FieldSize_y_;
    } else {
        FieldSize_y_ = size;
        size *= FieldSize_x_;
    }
    ThisField.resize(size, false);
    NextField.resize(size, false);
}
bool Game::change_rules(std::string rules) {
    auto pos1 = rules.find("b");
    auto pos2 = rules.find("s");

    if (pos1 != std::string::npos and pos2 != std::string::npos) {
        alive_rules.clear();
        dead_rules.clear();
        std::string arg1 = rules.substr(pos1 + 1, -pos1 - 1 + pos2);
        std::string arg2 = rules.substr(pos2 + 1, rules.size() - 1 - pos2);
        for (const auto &i : arg1) {
            if (i - '0' > 0 and i - '0' < 10) {
                dead_rules.push_back(i - '0');
            } else {
                dead_rules = {3};
                return false;
            }
        }
        for (const auto &i : arg2) {
            if (i - '0' > 0 and i - '0' < 10) {
                alive_rules.push_back(i - '0');
            } else {
                alive_rules = {2, 3};
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

bool Game::right_neighbor(int n, bool is_alive) {
    if (is_alive) {
        return std::find(alive_rules.begin(), alive_rules.end(), n) != alive_rules.end();
    }
    return std::find(dead_rules.begin(), dead_rules.end(), n) != dead_rules.end();
}

void Game::next_field_generation() {
    for (size_t i = 0; i < FieldSize_y_; ++i) {
        for (size_t j = 0; j < FieldSize_x_; ++j) {
            NextField[i * FieldSize_x_ + j] = will_be_alive(j, i);
        }
    }
}

bool Game::is_alive(size_t x, size_t y) {
    return ThisField[y * FieldSize_x_ + x];
}

void Game::change_state(size_t x, size_t y) {
    ThisField[y * FieldSize_x_ + x] = !ThisField[y * FieldSize_x_ + x];
}
void Game::converse_field(std::vector<bool> f) {
    std::swap(ThisField, f);
}
void Game::converse_field() {
    std::swap(ThisField, NextField);
}
bool Game::field_equal() {
    return (ThisField == NextField);
}

void Game::clear_field() {
    std::fill(ThisField.begin(), ThisField.end(), false);
}

bool Game::will_be_alive(size_t x, size_t y) {
    int alive_nearby = 0;
    if (x > 0 and x < FieldSize_x_ - 1 and y > 0 and y < FieldSize_y_ - 1) {
        alive_nearby += ThisField[x + (y + 1) * FieldSize_x_] + ThisField[x + (y - 1) * FieldSize_x_] +
                        ThisField[(x - 1) + (y + 1) * FieldSize_x_] + ThisField[(x + 1) + (y + 1) * FieldSize_x_] +
                        ThisField[(x - 1) + (y - 1) * FieldSize_x_] + ThisField[(x + 1) + (y - 1) * FieldSize_x_] +
                        ThisField[(x - 1) + y * FieldSize_x_] + ThisField[(x + 1) + y * FieldSize_x_];
    } else if (x > 0 and x < FieldSize_x_ - 1 and y == 0) {
        alive_nearby += ThisField[x + (y + 1) * FieldSize_x_] + ThisField[(x - 1) + (y + 1) * FieldSize_x_] +
                        ThisField[(x + 1) + (y + 1) * FieldSize_x_] + ThisField[(x - 1) + y * FieldSize_x_] +
                        ThisField[(x + 1) + y * FieldSize_x_];
    }
    if (x > 0 and x < FieldSize_x_ - 1 and y == FieldSize_y_ - 1) {
        alive_nearby += ThisField[x + (y - 1) * FieldSize_x_] + ThisField[(x - 1) + (y - 1) * FieldSize_x_] +
                        ThisField[(x + 1) + (y - 1) * FieldSize_x_] + ThisField[(x - 1) + y * FieldSize_x_] +
                        ThisField[(x + 1) + y * FieldSize_x_];
    } else if (x == 0 and y > 0 and y < FieldSize_y_ - 1) {
        alive_nearby += ThisField[x + (y + 1) * FieldSize_x_] + ThisField[x + (y - 1) * FieldSize_x_] +
                        ThisField[(x + 1) + (y + 1) * FieldSize_x_] + ThisField[(x + 1) + (y - 1) * FieldSize_x_] +
                        ThisField[(x + 1) + y * FieldSize_x_];
    } else if (x == 0 and y == 0) {
        alive_nearby += ThisField[x + (y + 1) * FieldSize_x_] + ThisField[(x + 1) + (y + 1) * FieldSize_x_] +
                        ThisField[(x + 1) + y * FieldSize_x_];
    } else if (x == 0 and y == FieldSize_y_ - 1) {
        alive_nearby += ThisField[x + (y - 1) * FieldSize_x_] + ThisField[(x + 1) + (y - 1) * FieldSize_x_] +
                        ThisField[(x + 1) + y * FieldSize_x_];
    } else if (x == FieldSize_x_ - 1 and y > 0 and y < FieldSize_y_ - 1) {
        alive_nearby += ThisField[x + (y + 1) * FieldSize_x_] + ThisField[x + (y - 1) * FieldSize_x_] +
                        ThisField[(x - 1) + (y + 1) * FieldSize_x_] + ThisField[(x - 1) + (y - 1) * FieldSize_x_] +
                        ThisField[(x - 1) + y * FieldSize_x_];
    } else if (x == FieldSize_x_ - 1 and y == 0) {
        alive_nearby += ThisField[x + (y + 1) * FieldSize_x_] + ThisField[(x - 1) + (y + 1) * FieldSize_x_] +
                        ThisField[(x - 1) + y * FieldSize_x_];
    } else if (x == FieldSize_x_ - 1 and y == FieldSize_y_ - 1) {
        alive_nearby += ThisField[x + (y - 1) * FieldSize_x_] + ThisField[(x - 1) + (y - 1) * FieldSize_x_] +
                        ThisField[(x - 1) + y * FieldSize_x_];
    }
    return right_neighbor(alive_nearby, is_alive(x, y));
}
