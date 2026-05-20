#pragma once
#include "Scene.h"
#include "Difficulty.h"
#include "Ranking.h"

//============================================================
// GameManager クラス
// ゲーム全体の管理を行う
//
// ・現在のシーン管理
// ・シーン切り替え
// ・難易度の保持
//
// シングルトンパターンで実装し、
// ゲーム内で1つのインスタンスのみ使用する
//============================================================
class GameManager
{
private:
	// 現在実行中のシーン
	Scene* currentScene; 

	// 選択された難易度
	Difficulty selectedDifficulty; 

	Ranking* rankings[3];

	// コンストラクタ（シングルトンのため private）
	GameManager();
public:

	//デストラクタ
	~GameManager();

	// GameManager のインスタンス取得
	static GameManager& GetInstance();

	// 難易度設定
	void SetDifficulty(Difficulty d);
 
    // 現在の難易度取得
	Difficulty GetDifficulty() const;

	// 現在の難易度のランキング取得
	Ranking& GetRanking();

	// プレイヤー名
	TCHAR playerName[16];

	// プレイヤー名を設定
	void SetPlayerName(const TCHAR* name);

	// プレイヤー名を取得
	const TCHAR* GetPlayerName() const;

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// シーン切り替え
	void ChangeScene(Scene*next);
};

