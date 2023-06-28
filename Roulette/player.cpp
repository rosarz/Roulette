#include "player.h"

player::player()
{
	money = 500;
	bet = 0; 
	last_bet = 0; 
}


void player::saveData(const std::string& filename)
{
	std::ofstream file(filename, std::ios::binary);

	if (file.is_open())
	{
		size_t nicknameSize = nickname.size();
		file.write(reinterpret_cast<const char*>(&nicknameSize), sizeof(nicknameSize));
		file.write(nickname.data(), nicknameSize);
		file.write(reinterpret_cast<const char*>(&money), sizeof(money));

		file.close();
	}
}

void player::loadData(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);

	if (file.is_open())
	{
		size_t nicknameSize;
		file.read(reinterpret_cast<char*>(&nicknameSize), sizeof(nicknameSize));
		nickname.resize(nicknameSize);
		file.read(nickname.data(), nicknameSize);
		file.read(reinterpret_cast<char*>(&money), sizeof(money));
		std::cout << "Wczytano gre\n";
		file.close();
	}
	else
	{
		std::cout << "Nie udalo sie wczytaæ gry\n";
	}
}

void player::deleteSaveFile(const std::string& filename)
{
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

void player::saveMaxWin(const std::string& filename, int maxWin)
{
	std::ifstream inputFile(filename);
	std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

	std::regex regexMaxWin(R"(^Max Win: (\d+)$)");
	std::smatch match;

	if (std::regex_search(fileContent, match, regexMaxWin))
	{
		// Aktualizuj istniej¹cy zapis najwiêkszej wygranej
		std::string updatedContent = std::regex_replace(fileContent, regexMaxWin, "Max Win: " + std::to_string(maxWin));

		std::ofstream outputFile(filename);
		outputFile << updatedContent;
		std::cout << "Najwiêksza wygrana zosta³a zaktualizowana: " << maxWin << std::endl;
	}
	else
	{
		// Dodaj nowy wpis najwiêkszej wygranej
		std::ofstream outputFile(filename, std::ios::app);
		outputFile << "\nMax Win: " << maxWin;
		std::cout << "Dodano nowy wpis najwiêkszej wygranej: " << maxWin << std::endl;
	}
}

long player::loadMaxWin(const std::string& filename)
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