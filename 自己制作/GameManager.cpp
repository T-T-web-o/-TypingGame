#include "GameManager.h"
#include "TitleScene.h"

//============================================================
// コンストラクタ
// ゲーム開始時に最初のシーンを設定する
//============================================================
GameManager::GameManager()
{
	// ゲーム起動時はタイトルシーンから開始
	currentScene = new TitleScene();
	//　安全のため初期化
	selectedDifficulty = EASY;
}

//============================================================
// デストラクタ
// 使用していたシーンを解放する
//============================================================
GameManager::~GameManager()
{
	// 現在のシーンを解放
	delete currentScene;
}

//============================================================
// GameManagerのインスタンス取得（シングルトン）
// 常に同じ GameManager を返す
//============================================================
GameManager& GameManager::GetInstance()
{
	// static にすることでプログラム全体で1つだけ生成される
	static GameManager instance;
	return instance;
}

//============================================================
// 更新処理
// 現在のシーンの Update を呼び出す
//============================================================
void GameManager::Update()
{
	currentScene->Update();
}

//============================================================
// 描画処理
// 現在のシーンの Draw を呼び出す
//============================================================
void GameManager::Draw()
{
	currentScene->Draw();
}

//============================================================
// シーン切り替え処理
// 現在のシーンを削除して新しいシーンに変更する
//============================================================
void GameManager::ChangeScene(Scene* next)
{
	// 以前のシーンを解放
	delete currentScene;

	// 新しいシーンに切り替え
	currentScene = next;
}

//============================================================
// 難易度を設定する
// SelectScene から呼び出される
//============================================================
void GameManager::SetDifficulty(Difficulty d)
{
	selectedDifficulty = d;
}

//============================================================
// 現在設定されている難易度を取得する
//============================================================
Difficulty GameManager::GetDifficulty() const
{
	return selectedDifficulty;
}

Ranking& GameManager::GetRanking()
{
	return ranking[selectedDifficulty];
}


