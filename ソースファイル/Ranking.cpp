#include "Ranking.h"
#include "DxLib.h"
#include "GameManager.h"
#include <cstring> 
#include <fstream>
#include "../sqlite3.h"

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
Ranking::Ranking(Difficulty difficulty)
{
	// ランキング数を初期化
	rankingCount = 0;

	// ranking初期化
	for (int i = 0; i < MAX_RANKING; i++)
	{
		ranking[i].name[0] = '\0';
		ranking[i].score = 0;
		ranking[i].rank = 0;
	}

	sqlite3* db;

	// データベースを開く
	sqlite3_open("ranking.db", &db);

	// ranking テーブルを作成
	const char* sql =
		"CREATE TABLE IF NOT EXISTS ranking ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT,"
		"score INTEGER,"
		"rank INTEGER,"
		"difficulty INTEGER);";

	sqlite3_exec(db, sql, nullptr, nullptr, nullptr);

	ScoreData data;

	// ランキング取得SQL
	const char* selectSQL =
		"SELECT name, score, rank "
		"FROM ranking "
		"WHERE difficulty = ? "
		"ORDER BY score DESC, rank DESC "
		"LIMIT 8;";

	sqlite3_stmt* stmt;

	// SQL文を準備
	int result =
		sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);

	// エラーチェック
	if (result != SQLITE_OK)
	{
		DrawString(100, 100, TEXT("SQL準備エラー"), GetColor(255, 0, 0));

		sqlite3_close(db);

		return;
	}

	// difficultyの値を？にセット
	sqlite3_bind_int(stmt, 1, difficulty);
	
	// データベースから一行ずつ取得
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		// 名前取得
		const unsigned char* name = sqlite3_column_text(stmt, 0);

		// スコア取得
		data.score = sqlite3_column_int(stmt, 1);

		// ランク取得
		data.rank = sqlite3_column_int(stmt, 2);

		// char から　TCHAR に変換
		mbstowcs_s(NULL, data.name, 16, (const char*)name, _TRUNCATE);

		if (rankingCount < MAX_RANKING)
		{
			ranking[rankingCount++] = data;
		}
	}

	// SQL終了
	sqlite3_finalize(stmt);

	// データベースを閉じる
	sqlite3_close(db);
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
		if (score > ranking[rankingCount - 1].score ||
			(score == ranking[rankingCount - 1].score &&
				rank > ranking[rankingCount - 1].rank))
		{
			_tcscpy_s(ranking[rankingCount - 1].name, name);
			ranking[rankingCount - 1].score = score;
			ranking[rankingCount - 1].rank = rank;
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
	// SQLiteへ保存
	sqlite3* db;

	// データベースを開く
	sqlite3_open("ranking.db", &db);

	// 現在の難易度取得
	Difficulty d = GameManager::GetInstance().GetDifficulty();

	// SQL文作成
	char sql[256]; 

	char charName[16];

	// TCHARからcharへ
	wcstombs_s(nullptr, charName, name, _TRUNCATE);

	sprintf_s(
		sql,
		"INSERT INTO ranking(name, score, rank, difficulty) VALUES('%s', %d, %d, %d);",
		charName,
		score,
		rank,
		d
	);

	// SQL実行
	sqlite3_exec(db, sql, nullptr, nullptr, nullptr);

	// データベースを閉じる
	sqlite3_close(db);
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
