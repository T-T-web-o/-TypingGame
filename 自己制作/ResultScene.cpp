#include "ResultScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "TitleScene.h"

// リザルトシーンのコンストラクタ
// ゲーム終了時のスコアとミス数を受け取り、結果として保持する
ResultScene::ResultScene(int score ,int miss ,int maxCombo)
{
	finalScore = score;
	finalMiss = miss;
	MaxCombo = maxCombo;

	//画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//背景画像読み込み
	resultImage = LoadGraph(TEXT("Resource/blackboard.png"));

	// スコアごとのランク付け
	if (miss == 0 && score == 30)
	{
		rank = TEXT("SS");
		rankColor = GetColor(0, 0, 0);       // 黒
	}
	else if (score == 30)
	{
		rank = TEXT("S");
		rankColor = GetColor(0, 0, 255);     // 青
	}
	else if (score >= 25)
	{
		rank = TEXT("A");
		rankColor = GetColor(255, 255, 0);   // 黄
	}
	else if (score >= 20)
	{
		rank = TEXT("B");
		rankColor = GetColor(255, 0, 0);     // 赤
	}
	else if (score >= 15)
	{
		rank = TEXT("C");
		rankColor = GetColor(0, 255, 0);     // 緑
	}
	else
	{
		rank = TEXT("D");
		rankColor = GetColor(0, 255, 255);   // 水色
	}
}

//デストラクタでメモリ上から削除する
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

	SetFontSize(50);
	// リザルトタイトル表示
	DrawString(220, 10, TEXT("リザルト"), GetColor(230, 230, 230));

	SetFontSize(30);
	// スコア表示
	DrawFormatString(200, 100, GetColor(230, 230, 230), TEXT("スコア: %d"), finalScore);

	//ミス数表示
	DrawFormatString(200, 170, GetColor(230, 230, 230),TEXT("ミス: %d"), finalMiss);

	//最大コンボ数表示
	DrawFormatString(200, 240, GetColor(230, 230, 230), TEXT("最大コンボ数: %d"), MaxCombo);

	SetFontSize(16);
	// 操作案内表示
	DrawString(430, 420, TEXT("Spaceでタイトル"), GetColor(230, 230, 230));

	//ランク表示
	SetFontSize(40);
	DrawFormatString(200, 310, rankColor, TEXT("ランク: %s"), rank);
}
