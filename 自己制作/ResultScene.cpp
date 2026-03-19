#include "ResultScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "Scoreboard.h"
#include "TitleScene.h"

//============================================================
// 描画用定数
//============================================================

const int TITLE_TEXT_X = 200;  // タイトル文字のX座標
const int TITLE_TEXT_Y = 10;   // タイトル文字のY座標

const int SCORE_TEXT_X = 140;  // スコア文字のX座標
const int SCORE_TEXT_Y = 80;  // スコア文字のY座標

const int MISS_TEXT_X = 140;   // ミス数文字のX座標
const int MISS_TEXT_Y = 150;   // ミス数文字のY座標

const int COMBO_TEXT_X = 140;  // コンボ文字のX座標
const int COMBO_TEXT_Y = 220;  // コンボ文字のY座標

const int ACCURACY_TEXT_X = 140; // 正答率文字のX座標
const int ACCURACY_TEXT_Y = 290; // 正答率文字のY座標

const int GUIDE_TEXT_X = 460; // 操作案内文字のX座標
const int GUIDE_TEXT_Y = 430; // 操作案内文字のY座標

const int RANK_TEXT_X = 200;  // ランク文字のX座標
const int RANK_TEXT_Y = 360;  // ランク文字のY座標

const int SCORE_BOARD_X = 480; // スコアボードのX座標
const int SCORE_BOARD_Y = 10;  // スコアボードのY座標

const int TEXT_COLOR = GetColor(230, 230, 230);  //白

//============================================================
// コンストラクタ
// ゲーム終了時のスコア・ミス数・最大コンボを受け取り
// リザルト画面用のデータを初期化する
//============================================================
ResultScene::ResultScene(int score ,int miss ,int maxCombo)
{

	// リザルトデータ保存
	finalScore = score;    //最終スコア
	finalMiss = miss;      //ミス回数
	MaxCombo = maxCombo;   //最大コンボ数

	// 画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	// 背景画像読み込み
	resultImage = LoadGraph(TEXT("Resource/blackboard.png"));

	// スコアによるランク判定
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

//============================================================
// デストラクタ（使用した画像の解放）
//============================================================
ResultScene::~ResultScene()
{
	DeleteGraph(resultImage);
}

//============================================================
// 更新処理
//============================================================
void ResultScene::Update()
{
	// スペースキーでタイトル画面へ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		GameManager::GetInstance().ChangeScene(new TitleScene());
	}
}

//============================================================
// 描画処理
//============================================================
void ResultScene::Draw()
{
	
	//背景画像を画面全体に表示
	DrawExtendGraph(0, 0, screenW, screenH,resultImage, TRUE);

	SetFontSize(50);
	// リザルトタイトル表示
	DrawString(TITLE_TEXT_X, TITLE_TEXT_Y, TEXT("リザルト"), TEXT_COLOR);

	SetFontSize(40);
    // スコア情報表示
	DrawFormatString(SCORE_TEXT_X, SCORE_TEXT_Y, TEXT_COLOR, TEXT("スコア: %d"), finalScore);

    // タイプミス数の表示
	DrawFormatString(MISS_TEXT_X, MISS_TEXT_Y, TEXT_COLOR, TEXT("ミス: %d"), finalMiss);

	// 最大コンボ数表示
	DrawFormatString(COMBO_TEXT_X, COMBO_TEXT_Y, TEXT_COLOR, TEXT("最大コンボ数: %d"), MaxCombo);


	// 正確率
	float accuracy = 0.0f;

	int total = finalScore + finalMiss;

	if (total > 0)
	{
		accuracy = (float)finalScore / total * 100;
	}
	DrawFormatString(ACCURACY_TEXT_X, ACCURACY_TEXT_Y, TEXT_COLOR, TEXT("正確率: %.1f%%"), accuracy);


	SetFontSize(16);
	// 操作案内
	DrawString(GUIDE_TEXT_X, GUIDE_TEXT_Y, TEXT("Spaceでタイトル"), TEXT_COLOR);

	SetFontSize(40);
	// ランク表示
	DrawFormatString(RANK_TEXT_X, RANK_TEXT_Y, rankColor, TEXT("ランク: %s"), rank);

	//スコアボード表示
	scoreboard.Draw(SCORE_BOARD_X, SCORE_BOARD_Y);
}
