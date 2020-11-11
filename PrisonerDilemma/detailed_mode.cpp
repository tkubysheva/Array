#include "detailed_mode.h"
#include "factory.h"
#include <conio.h>
#include <iomanip>

namespace {
    bool gen() {
        Factory<PlayMode, std::string, PlayMode *(*) ()>::getInstance()->addCreator("detailed", createDetailedMode);
        return true;
    }
    static bool d = gen();
}// namespace

PlayMode *createDetailedMode() {
    return new Detailed;
}

void Detailed::play(MATRIX_ &M, std::set<std::string> &names, int N, std::string configs) {
    T = M;
    Initial(names, configs);
    while (!gamer.Exit(steps_counter)) {
        steps_counter++;
        OneGame(true);
    }
}
void Detailed::PrintRes(const std::vector<char> &choice, const std::vector<int> &res) {
    std::cout.setf(std::ios::fixed);
    std::cout << std::setw(20) << std::left << "Strategy's name" << std::setw(8) << "choice" << std::setw(8) << "points" << std::setw(10) << "score" << std::endl;
    for (int i = 0; i < 3; ++i)
        std::cout << std::setw(20) << std::left << str[i]->name() << std::setw(8)
                  << choice[i] << std::setw(8) << res[i] << std::setw(10) << str[i]->score << std::endl;
    std::cout << "Press any key to continue or 'q' to exit:" << std::endl;
}
bool Detailed::Gamer::Exit(const int &count) {
    if (Test) {
        return (Button[count] == 'q');
    }
    if (count == 0)
        return false;
    int c = getch();
    if (c == 'q')
        return true;
    return false;
}
