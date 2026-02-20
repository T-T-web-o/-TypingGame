#include "DxLib.h"
#include "GameManager.h"
#include <ctime>


// アプリケーションのエントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);
	// DxLibの初期化
	DxLib_Init();

	// 乱数の初期化（毎回違う文字を出すため）
	srand((unsigned int)time(nullptr));

	// メインループ
	// ProcessMessage() が 0 を返している間、ゲームを動かし続ける
	while (ProcessMessage() == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// 現在のシーンの更新処理
		GameManager::GetInstance().Update();

		// 現在のシーンの描画処理
		GameManager::GetInstance().Draw();
		
		// バックバッファと画面を入れ替えて描画を反映
		ScreenFlip();
	}
	// DxLibの終了処理
	DxLib_End();

	return 0;
}