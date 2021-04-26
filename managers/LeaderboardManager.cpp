#include "LeaderboardManager.h"

#include <iostream>

LeaderboardManager::LeaderboardManager() {
    GetRecords();
}

void LeaderboardManager::GetRecords() {
    DWORD dwDisposition;
    int time;
    std::string name;

    RegCreateKeyEx(HKEY_CURRENT_USER, WINMINEREG.c_str(), 0, NULL, 0, KEY_READ, NULL,
                   &H_REG, &dwDisposition);

    time = ReadInt("Time1");
    name = ReadStr("Name1");
    this->records[GAME_EASY] = {name, time};

    time = ReadInt("Time2");
    name = ReadStr("Name2");
    this->records[GAME_NORMAL] = {name, time};

    time = ReadInt("Time3");
    name = ReadStr("Name3");
    this->records[GAME_HARD] = {name, time};
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
    RegSetValueEx(this->H_REG, pref.c_str(), 0, REG_SZ, (LPBYTE) &value, value.size() * sizeof(char));
}




