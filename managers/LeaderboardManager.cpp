#include "LeaderboardManager.h"

#include <iostream>

LeaderboardManager::LeaderboardManager() {
    GetRecords();
}

void LeaderboardManager::GetRecords() {
    this->records.clear();
    DWORD dwDisposition;
    int time;
    std::string name;

    RegCreateKeyEx(HKEY_CURRENT_USER, WINMINEREG.c_str(), 0, NULL, 0, KEY_READ, NULL,
                   &H_REG, &dwDisposition);

    time = ReadInt("Time1");
    name = ReadStr("Name1");
    this->records[GAME_EASY] = {name, time, GAME_EASY};

    time = ReadInt("Time2");
    name = ReadStr("Name2");
    this->records[GAME_NORMAL] = {name, time, GAME_NORMAL};

    time = ReadInt("Time3");
    name = ReadStr("Name3");
    this->records[GAME_HARD] = {name, time, GAME_HARD};
}

int LeaderboardManager::ReadInt(std::string pref) {
    int data;
    DWORD size = sizeof(int);
    RegQueryValueEx(this->H_REG, pref.c_str(), 0, 0, (LPBYTE) &data, &size);
    return data;
}

std::string LeaderboardManager::ReadStr(std::string pref) {
    char data[32];
    DWORD size = sizeof(char) * 32;
    RegQueryValueEx(this->H_REG, pref.c_str(), 0, 0, (LPBYTE) &data, &size);
    return std::string(data);
}


void LeaderboardManager::SaveInt(std::string pref, int value)
{
    RegSetValueEx(this->H_REG, pref.c_str(), 0, REG_DWORD, (LPBYTE) &value, sizeof(value));
}

void LeaderboardManager::SaveSrt(std::string pref, std::string value)
{
    RegSetValueEx(this->H_REG, pref.c_str(), 0, REG_SZ, (LPBYTE) value.c_str(), value.size() * sizeof(char));
}

bool LeaderboardManager::CheckResult(struct Record result) {
    int difficulty = result.game_type;
    struct Record record = this->records.at(difficulty);
    if (record.time > result.time) return true;

    return false;
}

void LeaderboardManager::SaveResult(struct Record result) {
    if (!CheckResult(result)) return;

    DWORD dwDisposition;
    RegCreateKeyEx(HKEY_CURRENT_USER, WINMINEREG.c_str(), 0, NULL, 0, KEY_WRITE, NULL, &H_REG, &dwDisposition);

    switch (result.game_type) {
        case GAME_EASY: {
            SaveSrt("Name1", result.name);
            SaveInt("Time1", result.time);
            break;
        }
        case GAME_NORMAL: {
            SaveSrt("Name2", result.name);
            SaveInt("Time2", result.time);
            break;
        }
        case GAME_HARD: {
            SaveSrt("Name3", result.name);
            SaveInt("Time3", result.time);
            break;
        }
    }

    GetRecords();
}




