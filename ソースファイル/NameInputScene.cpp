#include "NameInputScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "KeyTable.h"
#include "SelectScene.h"
#include "SoundManager.h"
#include "ExplanationScene.h"

//============================================================
// レイアウト定数
//============================================================

// タイトル位置
const int TITLE_X = 110;
const int TITLE_Y = 100;

// 名前入力欄
const int NAME_LABEL_X = 200;
const int NAME_LABEL_Y = 200;

const int NAME_INPUT_X = 300;
const int NAME_INPUT_Y = 200;

// カーソル
const int CURSOR_X = 300;
const int CURSOR_Y = 200;
const int CURSOR_OFFSET_X = 16;

// メッセージ位置
const int MESSAGE_X1 = 170;
const int MESSAGE_X2 = 200;

const int MESSAGE_Y1 = 270;
const int MESSAGE_Y2 = 300;
const int MESSAGE_Y3 = 330;

//============================================================
// フォントサイズ
//============================================================
const int FONT_TITLE = 40;
const int FONT_NORMAL = 30;
const int FONT_SMALL = 20;

//============================================================
// 色
//============================================================
const int COLOR_WHITE = GetColor(230, 230, 230);
const int COLOR_RED = GetColor(255, 100, 100); 

const int MAX_NAME_LENGTH = 5;

// コンストラクタ
NameInputScene::NameInputScene()
{
	// 画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	// 背景画像読み込み
	NameInputImage = LoadGraph(TEXT("Resource/Model/blackboard.png"));

	// 名前と名前の長さを初期化
	name[0] = '\0';
	length = 0;

	// 入力状態を初期化
	state = STATE_INPUT;

	//重複フラグを初期化
	isDuplicate = false;

	memset(keyNow, 0, sizeof(keyNow));
	memset(keyOld, 0, sizeof(keyOld));

	GetHitKeyStateAll(keyOld);
}

// 更新処理
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
				// タイピング音
				PlaySoundMem(SoundManager::typeSE, DX_PLAYTYPE_BACK);

				if (length < MAX_NAME_LENGTH)
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
			// タイピング音
			PlaySoundMem(SoundManager::typeSE, DX_PLAYTYPE_BACK);

			if (length > 0)
			{
				length--;
				name[length] = '\0';
			}
		}

		// 名前決定
		if (keyNow[KEY_INPUT_RETURN] && !keyOld[KEY_INPUT_RETURN])
		{
			// タイピング音
			PlaySoundMem(SoundManager::typeSE, DX_PLAYTYPE_BACK);

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


	//左SHIFTキーの入力状態を取得
	nowShift = CheckHitKey(KEY_INPUT_LSHIFT);

	//SHIFTキーが押されたら
	if (nowShift && !prevShift)
	{
		//効果音再生
		PlaySoundMem(SoundManager::titleSE, DX_PLAYTYPE_BACK);

		// 説明シーンに切り替え
		GameManager::GetInstance().ChangeScene(new ExplanationScene());
	}
	// 前フレームの入力状態を保存
	prevShift = nowShift;
}

// 描画処理
void NameInputScene::Draw()
{
	// 背景画像を画面全体に表示
	DrawExtendGraph(0, 0, screenW, screenH, NameInputImage, TRUE);

	SetFontSize(FONT_TITLE);

	DrawString(TITLE_X, TITLE_Y,TEXT("名前を入力してください"), COLOR_WHITE);

	SetFontSize(FONT_NORMAL);

	DrawString(NAME_LABEL_X, NAME_LABEL_Y, TEXT("名前:"), COLOR_WHITE);
	DrawString(NAME_INPUT_X, NAME_INPUT_Y, name, COLOR_WHITE);

	// 入力カーソルの表示
	if ((GetNowCount() / 500) % 2 == 0)
	{
		DrawString(CURSOR_X + length * CURSOR_OFFSET_X, CURSOR_Y, TEXT("_"), COLOR_WHITE);
	}

	// ===== 重複時 =====
	if (state == STATE_CONFIRM)
	{
		DrawString(MESSAGE_X1, MESSAGE_Y1, TEXT("同じ名前があります"), COLOR_RED);
		DrawString(MESSAGE_X1, MESSAGE_Y3, TEXT("上書きしますか？ Y / N"), COLOR_WHITE);
	}
	else
	{
		SetFontSize(FONT_SMALL);

		DrawString(MESSAGE_X2, MESSAGE_Y2, TEXT("Enterで決定"), COLOR_WHITE);
		DrawString(MESSAGE_X2, MESSAGE_Y3, TEXT("BackSpaceで消去"), COLOR_WHITE);
	}

	// 文字数制限
	if (length >= MAX_NAME_LENGTH)
	{
		DrawString(MESSAGE_X2, 360, TEXT("これ以上入力できません"), COLOR_RED);
	}

	DrawString(20, 400, TEXT("左SHIFTで戻る"),COLOR_WHITE);
}
