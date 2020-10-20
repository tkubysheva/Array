#include "mode.h"

template<typename T>
T convert(char* arg){
    std::stringstream convert(arg);
    T n;
    convert >> n;
    return n;
}
/*
...................Реализованные варианты запуска программы.........................
 \PrisonerDilemma.exe tough-tit-for-tat random poor-trusting-fool all-defect
 \PrisonerDilemma.exe tough-tit-for-tat random poor-trusting-fool all-defect --mode=tournament
 \PrisonerDilemma.exe tough-tit-for-tat random poor-trusting-fool
 \PrisonerDilemma.exe tough-tit-for-tat random poor-trusting-fool --mode=detailed
 \PrisonerDilemma.exe tough-tit-for-tat random poor-trusting-fool --mode=fast
 \PrisonerDilemma.exe tough-tit-for-tat random poor-trusting-fool --mode=fast --step= 2000
...................................Стратегии..........................................
 poor-trusting-fool
 all-defect
 random
 soft-tit-for-tat
 tough-tit-for-tat
 .....................................................................................*/


//невероятно корявая обработка аргументов, нужно бы улучшить с помощью фабрики или map(?)
int main(int argc, char* argv[]) {
    if (argc < 4) return -1;

    if (argc == 4 or (argc >= 5 and convert<std::string>(argv[4]) == "--mode=detailed")) {
        detailed(argv[1], argv[2], argv[3]);
    }else if(convert<std::string>(argv[4]) == "--mode=fast"){
        int steps = 1000;
        if(argc >=7) {
            std::string s = convert<std::string>(argv[5]);
            if (s.find("--step=") != 0)
                throw std::runtime_error("WRONG ARGUMENTS1");
            steps = convert<int>(argv[6]);
        }

        fast(argv[1], argv[2], argv[3], steps);
    }
    else if(convert<std::string>(argv[argc - 1]) == "--mode=tournament" or
             convert<std::string>(argv[argc - 1]).find("--")){
        std::set<std::string> names;
        for(int i = 1; i < argc and convert<std::string>(argv[i]).find("--"); i++){
            names.emplace(argv[i]);
        }
        tournament(names);
    }else throw std::runtime_error("WRONG ARGUMENTS2");

}