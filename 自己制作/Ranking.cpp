#include "Ranking.h"
#include "DxLib.h"
#include <cstring> 


Ranking::Ranking()
{
	rankingCount = 0;
}

void Ranking::Add(const char* name, int score)
{
	strcpy_s(ranking[rankingCount].name, name);
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
}
