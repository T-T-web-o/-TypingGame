#include "ExplanationScene.h"
#include "GameManager.h"
#include "SelectScene.h"
#include "DxLib.h"

ExplanationScene::ExplanationScene()
{
	// 画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//背景画像読み込み
	ExplanationImage = LoadGraph(TEXT("Resource/blackboard.png"));
}

ExplanationScene::~ExplanationScene()
{
	DeleteGraph(ExplanationImage);
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
	DrawExtendGraph(0, 0, screenW, screenH, ExplanationImage, TRUE);

	// ～～～～～～ ゲームの説明を表示 ～～～～～～
	DrawString(260, 10, TEXT("ゲーム説明"), GetColor(255, 220, 100));

	DrawString(100, 40, TEXT("表示された文字を正しくタイピングしよう！"), GetColor(255, 255, 255));

	// ====== 操作説明 ======
	DrawString(20, 80, TEXT("[操作説明]"), GetColor(100, 200, 255));
	DrawString(20, 110, TEXT("Enter:ゲームスタート"), GetColor(100, 255, 100));
	DrawString(20, 140, TEXT("Space:選択"), GetColor(100, 255, 100));
	DrawString(20, 170, TEXT("Tab:ゲーム終了"), GetColor(100, 255, 100));
	//=======================

	// ======　ゲームモード紹介 ======
	DrawString(300, 80, TEXT("[ゲームモード]"), GetColor(100, 200, 255));
	DrawString(300, 110, TEXT("・一文字タイピング練習"), GetColor(255, 255, 255));
	DrawString(300, 140, TEXT("・アルファベットタイピング練習"), GetColor(255, 255, 255));
	DrawString(300, 170, TEXT("・単語タイピング"), GetColor(255, 255, 255));
	//================================

	// ====== 各モードの説明 ======
	DrawString(20, 220, TEXT("・一文字タイピング練習"), GetColor(255, 220, 100));
	DrawString(40, 250, TEXT("ひらがなをローマ字で入力する基本練習モード"), GetColor(255, 255, 255));

	DrawString(20, 290, TEXT("・アルファベットタイピング練習"), GetColor(255, 220, 100));
	DrawString(40, 320, TEXT("A～Zをタイピングしてキーボード操作に慣れよう"), GetColor(255, 255, 255));

	DrawString(20, 360, TEXT("・単語タイピング"), GetColor(255, 220, 100));
	DrawString(40, 390, TEXT("英単語を素早く入力してスコアとコンボを伸ばそう"), GetColor(255, 255, 255));
	//==============================

	DrawString(460, 430, TEXT("Enterでスタート"), GetColor(230, 230, 230));
	//～～～～～～～～～～～～～～～～～～～～
}
