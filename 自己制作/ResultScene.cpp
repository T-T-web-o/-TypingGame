#include "ResultScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "TitleScene.h"

// リザルトシーンのコンストラクタ
// ゲーム終了時のスコアとミス数を受け取り、結果として保持する
ResultScene::ResultScene(int score ,int miss)
{
	finalScore = score;
	finalMiss = miss;

	//画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//背景画像読み込み
	resultImage = LoadGraph(TEXT("Resource/result.png"));
}

ResultScene::~ResultScene()
{
	DeleteGraph(resultImage);
}

// リザルトシーンの更新処理
void ResultScene::Update()
{
	// スペースキーが押されたらタイトル画面に切り替え
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		GameManager::GetInstance().ChangeScene(new TitleScene());
	}
}

// リザルトシーンの描画処理
void ResultScene::Draw()
{
	//背景画像を画面全体に表示
	DrawExtendGraph(0, 0, screenW, screenH,resultImage, TRUE);

	// リザルトタイトル表示
	DrawString(270, 170, TEXT("リザルト"), GetColor(230, 230, 230));

	// スコア表示
	DrawFormatString(250, 220, GetColor(230, 230, 230), TEXT("スコア:%d"), finalScore);

	//ミス数表示
	DrawFormatString(250, 260, GetColor(230, 230, 230),TEXT("ミス: %d"), finalMiss);

	// 操作案内表示
	DrawString(250, 300, TEXT("Spaceでタイトル"), GetColor(230, 230, 230));
}
