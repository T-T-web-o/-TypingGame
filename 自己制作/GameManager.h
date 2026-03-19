#pragma once
#include "Scene.h"
#include "Difficulty.h"

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

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// シーン切り替え
	void ChangeScene(Scene*next);
};

