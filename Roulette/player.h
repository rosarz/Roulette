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


public:
	std::string nickname;
	long money; 
	long bet;
	int last_bet;
	int last_win;
	int number; 

	std::vector<int> betNum;

	void saveData(const std::string& filename);
	void loadData(const std::string& filename);
	void deleteSaveFile(const std::string& filename);
	void saveMaxWin(const std::string& filename, int maxWin);
	long loadMaxWin(const std::string& filename);

	player();
};

