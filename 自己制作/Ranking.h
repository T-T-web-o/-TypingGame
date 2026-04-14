#pragma once
#include <tchar.h>

struct ScoreData 
{
    TCHAR name[16];
	int score;
	int rank;
};
class Ranking
{
private:

	static const int MAX_RANKING = 5;

	ScoreData ranking[MAX_RANKING];

	int rankingCount;

	char fileName[64];
	
public:
	Ranking(const char* fileName);

	int GetCount()const;
	ScoreData GetData(int index)const;

	void Add(const TCHAR* name, int score, int rank);

	void SaveRanking();

	bool IsNameExists(const TCHAR* name);
};

