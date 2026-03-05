#include "TitleScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "PracticeTypingScene_1.h"
#include "SelectScene.h"
#include "ExplanationScene.h"

TitleScene::TitleScene()
{
	//画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//タイトル画像読み込み
	titleImage = LoadGraph(TEXT("Resource/Title.png"));
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
}

// タイトル画面の更新処理
// Enterキーが押されたらゲーム選択画面へ遷移する
void TitleScene::Update()
{
	nowEnter = (CheckHitKey(KEY_INPUT_RETURN));
	// Enterキーが押されたか判定
	if (nowEnter && !prevEnter)
	{
		// ゲーム選択シーンに切り替え
		GameManager::GetInstance().ChangeScene(new ExplanationScene());
	}
	prevEnter = nowEnter;
}

// タイトル画面の描画処理
void TitleScene::Draw()
{
	//背景画像を画面全体に表示
	DrawExtendGraph(0, 0,screenW, screenH,titleImage,TRUE);

	SetFontSize(23);
	DrawString(430, 420, TEXT("Enterでスタート"), GetColor(230, 230, 230));
}


