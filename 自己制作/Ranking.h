#pragma once

static const int MAX_RANKING = 10;

struct ScoreData 
{
	char name[16];
	int score;
};
class Ranking
{
private:
	ScoreData ranking[MAX_RANKING];

	int rankingCount;
public:
	Ranking();

	void Add(const char* name,int score);
};

