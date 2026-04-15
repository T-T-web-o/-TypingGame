#include "ResultScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "Scoreboard.h"
#include "TitleScene.h"
#include "KeyTable.h"
#include "Ranking.h"

//============================================================
// 描画用定数
//============================================================


// ===== レイアウト =====
const int CENTER_X = 300;

const int TITLE_TEXT_X = CENTER_X;  // タイトル文字のX座標
const int TITLE_TEXT_Y = 30;        // タイトル文字のY座標

const int INFO_START_Y = 100;       // 
const int LINE_SPACE = 55;          // 

const int RANK_TEXT_Y = 320;

// ランキング（右側）
const int RANKING_X = 650;
const int RANKING_Y = 120;

// 名前入力
const int NAME_X = 200;
const int NAME_Y = 380;

const int TEXT_COLOR = GetColor(230, 230, 230);  //白


//============================================================
// コンストラクタ
// ゲーム終了時のスコア・ミス数・最大コンボを受け取り
// リザルト画面用のデータを初期化する
//============================================================
ResultScene::ResultScene(int score ,int miss ,int maxCombo,bool useRanking)
{

	// リザルトデータ保存
	finalScore = score;    //最終スコア
	finalMiss = miss;      //ミス回数
	MaxCombo = maxCombo;   //最大コンボ数
	this->useRanking = useRanking; //ランキング表示

	isAdded = false;

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
	 // 1回だけランキング登録
	if (!isAdded && useRanking)
	{
		const TCHAR* name = GameManager::GetInstance().GetPlayerName();

		int rankValue = 0;

		if (_tcscmp(rank, TEXT("SS")) == 0)rankValue = 5;
		else if (_tcscmp(rank, TEXT("S")) == 0)rankValue = 4;
		else if (_tcscmp(rank, TEXT("A")) == 0)rankValue = 3;
		else if (_tcscmp(rank, TEXT("B")) == 0)rankValue = 2;
		else if (_tcscmp(rank, TEXT("C")) == 0)rankValue = 1;
		else rankValue = 0;

		GameManager::GetInstance().GetRanking().Add(name, finalScore, rankValue);

		isAdded = true;
	}

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
	int centerX = screenW / 2;

	// 左側（リザルト）
	int leftX = screenW / 4 - 110;

	// 右側（ランキング）
	int rightX = screenW * 3 / 4 - 110;

	//背景画像を画面全体に表示
	DrawExtendGraph(0, 0, screenW, screenH,resultImage, TRUE);

	SetFontSize(40);
	// リザルトタイトル表示
	DrawFormatString(leftX, TITLE_TEXT_Y, TEXT_COLOR, TEXT("リザルト"));

	SetFontSize(35);
    // スコア情報表示
	DrawFormatString(leftX, INFO_START_Y + LINE_SPACE * 0, TEXT_COLOR, TEXT("スコア: %d"), finalScore);

    // タイプミス数の表示
	DrawFormatString(leftX, INFO_START_Y + LINE_SPACE * 1, TEXT_COLOR, TEXT("ミス: %d"), finalMiss);

	// 最大コンボ数表示
	DrawFormatString(leftX, INFO_START_Y + LINE_SPACE * 2, TEXT_COLOR, TEXT("最大コンボ: %d"), MaxCombo);

	// 正確率
	float accuracy = 0.0f;

	int total = finalScore + finalMiss;

	if (total > 0)
	{
		accuracy = (float)finalScore / total * 100;
	}
	DrawFormatString(leftX, INFO_START_Y + LINE_SPACE * 3, TEXT_COLOR, TEXT("正確率: %.1f%%"), accuracy);

	// ランク表示
	DrawFormatString(leftX, RANK_TEXT_Y, rankColor, TEXT("ランク: %s"), rank);

	//ランキング表示
	if (useRanking)
	{
		SetFontSize(40);
		
		DrawFormatString(rightX, 30, TEXT_COLOR, TEXT("ランキング"));

		SetFontSize(30);

		// 順位・名前・ポイント・ランク表示
		Ranking& ranking = GameManager::GetInstance().GetRanking();
		for (int i = 0; i < ranking.GetCount(); i++)
		{
			ScoreData data = ranking.GetData(i);

			const TCHAR* rankText;

			switch (data.rank)
			{
			case 5: rankText = TEXT("SS"); break;
			case 4: rankText = TEXT("S"); break;
			case 3: rankText = TEXT("A"); break;
			case 2: rankText = TEXT("B"); break;
			case 1: rankText = TEXT("C"); break;
			default: rankText = TEXT("D"); break;
			}

			DrawFormatString(rightX+10, 100 + i * 40, TEXT_COLOR, TEXT("%d位 %s %d %s"), i + 1, data.name, data.score, rankText);
		}
	}
	
	// 練習モードの時はランキングを表示しない。
	SetFontSize(20);
	if (!useRanking)
	{
		DrawString(270, 60, TEXT("※練習モードのためランキングなし"), TEXT_COLOR);
	}

	// 操作案内
	DrawString(screenW - 220, screenH - 60, TEXT("Spaceでタイトル"), TEXT_COLOR);
}
