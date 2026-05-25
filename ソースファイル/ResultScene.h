#pragma once
#include "Scene.h"
#include "Scoreboard.h"
#include "Ranking.h"
#include <tchar.h>

//============================================================
// リザルト画面用シーンクラス
//============================================================
class ResultScene:public Scene
{
private:
	// ゲーム結果データ

	int finalScore; // 最終スコア	
	int finalMiss;  // ミス回数
	int MaxCombo;   // 最大コンボ数
	
	// 画面関連
	
	int resultImage;  // 背景画面 
	int screenW;      // 画面幅
	int screenH;      // 画面高さ

	// ランク文字列
	const TCHAR* rank;
	
	// ランク表示色
	int rankColor;

	// スコアボード描画管理
	Scoreboard scoreboard;

	// ランキング表示
	bool useRanking;

	// 追加されたかどうか
	bool isAdded;

	// 入力管理
	bool prevShift;
	bool nowShift;

public:
	//------------------------------------------------------------
	// コンストラクタ
	// ゲーム終了時のスコア・ミス数・最大コンボを受け取る
	// ランキングを表示するかどうかを受け取る
	//------------------------------------------------------------
	ResultScene(int score ,int miss, int maxCombo,bool useRanking);

	// デストラクタ
	~ResultScene();

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;
};

