#pragma once
#include <tchar.h>
#include "Difficulty.h"

// スコアデータの管理
struct ScoreData 
{
    TCHAR name[16]; // 名前
	int score;      // スコア
	int rank;       // ランク
};

// ランキング管理クラス
class Ranking
{
private:

	// 定数　保存できるランキングの最大数
	static const int MAX_RANKING = 8;

	// ランキングのデータ配列
	ScoreData ranking[MAX_RANKING];

	// 現在のランキング数
	int rankingCount;

	// 保存・読み込みに使用するファイル名
	char fileName[64];
	
public:
	// ファイルからランキングを読み込む
	Ranking(Difficulty difficulty);

	// 登録数の取得
	int GetCount()const;

	// 指定順位のデータを取得
	ScoreData GetData(int index)const;

	// ランキングに追加
	// name : プレイヤー名
	// score: スコア
	// rank ; ランク
	void Add(const TCHAR* name, int score, int rank);


	// 名前の重複をチェック
	bool IsNameExists(const TCHAR* name);
};

