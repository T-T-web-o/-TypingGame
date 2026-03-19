#include "DxLib.h"
#include "GameManager.h"
#include "SoundManager.h"
#include <ctime>

//============================================================
// アプリケーションのエントリーポイント
// Windowsアプリの main 関数
//============================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// DxLib初期化
	DxLib_Init();

	// 乱数初期化
	// 毎回違う単語が出るようにする
	srand((unsigned int)time(nullptr));

	// サウンド読み込み
	SoundManager::Load();

    // メインゲームループ
	while (ProcessMessage() == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// 現在のシーンの更新
		GameManager::GetInstance().Update();

		// 現在のシーンの描画
		GameManager::GetInstance().Draw();
		
		// 描画結果を画面に反映
		ScreenFlip();
	}

	// サウンド解放
	SoundManager::Release();

	// DxLibの終了処理
	DxLib_End();

	return 0;
}