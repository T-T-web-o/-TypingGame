#include "PracticeTypingScene_2.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "ResultScene.h"
#include "KeyTable.h"
#include "CountDown.h"
#include "Scoreboard.h"
#include "ChalkEffect.h"
#include "Input.h"

//============================================================
// 描画用定数
//============================================================
 
const int COUNTDOWN_X = 400;    // カウントダウン表示のX座標
const int COUNTDOWN_Y = 200;    // カウントダウン表示のY座標

const int TYPING_WORD_X = 260;  // タイピング文字のX座標
const int TYPING_WORD_Y = 170;  // タイピング文字のY座標

const int ROMAJI_X = 270;       // ローマ字文字のX座標
const int ROMAJI_Y = 210;       // ローマ字文字のY座標
const int ROMAJI_SPACE = 15;    // 文字と文字の間隔

const int UI_X = 10;         // UIのX座標
const int UI_START_Y = 20;   // UIの開始Y座標
const int UI_SPACE = 30;     // UI同士の間隔

const int END_TEXT_X = 550;  // 終了案内のX座標
const int END_TEXT_Y = 430;  // 終了案内のY座標

const int SCOREBOARD_X = 480; // スコアボードのX座標
const int SCOREBOARD_Y = 10;  // スコアボードのY座標

const int KEYBOARD_X = 100;    // キーボード描画のX座標
const int KEYBOARD_Y = 300;    // キーボード描画のY座標

const int COLOR_TEXT = GetColor(240, 240, 240);  //白
const int COLOR_TYPED = GetColor(100, 255, 100);  //緑
const int COLOR_MISS = GetColor(255, 0, 0);        //赤

WordData_2 practiceKana[] = {

	// ===== あ行 =====
	{ TEXT("あ"), TEXT("a") },{ TEXT("い"), TEXT("i") },{ TEXT("う"), TEXT("u") },{ TEXT("え"), TEXT("e") },{ TEXT("お"), TEXT("o") },

	// ===== か行 =====
	{ TEXT("か"), TEXT("ka") },{ TEXT("き"), TEXT("ki") },{ TEXT("く"), TEXT("ku") },{ TEXT("け"), TEXT("ke") },{ TEXT("こ"), TEXT("ko") },

	// ===== さ行 =====
	{ TEXT("さ"), TEXT("sa") },{ TEXT("し"), TEXT("shi") },{ TEXT("す"), TEXT("su") },{ TEXT("せ"), TEXT("se") },{ TEXT("そ"), TEXT("so") },

	// ===== た行 =====
	{ TEXT("た"), TEXT("ta") },{ TEXT("ち"), TEXT("chi") },{ TEXT("つ"), TEXT("tsu") },{ TEXT("て"), TEXT("te") },{ TEXT("と"), TEXT("to") },

	// ===== な行 =====
	{ TEXT("な"), TEXT("na") },{ TEXT("に"), TEXT("ni") },{ TEXT("ぬ"), TEXT("nu") },{ TEXT("ね"), TEXT("ne") },{ TEXT("の"), TEXT("no") },

	// ===== は行 =====
	{ TEXT("は"), TEXT("ha") },{ TEXT("ひ"), TEXT("hi") },{ TEXT("ふ"), TEXT("fu") },{ TEXT("へ"), TEXT("he") },{ TEXT("ほ"), TEXT("ho") },

	// ===== ま行 =====
	{ TEXT("ま"), TEXT("ma") },{ TEXT("み"), TEXT("mi") },{ TEXT("む"), TEXT("mu") },{ TEXT("め"), TEXT("me") },{ TEXT("も"), TEXT("mo") },

	// ===== や行 =====
	{ TEXT("や"), TEXT("ya") },{ TEXT("ゆ"), TEXT("yu") },{ TEXT("よ"), TEXT("yo") },

	// ===== ら行 =====
	{ TEXT("ら"), TEXT("ra") },{ TEXT("り"), TEXT("ri") },{ TEXT("る"), TEXT("ru") },{ TEXT("れ"), TEXT("re") },{ TEXT("ろ"), TEXT("ro") },

	// ===== わ行 =====
	{ TEXT("わ"), TEXT("wa") },{ TEXT("を"), TEXT("wo") },{ TEXT("ん"), TEXT("n") }
};

//============================================================
// コンストラクタ
//============================================================
PracticeTypingScene_2::PracticeTypingScene_2()
{
   //画面サイズ取得
   GetDrawScreenSize(&screenW, &screenH);

   //背景画像読み込み
   gameImage = LoadGraph(TEXT("Resource/Model/blackboard.png"));

   //最初の単語設定
   kanaIndex = 0;
   currentWord = practiceKana[kanaIndex];

   //スコア初期化
   score = 0;
   miss = 0;

   //現在入力している文字位置
   charIndex = 0;

   //キー入力状態初期化
   memset(keyNow, 0, sizeof(keyNow));
   memset(keyOld, 0, sizeof(keyOld));

   //コンボ初期化
   combo = 0;
   maxCombo = 0;

   //この単語でミスしたか
   missFlag = false;

   //ミス表示用
   missTimer = 0;
   missIndex = -1;
   missKey = '\0';
}

//============================================================
// デストラクタ
//============================================================
PracticeTypingScene_2::~PracticeTypingScene_2()
{
	DeleteGraph(gameImage);
}

//============================================================
// 更新処理
//============================================================
void PracticeTypingScene_2::Update()
{
	//ESCキーで結果画面へ
	if (Input::IsTriggerEsc())
	{
		GameManager::GetInstance().ChangeScene(new ResultScene(score, miss,maxCombo,false));
		return;
	}

	//チョークエフェクト更新
	chalk.Update();

	//現在のキー状態取得
	GetHitKeyStateAll(keyNow);

	//カウントダウン更新
	countdown.Update();

	//カウントダウンが終わるまでゲーム開始しない
	if (!countdown.IsFinished())
	{
		return;
	}

	//タイピング処理
	TypingUpdate();

	//次フレーム用にキー状態保存
	memcpy(keyOld, keyNow, sizeof(keyNow));
}

//============================================================
// タイピング処理本体
//============================================================
void PracticeTypingScene_2::TypingUpdate()
{
	// 今入力すべき文字
	char correctChar = currentWord.input[charIndex];

	// A～Zのキー入力判定
	for (int i = 0; i < 26; i++)
	{
		// 押された瞬間だけ判定
		if (keyNow[keyTable[i]] && !keyOld[keyTable[i]])
		{
			//キーを文字に変換
			char inputChar = 'a' + i;

			// タイピング音
			PlaySoundMem(SoundManager::typeSE, DX_PLAYTYPE_BACK);

			
		    // 正解判定
			if (inputChar == correctChar)
			{
				charIndex++;

				//単語入力完了
				if (currentWord.input[charIndex] == '\0')
				{
					//チョークエフェクト
					chalk.Spawn(270+charIndex*15, 240);

					//ミスしていなければコンボ増加
					if (!missFlag) {
						combo++;
						if (combo > maxCombo) {
							maxCombo = combo;
						}
					}

					score++;

					//次の単語へ
					kanaIndex++;

					missFlag = false;

					//最後まで行ったら最初へ戻す
					if (kanaIndex >= sizeof(practiceKana) / sizeof(practiceKana[0]))
					{
						kanaIndex = 0; // 最初に戻す
					}
					currentWord = practiceKana[kanaIndex];

					charIndex = 0;
				}
			}
			else
			{
				// ミス
				miss++;
				combo = 0;
				missFlag = true;
				missTimer = 20;
				missIndex=charIndex;
				missKey = toupper(inputChar);
			}
			break;
		}
	}
	//ミス表示タイマー
	if (missTimer > 0)
	{
		missTimer--;
	}
	else
	{
		missIndex = -1;
		missKey = '\0';
	}
}

//============================================================
// 描画処理
//============================================================
void PracticeTypingScene_2::Draw()
{
	//背景画像を画面全体に表示
	DrawExtendGraph(0, 0, screenW, screenH, gameImage, TRUE);

	//カウントダウン表示
	countdown.Draw(COUNTDOWN_X, COUNTDOWN_Y);

	// カウントダウンが終わるまでゲーム画面は表示しない
	if (!countdown.IsFinished())
	{
		return;
	}

    // タイピング文字を表示
	SetFontSize(40);
	DrawFormatString(TYPING_WORD_X, TYPING_WORD_Y, COLOR_TEXT, TEXT("%s"), currentWord.display);
	
	SetFontSize(30);

	//入力に応じて文字の色を変更して表示
	for (int i = 0; currentWord.input[i] != '\0'; i++)
	{
		int color;

		if (i < charIndex)
		{
			//入力済み（緑）
			color = COLOR_TYPED;
		}
		else if (i== missIndex&&missTimer>0)
		{
			//入力ミス（赤）
			color = COLOR_MISS;
		}
		else
		{
			// まだ（白）
			color = COLOR_TEXT;
		}
		// ローマ字を1文字ずつ描画
		DrawFormatString(ROMAJI_X + i * ROMAJI_SPACE, ROMAJI_Y, color, TEXT("%c"), currentWord.input[i]);
	}
	
	SetFontSize(23);

    // スコア表示
	DrawFormatString(UI_X, UI_START_Y + UI_SPACE * 0, COLOR_TEXT, TEXT("スコア:%d"), score);

	// タイプミス数の表示
	DrawFormatString(UI_X, UI_START_Y + UI_SPACE * 1, COLOR_TEXT, TEXT("ミス:%d"), miss);

    // コンボ表示
	DrawFormatString(UI_X, UI_START_Y + UI_SPACE * 2, COLOR_TEXT, TEXT("コンボ：%d"), combo);


	SetFontSize(16);
	// 終了案内
	DrawString(END_TEXT_X, END_TEXT_Y, TEXT("ESCで終了"), COLOR_TEXT);


	// キーボード表示
	if (currentWord.input[charIndex] != '\0')
	{
		// 次に入力する文字を取得
		TCHAR target = currentWord.input[charIndex];

		// 小文字 → 大文字に変換（キーボード表示用）
		target = toupper(target);

		// キーボードUI描画
		keyboard.Draw(target,missKey, KEYBOARD_X, KEYBOARD_Y);
	}

	//スコアボード表示
	scoreboard.Draw(SCOREBOARD_X, SCOREBOARD_Y);

	//チョーク粉エフェクト表示
	chalk.Draw();
}
