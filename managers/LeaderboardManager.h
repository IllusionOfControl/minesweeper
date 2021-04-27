#ifndef MINESWEEPER_LEADERBOARDMANAGER_H
#define MINESWEEPER_LEADERBOARDMANAGER_H

#include <windows.h>
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include "../DEFINITIONS.h"

struct Record {
    std::string name;
    int time;
    int game_type;
};

class LeaderboardManager {
private:
    std::string WINMINEREG = "Software\\Microsoft\\winmine";
    HKEY H_REG;

    void SaveInt(std::string pref, int value);

    void SaveSrt(std::string pref, std::string value);

    int ReadInt(std::string pref);
    std::string ReadStr(std::string pref);

    void GetRecords();



public:
    LeaderboardManager();
    ~LeaderboardManager() {}

    bool CheckResult(struct Record result);
    void SaveResult(struct Record result);
    std::map<int, struct Record> records;
};


#endif //MINESWEEPER_LEADERBOARDMANAGER_H
