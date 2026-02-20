#include "GameManager.h"
#include "TitleScene.h"


// コンストラクタ
GameManager::GameManager()
{
	// ゲーム起動時はタイトルシーンから開始
	currentScene = new TitleScene();
}

// デストラクタ
GameManager::~GameManager()
{
	// 現在のシーンを解放
	delete currentScene;
}

// シングルトン取得
GameManager& GameManager::GetInstance()
{
	// static にすることで常に同じインスタンスを返す
	static GameManager instance;
	return instance;
}

// 毎フレーム呼ばれる更新処理
void GameManager::Update()
{
	// 現在のシーンの更新処理を呼び出す
	currentScene->Update();
}

// 毎フレーム呼ばれる描画処理
void GameManager::Draw()
{
	// 現在のシーンの描画処理を呼び出す
	currentScene->Draw();
}

// シーン切り替え処理
void GameManager::ChangeScene(Scene* next)
{
	// 以前のシーンを解放
	delete currentScene;

	// 新しいシーンに切り替え
	currentScene = next;
}

// 難易度を設定（SelectScene から呼ばれる）
void GameManager::SetDifficulty(Difficulty d)
{
	selectedDifficulty = d;
}

// 現在選択されている難易度を取得
Difficulty GameManager::GetDifficulty() const
{
	return selectedDifficulty;
}


