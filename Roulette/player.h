#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <regex>

class player
{
private:

	std::string dataFolder = "player_data";
	std::string maxFolder = "maxWins";
public:
	std::string nickname;
	long money; 
	long bet;
	int last_bet;
	int last_win;
	int number; 
	int maxWin; 
	int i = 0;

	std::vector<int> betNum;

	void saveData();
	void loadData();
	void deleteSaveFile();
	void saveMaxWin();
	long loadMaxWin(const std::string& filename, int maxWin);

	player();
};

