#include "player.h"

player::player()
{
	money = 500;
	bet = 0; 
	last_bet = 0; 
	maxWin; 
}


void player::saveData()
{
	// SprawdŸ, czy folder player_data istnieje
	if (!std::filesystem::exists(dataFolder))
	{
		// Jeœli nie, utwórz nowy folder
		std::filesystem::create_directory(dataFolder);
	}

	if (nickname.find("/") != std::string::npos)
	{
		nickname.erase(0, 1);
	}

	std::string filename = dataFolder + "/" + nickname + ".txt";
	std::ofstream file(filename);

	if (file.is_open())
	{
		file << "Nickname: " << nickname << std::endl;
		file << "Money: " << money << std::endl;
		file << "Bet: " << bet << std::endl;
		file << "MaxWin: " << maxWin << std::endl;

		file.close();
		std::cout << "Dane gracza zapisane do pliku: " << filename << std::endl;
	}
	else
	{
		std::cerr << "Blad podczas zapisywania danych gracza do pliku." << std::endl;
	}
}

void player::loadData()
{
	if (nickname.find("/") != std::string::npos)
	{
		nickname.erase(0, 1);
	}

	std::string filename = dataFolder + "/" + nickname + ".txt";
	std::ifstream file(filename);

	if (file.is_open())
	{ 
		//(\S+) znaki
		//:\s* dwukropek
		//:\w+ cyfra 

		std::regex pattern(R"((\S+):\s*(\w+))");
		std::smatch matches;

		std::string line;
		while (std::getline(file, line))
		{
			if (std::regex_search(line, matches, pattern))
			{
				std::string key = matches[1];
				std::string value = matches[2];

				if (key == "Nickname")
					nickname = value;
				else if (key == "Money")
					money = std::stol(value);
				else if (key == "Bet")
					bet = std::stol(value);
				else if (key == "MaxWin") {
					std::cout << "Wykonano zaladowanie maxWin\n";
					maxWin = std::stoi(value);
				}
			}
		}

		std::cout << "Wczytano gre\n";
		file.close();
	}
	else
	{
		std::cout << "Nie udalo sie wczytac gry\n";
	}
}

void player::deleteSaveFile()
{
	std::string filename = dataFolder + "/" + nickname + ".txt";
	std::filesystem::path filePath(filename);

	if (std::filesystem::exists(filePath))
	{
		std::filesystem::remove(filePath);
		std::cout << "Zapis gry usuniêty: " << filename << std::endl;
	}
	else
	{
		std::cout << "Nie mo¿na odnaleŸæ zapisu gry: " << filename << std::endl;
	}
}

void player::saveMaxWin()
{
	// SprawdŸ, czy folder player_data istnieje
	if (!std::filesystem::exists(maxFolder))
	{
		// Jeœli nie, utwórz nowy folder
		std::filesystem::create_directory(maxFolder);
	}

	std::time_t t = std::time(nullptr);
	std::tm now;

	// U¿yj localtime_s zamiast localtime
	localtime_s(&now, &t);

	int year = now.tm_year + 1900;
	int month = now.tm_mon + 1;
	int day = now.tm_mday;
	int hour = now.tm_hour; 
	int minute = now.tm_min; 

	std::string filename = maxFolder + "/maxWins_" + nickname + ".txt";
	std::ofstream file(filename);

	if (file.is_open())
	{
		file << "Max Win: " << maxWin;
		file << "  Date: " << year << "/" << month << "/" << day << " Hour: " << hour << ":" << minute;
		file << "  Nickname: " << nickname; 

		file.close();
		std::cout << "Najwyzszy wynik zapisany do pliku: " << filename << std::endl;
	}
	else
	{
		std::cerr << "Blad podczas zapisywania najwyzszej wygranej" << std::endl;
	}
}

long player::loadMaxWin(const std::string& filename, int maxWin)
{
	std::ifstream inputFile(filename);
	std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

	std::regex regexMaxWin(R"(^Max Win: (\d+)$)");
	std::smatch match;

	if (std::regex_search(fileContent, match, regexMaxWin))
	{
		std::string maxWinString = match[1].str();
		long maxWin = std::stol(maxWinString);
		return maxWin;
	}

	return 0;
}