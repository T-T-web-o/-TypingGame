#pragma once
#include "Scene.h"
#include "Difficulty.h"

// ゲーム全体を管理するクラス
// ・現在のシーン管理
// ・難易度設定の保持
// ・シーン切り替え処理
class GameManager
{
private:
	Scene* currentScene; // 現在実行中のシーン

	Difficulty selectedDifficulty; // 選択された難易度

	// コンストラクタを private にして
	// 外部から new できないようにする（シングルトン）
	GameManager();
public:
	~GameManager();

	// GameManager の唯一のインスタンスを取得する
	static GameManager& GetInstance();

	// 難易度を設定する（SelectScene から呼ばれる）
	void SetDifficulty(Difficulty d);

	// 現在の難易度を取得する
	Difficulty GetDifficulty() const;

	// 現在のシーンの Update を呼び出す
	void Update();

	// 現在のシーンの Draw を呼び出す
	void Draw();

	// シーンを切り替える
	// 引数で渡されたシーンを新しい currentScene にする
	void ChangeScene(Scene*next);
};

