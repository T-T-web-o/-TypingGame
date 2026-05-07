#include "CountDown.h"
#include "SoundManager.h"
#include "DxLib.h"

//============================================================
// 描画用定数
//============================================================

const int TITLE_TEXT_X = 200;   // タイトル座標X
const int TITLE_TEXT_Y = 10;    // タイトル座標Y

const int START_TEXT_X = 200;   // 操作案内座標X
const int START_TEXT_Y = 240;   // 操作案内座標Y

const int COUNTDOWN_TEXT_X = 300;   // カウントダウン座標X
const int COUNTDOWN_TEXT_Y = 200;   // カウントダウン座標Y

const int COLOR_TEXT = GetColor(230, 230, 230);  //白

//============================================================
// コンストラクタ（カウントダウンの初期化）
//============================================================
CountDown::CountDown()
{
	state = WAIT_START;   //　ゲーム開始前の状態
	countdownTimer = 180; //  カウントダウン用タイマー（３秒：60fps×3）
}

//============================================================
// カウントダウン状態の更新処理
//============================================================
void CountDown::Update()
{
	// ゲーム開始待ち状態
	if (state == WAIT_START)
	{
		//ENTERキーが押されたらカウントダウン開始
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			//効果音再生
			PlaySoundMem(SoundManager::titleSE, DX_PLAYTYPE_BACK);

			//カウントダウン状態へ
			state = COUNTDOWN;
		}
		return;
	}

	// カウントダウン処理
	if (state == COUNTDOWN)
	{
		//タイマーを減らす
		countdownTimer--;

		//タイマーが0になったらゲーム開始
		if (countdownTimer == 0)
		{
			state = END;
		}
		return;
	}
}

//============================================================
// カウントダウンの描画処理
//============================================================
void CountDown::Draw(int x, int y)
{
	// ゲーム開始前の表示
	if (state == WAIT_START)
	{
		SetFontSize(30);

		DrawString(TITLE_TEXT_X, TITLE_TEXT_Y, TEXT("タイピングゲーム"), COLOR_TEXT);

		DrawString(START_TEXT_X, START_TEXT_Y, TEXT("ENTERキーでスタート"), COLOR_TEXT);

		return;
	}

	// カウントダウン表示
	if (state == COUNTDOWN)
	{
		// 残り秒数を計算
		int count = countdownTimer / 60 + 1;

		SetFontSize(80);
		// カウント数字を表示
		DrawFormatString(COUNTDOWN_TEXT_X, COUNTDOWN_TEXT_Y, COLOR_TEXT, TEXT("%d"), count);
		return;
	}
}

//============================================================
// カウントダウン終了判定
// true：カウントダウン終了
//============================================================
bool CountDown::IsFinished() const
{
	return state == END;
}
