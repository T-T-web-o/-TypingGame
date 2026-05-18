#include "Keyboard.h"
#pragma once

//============================================================
// ゲーム開始前のカウントダウンを管理するクラス
//============================================================
class CountDown
{
private:

    // カウントダウン状態
	enum GameState
	{
		WAIT_START,   // ゲーム開始待ち
		COUNTDOWN,    // 3,2,1
		END           //カウントダウン終了
	};

	// 現在の状態
	GameState state;

	//カウントダウン用タイマー
	int countdownTimer;

	// キーボード描画管理
	Keyboard keyboard;

public:
	// コンストラクタ（初期化）
	CountDown();

	// 状態更新
	void Update();

	// 描画処理
	void Draw(int x, int y);

	// カウントダウン終了判定
	bool IsFinished() const;
};

