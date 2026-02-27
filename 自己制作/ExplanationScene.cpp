#include "ExplanationScene.h"
#include "GameManager.h"
#include "SelectScene.h"
#include "DxLib.h"

ExplanationScene::ExplanationScene()
{
	// 画面サイズ取得
		GetDrawScreenSize(&screenW, &screenH);

	//背景画像読み込み
	otherGameImage = LoadGraph(TEXT("Resource/game.png"));
}

ExplanationScene::~ExplanationScene()
{
	DeleteGraph(otherGameImage);
}

void ExplanationScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// ゲーム選択シーンに切り替え
		GameManager::GetInstance().ChangeScene(new SelectScene());
	}
}

void ExplanationScene::Draw()
{
	//背景画像を画面全体に表示
	SetFontSize(20);
	DrawExtendGraph(0, 0, screenW, screenH, otherGameImage, TRUE);

	DrawString(260, 120, TEXT("ゲーム説明"), GetColor(255, 255, 255));



}
