#include "PracticeTypingScene_2.h"
#include "GameManager.h"
#include "ResultScene.h"
#include "KeyTable.h"

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

PracticeTypingScene_2::PracticeTypingScene_2()
{
   //画面サイズ取得
   GetDrawScreenSize(&screenW, &screenH);

   //背景画像読み込み
   gameImage = LoadGraph(TEXT("Resource/game.png"));

   //タイピング音読み込み
   typeSE = LoadSoundMem(TEXT("Resource/type.mp3"));

   

   kanaIndex = 0;
   currentWord = practiceKana[kanaIndex];

   // スコア・ミス数の初期化
   score = 0;
   miss = 0;
   charIndex = 0;
   memset(keyNow, 0, sizeof(keyNow));
   memset(keyOld, 0, sizeof(keyOld));

   combo = 0;
   maxCombo = 0;
   missFlag = false;
}

PracticeTypingScene_2::~PracticeTypingScene_2()
{
	DeleteGraph(gameImage);
	DeleteSoundMem(typeSE);
}

void PracticeTypingScene_2::Update()
{
	// Tabキーが押されたら結果画面へ遷移
	if (CheckHitKey(KEY_INPUT_TAB))
	{
		GameManager::GetInstance().ChangeScene(new ResultScene(score, miss,maxCombo));
		return;
	}

	// 現在フレームの全キー状態を取得
	// keyNow に「押されている / 押されていない」を格納する
	GetHitKeyStateAll(keyNow);

	// 今入力すべき正解文字
	char correctKana = currentWord.input[charIndex];

	// A～Zのどれが押されたか判断
	for (int i = 0; i < 26; i++)
	{
		// 押された瞬間のみ反応
	   if (keyNow[keyTable[i]] && !keyOld[keyTable[i]])
	   {
		   // 押されたキーを文字に変換
			char inputChar = 'a' + i;

			// タイピング音
			PlaySoundMem(typeSE, DX_PLAYTYPE_BACK);

			if (inputChar == correctKana)
			{
				// ====== 正解 ======
				charIndex++;

				// 単語終了チェック
				if (currentWord.input[charIndex] == '\0')
				{
					if (!missFlag){
						combo++;
						if (combo > maxCombo) {
							maxCombo = combo;
						}
					}
					score++;
					kanaIndex++;
					missFlag = false;
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
				miss++;
				combo = 0;
				missFlag = true;
			}
			break;
	   }
	}
	memcpy(keyOld, keyNow, sizeof(keyNow));
}

void PracticeTypingScene_2::Draw()
{
	//背景画像を画面全体に表示
	DrawExtendGraph(0, 0, screenW, screenH, gameImage, TRUE);

	//タイピングする文字の表示
	SetFontSize(40);
	DrawFormatString(220, 170, GetColor(230, 230, 230), TEXT("Word:%s"), currentWord.display);
	SetFontSize(30);
	DrawFormatString(335, 220, GetColor(230, 230, 230), TEXT("%s"), currentWord.input);

	//======タイピングしている文字の表示======
	DrawString(220, 260, TEXT("Typed : "), GetColor(230, 230, 230));
	for (int i = 0; i < charIndex; i++)
	{
		DrawFormatString(340 + (i * 15), 260, GetColor(230, 230, 230), TEXT("%c"), currentWord.input[i]);
	}
	//========================================

	SetFontSize(16);
	//スコアの表示
	DrawFormatString(100, 140, GetColor(255, 255, 255), TEXT("スコア:%d"), score);

	//タイピングミス数の表示
	DrawFormatString(100, 160, GetColor(255, 255, 255), TEXT("ミス:%d"), miss);

	//コンボ表示
	DrawFormatString(100, 180, GetColor(255, 255, 255), TEXT("コンボ：%d"), combo);

	//リザルト画面へ移行表示 
	DrawString(440, 320, TEXT("Tabで終了"), GetColor(230, 230, 230));

	//======キーボード表示======
	if (currentWord.input[charIndex] != '\0')
	{
		TCHAR target = currentWord.input[charIndex];
		target = toupper(target);
		keyboard.Draw(target, 100, 350);
	}
	//==========================
}
