#include "Ranking.h"
#include "DxLib.h"
#include <cstring> 
#include <fstream>

//============================================================
// 登録されているランキング数を取得
//============================================================
int Ranking::GetCount() const
{
	return rankingCount;
}

//============================================================
// 指定した順位のデータを取得
//============================================================
ScoreData Ranking::GetData(int index) const
{
	return ranking[index];
}

//===========================================================
// コンストラクタ
// ファイルからランキングデータを取得
//===========================================================
Ranking::Ranking(const char* fileName)
{
	// ファイル名をコピー
	strcpy_s(this->fileName, fileName);

	// ランキング数を初期化
	rankingCount = 0;

	// ファイルを開く
	std::ifstream file(fileName);

	ScoreData data;

	char name[16];
	int score;
	int rank;

	// 名前・スコア・ランクをファイルから読み込む
	while (file >> name >> score >> rank)
	{
		// 長すぎたら無視
		if (strlen(name) >= 16) continue; 

		// charからTCHARへ変換
		mbstowcs_s(NULL, data.name, 16, name, _TRUNCATE);

		// スコアをセット
		data.score = score;

		// ランクをセット
		data.rank = rank;

		// 最大数を超えない範囲で追加
		if (rankingCount < MAX_RANKING)
		{
			ranking[rankingCount++] = data;
		}
	}
}

//===============================================
// ランキングに新しいスコアを追加
//===============================================
void Ranking::Add(const TCHAR* name, int score, int rank)
{
	// 同じ名前があるかをチェック
	for (int i = 0; i < rankingCount; i++)
	{
		if (_tcscmp(ranking[i].name, name) == 0)
		{
			// スコアを比べ高ければ更新
			if (score > ranking[i].score)
			{
				ranking[i].score = score;
			}
			// 低かったら更新しない
			return;
		}
	}

	// 一旦追加
	if (rankingCount < MAX_RANKING)
	{
		// 名前をコピー
		_tcscpy_s(ranking[rankingCount].name, name);

		// スコアをセット
		ranking[rankingCount].score = score;

		// ランクをセット
		ranking[rankingCount].rank = rank;
		
		// ランキング数を増やす
		rankingCount++;
	}
	else
	{
		// スコアが最下位より高いなら入れ替え
		if (score > ranking[rankingCount - 1].score)
		{
			_tcscpy_s(ranking[rankingCount - 1].name, name);
			ranking[rankingCount - 1].score = score;
		}
		else
		{
			// 低いなら追加しない
			return; 
		}
	}
	
	// スコアが高い順に入れ替える
	for (int i = 0; i < rankingCount - 1; i++)
	{
		for (int j = i + 1; j < rankingCount; j++)
		{
			// 入れ替え
			if (ranking[i].score < ranking[j].score ||
				(ranking[i].score == ranking[j].score
					&& ranking[i].rank < ranking[j].rank))
			{
				ScoreData temp = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = temp;
			}
		}
	}
	// ファイルに保存
	SaveRanking();
}

//============================================================
// ランキングをファイルに保存
//============================================================
void Ranking::SaveRanking()
{
	// ファイルを開く
	std::ofstream file(fileName);

	for (int i = 0; i < rankingCount; i++)
	{
		char name[16];

		// TCHAR を char に変更
		wcstombs_s(NULL, name, 16, ranking[i].name, _TRUNCATE); 

		// 名前・スコアを保存
		file << name << " " << ranking[i].score << " " << ranking[i].rank << std::endl;
	}
}

//===========================================================
// 名前の重複をチェック
//===========================================================
bool Ranking::IsNameExists(const TCHAR* name)
{
	for (int i = 0; i < rankingCount; i++)
	{
		if (_tcscmp(ranking[i].name, name) == 0)
		{
			return true; // 見つかった
		}
	}
	return false; // 見つからない
}



