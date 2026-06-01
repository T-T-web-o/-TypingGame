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

	// プレイヤー名を空文字で初期化
	playerName[0] = '\0';

	rankings[0] = new Ranking(EASY);
	rankings[1] = new Ranking(NORMAL); 
	rankings[2] = new Ranking(HARD);
}

//============================================================
// デストラクタ
// 使用していたシーンを解放する
//============================================================
GameManager::~GameManager()
{
	// 現在のシーンを解放
	delete currentScene;

	for (int i = 0; i < 3; i++)
	{
		delete rankings[i];
		rankings[i] = nullptr;
	}
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
// GameManagerがSceneの所有権を持つ
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

//===========================================================
// 現在設定されている難易度のランキングを取得
//===========================================================
Ranking& GameManager::GetRanking()
{
	return *rankings[selectedDifficulty];
}

//==========================================================
// プレイヤー名を設定
//==========================================================
void GameManager::SetPlayerName(const TCHAR* name)
{
	_tcscpy_s(playerName, name);
}

//==========================================================
// プレイヤー名を取得
//==========================================================
const TCHAR* GameManager::GetPlayerName() const
{
	return playerName;
}


//==========================================================
// プレイヤー名の判定
//==========================================================
bool GameManager::IsNameExists(const TCHAR* name)
{
	for (int i = 0; i < 3; i++)
	{
		if (rankings[i]->IsNameExists(name))
		{
			return true;
		}
	}

	return false;
}


