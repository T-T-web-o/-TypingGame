#include "CountDown.h"
#include "DxLib.h"

CountDown::CountDown()
{
	state = WAIT_START;
	countdownTimer = 180; // 3秒（60fps×3）
}

void CountDown::Update()
{
	//ゲーム開始前
	if (state == WAIT_START)
	{
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			state = COUNTDOWN;

		}
		return;
	}

	//カウントダウン
	if (state == COUNTDOWN)
	{
		countdownTimer--;
		if (countdownTimer == 0)
		{
			state = END;
		}
		return;
	}
}

void CountDown::Draw(int x, int y)
{
	//ゲーム開始前の表示
	if (state == WAIT_START)
	{
		DrawString(230, 170, TEXT(" タイピングゲーム"), GetColor(230, 230, 230));
		DrawString(240, 240, TEXT("ENTERキーでスタート"), GetColor(255, 255, 255));
		return;
	}

	//カウントダウンの表示
	if (state == COUNTDOWN)
	{
		int count = countdownTimer / 60 + 1;

		SetFontSize(80);
		DrawFormatString(300, 220, GetColor(255, 255, 255), TEXT("%d"), count);
		return;
	}
}

bool CountDown::IsFinished() const
{
	return state == END;
}
