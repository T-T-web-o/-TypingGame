#pragma once
#include "Scene.h"

// リザルト画面用のシーン
class ResultScene:public Scene
{
private:
	//ゲーム終了時の最終スコアを保存する変数
	int finalScore;

	// ゲーム中のミス回数を保存する変数
	int finalMiss;

	//ゲーム終了時の最大コンボ数
	int MaxCombo;

	int resultImage; //背景画像ハンドル
	int screenW;
	int screenH;
public:
	// ゲーム終了時にスコアとミス回数を受け取って初期化する
	ResultScene(int score ,int miss, int maxCombo);

	//デストラクタ
	~ResultScene();

	// 毎フレーム呼ばれる更新処理
	void Update()override;

	// 画面描画処理
	void Draw()override;
};

