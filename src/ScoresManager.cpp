#include "ScoresManager.h"
const int NUM_OF_RECORDS = 10;

ScoresManager::ScoresManager()
{
	readRecords();
}

//----------------------------

void ScoresManager::readRecords()
{
	std::string filePath = std::filesystem::current_path().parent_path().parent_path().parent_path().string() + "/resources/" + "records.txt";
	auto file = std::ifstream(filePath);
	if (!file.is_open())
		throw std::runtime_error("failed to open recordes file");

	std::string record;
	int score;
	while (std::getline(file, record))
	{
		score = std::stoi(record.substr(0, record.find(" ")));
		m_records.insert({ score,record });
	}
	file.close();
}

//-----------------------------

void ScoresManager::writeRecords()
{
	std::string filePath = std::filesystem::current_path().parent_path().parent_path().parent_path().string() + "/resources/" + "records.txt";
	auto file = std::ofstream(filePath);
	for (auto& i : m_records)
		file << i.second << std::endl;
}

//-----------------------------

bool ScoresManager::isRecord(int score)
{
	if (m_records.size() < NUM_OF_RECORDS || score >= m_records.rbegin()->first)
		return true;

	return false;
}

//-----------------------------

void ScoresManager::addRecord(sf::RenderWindow& window, const int score, const std::string& playerName)
{

	m_records.insert({ score,std::to_string(score) + "                                            " + playerName });

	if (m_records.size() == NUM_OF_RECORDS + 1)
		m_records.erase(--m_records.end());

	writeRecords();
}

//------------------------

const std::multimap<int, std::string, std::greater<int>>& ScoresManager::getRecords() const
{
	return m_records;
}

