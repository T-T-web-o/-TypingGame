#include "Ranking.h"
#include "DxLib.h"
#include <cstring> 
#include <fstream>

int Ranking::GetCount() const
{
	return rankingCount;
}

ScoreData Ranking::GetData(int index) const
{
	return ranking[index];
}

Ranking::Ranking()
{

	rankingCount = 0;

	std::ifstream file("ranking.txt");

	ScoreData data;

	char name[16];
	int score;

	while (file >> name >> score)
	{
		if (strlen(name) >= 16) continue; // 長すぎたら無視

		ScoreData data;
		mbstowcs_s(NULL, data.name, 16, name, _TRUNCATE);
		data.score = score;

		if (rankingCount < MAX_RANKING)
		{
			ranking[rankingCount++] = data;
		}
	}
}

void Ranking::Add(const TCHAR* name, int score)
{
	_tcscpy_s(ranking[rankingCount].name, name);
	ranking[rankingCount].score = score;
	rankingCount++;

	for (int i = 0; i < rankingCount - 1; i++)
	{
		for (int j = i + 1; j < rankingCount; j++)
		{
			if (ranking[i].score < ranking[j].score)
			{
				ScoreData temp = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = temp;
			}
		}
	}

	if (rankingCount > MAX_RANKING)
	{
		rankingCount = MAX_RANKING;
	}
	SaveRanking();
}

void Ranking::SaveRanking()
{
	std::ofstream file("ranking.txt");

	for (int i = 0; i < rankingCount; i++)
	{
		char name[16];
		wcstombs_s(NULL, name, 16, ranking[i].name, _TRUNCATE); 

		file << name << " " << ranking[i].score << std::endl;
	}
}



