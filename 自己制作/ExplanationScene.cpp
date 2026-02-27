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
	nowEnter = CheckHitKey(KEY_INPUT_RETURN);

	if (nowEnter && !prevEnter)
	{
		// ゲーム選択シーンに切り替え
		GameManager::GetInstance().ChangeScene(new SelectScene());
	}

	prevEnter = nowEnter;
}

void ExplanationScene::Draw()
{
	//背景画像を画面全体に表示
	SetFontSize(20);
	DrawExtendGraph(0, 0, screenW, screenH, otherGameImage, TRUE);

	DrawString(260, 120, TEXT("ゲーム説明"), GetColor(255, 255, 255));

	DrawString(120, 140, TEXT("表示された文字を正しくタイピングしよう！"), GetColor(255, 255, 255));

	DrawString(120, 160, TEXT("[操作説明]"), GetColor(255, 255, 255));
	DrawString(120, 180, TEXT("Enter:ゲームスタート"), GetColor(255, 255, 255));
	DrawString(120, 200, TEXT("Space:選択"), GetColor(255, 255, 255));
	DrawString(120, 220, TEXT("Tab:ゲーム終了"), GetColor(255, 255, 255));

	//ー＞で選択できるようにする
	DrawString(120, 250, TEXT("一文字タイピング練習"), GetColor(255, 255, 255));
	DrawString(120, 270, TEXT("アルファベットタイピング練習"), GetColor(255, 255, 255));
	DrawString(120, 290, TEXT("単語タイピング"), GetColor(255, 255, 255));
}
