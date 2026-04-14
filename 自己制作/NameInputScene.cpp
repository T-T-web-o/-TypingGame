#include "NameInputScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "KeyTable.h"
#include "SelectScene.h"

NameInputScene::NameInputScene()
{
	// 画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	// 背景画像読み込み
	NameInputImage = LoadGraph(TEXT("Resource/blackboard.png"));

	// 名前と名前の長さを初期化
	name[0] = '\0';
	length = 0;

	state = STATE_INPUT;
	isDuplicate = false;

	memset(keyNow, 0, sizeof(keyNow));
	memset(keyOld, 0, sizeof(keyOld));

	GetHitKeyStateAll(keyOld);
}

void NameInputScene::Update()
{
	GetHitKeyStateAll(keyNow);

	if (state == STATE_INPUT)
	{
		// 名前入力
		for (int i = 0; i < 26; i++)
		{
			if (keyNow[keyTable[i]] && !keyOld[keyTable[i]])
			{
				if (length < 15)
				{
					name[length] = TEXT('a') + i;
					length++;
					name[length] = '\0';
				}
			}
		}
		// 名前消去
		if (keyNow[KEY_INPUT_BACK] && !keyOld[KEY_INPUT_BACK])
		{
			if (length > 0)
			{
				length--;
				name[length] = '\0';
			}
		}

		// 名前決定
		if (keyNow[KEY_INPUT_RETURN] && !keyOld[KEY_INPUT_RETURN])
		{
			Ranking& ranking = GameManager::GetInstance().GetRanking();

			// 名前が重複しているか確認
			if (ranking.IsNameExists(name))
			{
				// 重複したので確認
				state = STATE_CONFIRM;
				isDuplicate = true;
			}
			else
			{
				// 重複してないので次へ
				GameManager::GetInstance().SetPlayerName(name);
				GameManager::GetInstance().ChangeScene(new SelectScene());
			}
		}
	}
	else if (state == STATE_CONFIRM)
	{
		// Y → そのまま進む
		if (CheckHitKey(KEY_INPUT_Y))
		{
			GameManager::GetInstance().SetPlayerName(name);
			GameManager::GetInstance().ChangeScene(new SelectScene());
		}

		// N → 名前入力に戻る
		if (CheckHitKey(KEY_INPUT_N))
		{
			state = STATE_INPUT;
			isDuplicate = false;
		}
	}

	memcpy(keyOld, keyNow, sizeof(keyNow));
}

void NameInputScene::Draw()
{
	// 背景画像を画面全体に表示
	DrawExtendGraph(0, 0, screenW, screenH, NameInputImage, TRUE);

	int color = GetColor(255, 255, 255);

	SetFontSize(40);
	DrawString(110, 100,TEXT("名前を入力してください"), color);

	SetFontSize(30);
	DrawString(200, 200, TEXT("名前:"), color);
	DrawString(300, 200, name, color);

	// 入力カーソルの表示
	if ((GetNowCount() / 500) % 2 == 0)
	{
		DrawString(300 + length * 16, 200, TEXT("_"), color);
	}

	// ===== 重複時 =====
	if (state == STATE_CONFIRM)
	{
		DrawString(170, 270, TEXT("同じ名前があります"), GetColor(255, 100, 100));
		DrawString(170, 330, TEXT("上書きしますか？ Y / N"), GetColor(255, 255, 255));
	}
	else
	{
		SetFontSize(20);
		DrawString(200, 300, TEXT("Enterで決定"), GetColor(255, 255, 255));
		DrawString(200, 330, TEXT("BackSpaceで消去"), color);
	}
	
}
