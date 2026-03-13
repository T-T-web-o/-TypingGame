#include "WordTypingScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "ResultScene.h"
#include "KeyTable.h"
#include "CountDown.h"
#include "Scoreboard.h"
#include "ChalkEffect.h"
#include <cstdlib>
#include <cstring>
#include <ctime>



//難易度[かんたん]の単語リスト
WordData_1 easyWords[] = {
	{ TEXT("犬"), TEXT("inu") },{ TEXT("猫"), TEXT("neko") },{ TEXT("山"), TEXT("yama") },{ TEXT("海"), TEXT("umi") },{ TEXT("空"), TEXT("sora") },
	{ TEXT("川"), TEXT("kawa") },{ TEXT("森"), TEXT("mori") },{ TEXT("花"), TEXT("hana") },{ TEXT("雨"), TEXT("ame") },{ TEXT("雪"), TEXT("yuki") },
	{ TEXT("月"), TEXT("tsuki") },{ TEXT("星"), TEXT("hoshi") },{ TEXT("石"), TEXT("ishi") },{ TEXT("鳥"), TEXT("tori") },{ TEXT("音"), TEXT("oto") },
	{ TEXT("糸"), TEXT("ito") },{ TEXT("貝"), TEXT("kai") },{ TEXT("実"), TEXT("mi") },{ TEXT("火"), TEXT("hi") },{ TEXT("木"), TEXT("ki") },
	{ TEXT("草"), TEXT("kusa") },{ TEXT("竹"), TEXT("take") },{ TEXT("冬"), TEXT("fuyu") },{ TEXT("赤"), TEXT("aka") },{ TEXT("青"), TEXT("ao") },
	{ TEXT("白"), TEXT("shiro") },{ TEXT("黒"), TEXT("kuro") },{ TEXT("春"), TEXT("haru") },{ TEXT("夏"), TEXT("natsu") },{ TEXT("秋"), TEXT("aki") }
};

//難易度[ふつう]の単語リスト
WordData_1 normalWords[] = {
	{ TEXT("林檎"), TEXT("ringo") },{ TEXT("電車"), TEXT("densha") },{ TEXT("勝利"), TEXT("shouri") },{ TEXT("失敗"), TEXT("shippai") },{ TEXT("未来"), TEXT("mirai") },
	{ TEXT("希望"), TEXT("kibou") },{ TEXT("世界"), TEXT("sekai") },{ TEXT("平和"), TEXT("heiwa") },{ TEXT("音楽"), TEXT("ongaku") },{ TEXT("映画"), TEXT("eiga") },
	{ TEXT("旅行"), TEXT("ryokou") },{ TEXT("勇気"), TEXT("yuuki") },{ TEXT("力"), TEXT("chikara") },{ TEXT("写真"), TEXT("shashin") },{ TEXT("手紙"), TEXT("tegami") },
	{ TEXT("勉強"), TEXT("benkyou") },{ TEXT("約束"), TEXT("yakusoku") },{ TEXT("感謝"), TEXT("kansha") },{ TEXT("愛情"), TEXT("aijou") },{ TEXT("仕事"), TEXT("shigoto") },
	{ TEXT("健康"), TEXT("kenkou") },{ TEXT("野球"), TEXT("yakyuu") },{ TEXT("試合"), TEXT("shiai") },{ TEXT("学校"), TEXT("gakkou") },{ TEXT("先生"), TEXT("sensei") },
	{ TEXT("家族"), TEXT("kazoku") },{ TEXT("友達"), TEXT("tomodachi") },{ TEXT("買物"), TEXT("kaimono") },{ TEXT("料理"), TEXT("ryouri") },{ TEXT("時間"), TEXT("jikan") }
};


//難易度[むずかしい]の単語リスト
WordData_1 hardWords[] = {
	{ TEXT("情報技術"), TEXT("jouhougijutsu") },{TEXT("国際社会"), TEXT("kokusaishakai") },{ TEXT("環境問題"), TEXT("kankyoumondai") },{ TEXT("経済成長"), TEXT("keizaiseichou") },
	{ TEXT("科学技術"), TEXT("kagakugijutsu") },{ TEXT("技術革新"), TEXT("gijutsukakushin") },{ TEXT("情報社会"), TEXT("jouhoushakai") },{ TEXT("産業革命"), TEXT("sangyoukakumei") },
	{ TEXT("経営戦略"), TEXT("keieisenryaku") },{ TEXT("企業活動"), TEXT("kigyoukatsudou") },{ TEXT("研究開発"), TEXT("kenkyuukaihatsu") },{ TEXT("国際関係"), TEXT("kokusaikankei") },
	{ TEXT("情報通信"), TEXT("jouhoutsuushin") },{ TEXT("環境保護"), TEXT("kankyouhogo") },{ TEXT("社会問題"), TEXT("shakaimondai") },{ TEXT("教育制度"), TEXT("kyouikuseido") },
	{ TEXT("国際交流"), TEXT("kokusaikouryuu") },{ TEXT("経済政策"), TEXT("keizaiseisaku") },{ TEXT("都市開発"), TEXT("toshikaihatsu") },{ TEXT("情報分析"), TEXT("jouhoubunseki") },
	{ TEXT("人工知能"), TEXT("jinkouchinou") },{ TEXT("機械学習"), TEXT("kikaigakushuu") },{ TEXT("深層学習"), TEXT("shinsougakushuu") },{ TEXT("電子情報"), TEXT("denshijouhou") },
	{ TEXT("情報処理"), TEXT("jouhoushori") },{ TEXT("計算科学"), TEXT("keisankagaku") },{ TEXT("情報管理"), TEXT("jouhoukanri") },{ TEXT("国際協力"), TEXT("kokusaikyouryoku") },
	{ TEXT("社会発展"), TEXT("shakaihatten") },{ TEXT("産業発展"), TEXT("sangyouhatten") }
};

//============================================================
// コンストラクタ
//============================================================
WordTypingScene::WordTypingScene()
{
	//画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//背景画像読み込み
	otherGameImage = LoadGraph(TEXT("Resource/blackboard.png"));

	//選択された難易度の取得
	Difficulty d = GameManager::GetInstance().GetDifficulty();

	//------------------------------------------------------------
	// 難易度ごとに単語リストと制限時間を設定
	//------------------------------------------------------------
	if (d == EASY)
	{
		wordList = easyWords;
		wordCount = _countof(easyWords);
		timeLimit = 45 * 60; //60fps想定
	}
	else if (d == NORMAL)
	{
		wordList = normalWords;
		wordCount = _countof(normalWords);
		timeLimit = 60 * 60;
	}
	else // HARD
	{
		wordList = hardWords;
		wordCount = _countof(hardWords);
		timeLimit = 120 * 60;
	}
	
	//単語をランダムに出すための配列を作成
	for (int i = 0; i < wordCount; i++)
	{
		order[i] = i;
	}

	//単語順をシャッフル
	for (int i = 0; i < wordCount; i++)
	{
		int r = i+rand() % (wordCount-i);
		int tmp = order[i];
		order[i] = order[r];
		order[r] = tmp;
	}
	
	//最初の単語を設定
	wordIndex = 0;
	currentWord = wordList[order[wordIndex]];


	//------------------------------------------------------------
	// スコアや入力状態の初期化
	//------------------------------------------------------------

	//入力文字初期化
	charIndex = 0;

	//スコア初期化
	score = 0;
	miss = 0;

	//コンボ初期化
	combo = 0;
	maxCombo = 0;

	//ミス表示用
	missTimer = 0;
	missIndex = -1;
	missFlag = false;
	missKey = '\0';

	//キー入力状態初期化
	memset(keyNow, 0, sizeof(keyNow));
	memset(keyOld, 0, sizeof(keyOld));
}

//============================================================
// デストラクタ
//============================================================
WordTypingScene::~WordTypingScene()
{
	DeleteGraph(otherGameImage);
}

//============================================================
// 更新処理
//============================================================
void WordTypingScene::Update()
{
    // チョークエフェクト更新
	chalk.Update();

	//制限時間が終わったらリザルト画面に切り替え
	if (IsTimeUp())
	{
		GameManager::GetInstance().ChangeScene(
			new ResultScene(score, miss,maxCombo)
		);
		return;
	}

	//キー入力更新
	UpdateInput();

	//カウントダウン更新
	countdown.Update();

	if (!countdown.IsFinished())
	{
		return;
	}

	//制限時間を減らす
	timeLimit--;

	//タイピングの正誤判定
	CheckTyping();

	// ミス表示タイマー
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
// キー入力状態を取得
//============================================================
void WordTypingScene::UpdateInput()
{
	GetHitKeyStateAll(keyNow);
}

//============================================================
// タイピングの正誤判定
//============================================================
void WordTypingScene::CheckTyping()
{
	// 今入力すべき文字
	char correctChar = currentWord.input[charIndex];

	// A～Zのキー入力判定
	for (int i = 0; i < 26; i++)
	{
		// 押された瞬間だけ判定
		if (keyNow[keyTable[i]] && !keyOld[keyTable[i]])
		{
			// キーを文字に変換
			char inputChar = 'a' + i;

			// タイピング音
			PlaySoundMem(SoundManager::typeSE, DX_PLAYTYPE_BACK);

			//------------------------------------------------------------
			// 正解
			//------------------------------------------------------------
			if (inputChar == correctChar)
			{
				charIndex++;

				// 単語終了チェック
				if (currentWord.input[charIndex] == '\0')
				{
					chalk.Spawn(230 + (charIndex-1) * 15, 210);
					if (!missFlag)
					{
						combo++;
						chalk.Spawn(95,160);
						if (combo > maxCombo) {
							maxCombo = combo;
						}
					}
					score++;
					NextWord();
				}
			}
			//------------------------------------------------------------
			// ミス
			//------------------------------------------------------------
			else
			{
				miss++;
				combo = 0;
				missFlag = true;
				missTimer = 20;
				missIndex = charIndex;
				missKey = toupper(inputChar);
			}
			break; // 1入力で終了
		}
	}
	// 前フレーム保存
	memcpy(keyOld, keyNow, sizeof(keyNow));
}

//============================================================
// 次の単語へ移動
//============================================================
void WordTypingScene::NextWord()
{
	wordIndex++;

	//------------------------------------------------------------
	// 全単語終了 → リザルト
	//------------------------------------------------------------
	if (wordIndex >= wordCount)
	{
		GameManager::GetInstance().ChangeScene(
			new ResultScene(score, miss, maxCombo)
		);
		return;
	}
	currentWord = wordList[order[wordIndex]];
	charIndex = 0;
	missFlag = false;
}

//============================================================
// 制限時間終了判定
//============================================================
bool WordTypingScene::IsTimeUp() const
{
	return timeLimit <= 0;
}

//============================================================
// 描画処理
//============================================================
void WordTypingScene::Draw()
{

	// 背景画像を画面全体に表示
	SetFontSize(16);
	DrawExtendGraph(0, 0, screenW, screenH, otherGameImage, TRUE);

	countdown.Draw(400, 200);

	//------------------------------------------------------------
	// カウントダウン表示
	//------------------------------------------------------------
	if (!countdown.IsFinished())
	{
		return;
	}

	//------------------------------------------------------------
	// タイトル表示
	//------------------------------------------------------------
	SetFontSize(40);
	DrawString(170, 10, TEXT("タイムアタック"), GetColor(255, 255, 255));

	//-------------------------------------------------------------------
	//単語・ローマ字を中央に
	//-------------------------------------------------------------------
	int len = _tcslen(currentWord.input);    // ローマ字の長さを取得
	int width = len * 15;                    // ローマ字の幅を取得

	int centerX = screenW / 2;               // 画面の中央を取得
	int baseX = centerX - width / 2 - 40;    //  ローマ字の中央を取得

	int wordWidth = GetDrawStringWidth(currentWord.display
	   ,_tcslen(currentWord.display));            // 単語の長さを取得

	int romajiCenter = baseX + width / 2;         // ローマ字の中央を取得
	int wordX = romajiCenter - wordWidth / 2;     // 単語の中央を取得

	//------------------------------------------------------------
	// 単語表示
	//------------------------------------------------------------
	SetFontSize(30);
	DrawFormatString(wordX, 150, GetColor(240, 240, 240), TEXT("%s"), currentWord.display);

	//------------------------------------------------------------
	// 入力に応じて文字の色を変更して表示
	//------------------------------------------------------------
	for (int i = 0; currentWord.input[i] != '\0'; i++)
	{
		int color;

		if (i < charIndex)
		{
			// 入力済み（緑）
			color = GetColor(100, 255, 100);
		}
		else if (i == missIndex && missTimer > 0)
		{
			// 入力ミス　(赤)
			color = GetColor(255, 0, 0);
		}
		else
		{
			// まだ（白）
			color = GetColor(255, 255, 255);
		}

		DrawFormatString(baseX + i * 15, 190,color,TEXT("%c"),currentWord.input[i]);
	}

	SetFontSize(20);
	//------------------------------------------------------------
	// スコア表示
	//------------------------------------------------------------
	DrawFormatString(10, 20, GetColor(230, 230, 230), TEXT("スコア:%d"), score);     

	//------------------------------------------------------------
	// タイプミス数の表示
	//------------------------------------------------------------
	DrawFormatString(10, 60, GetColor(230, 230, 230), TEXT("ミス:%d"), miss);               

	//------------------------------------------------------------
	// 制限時間表示
	//------------------------------------------------------------
	DrawFormatString(10, 100, GetColor(230, 230, 230), TEXT("残り時間:%d"), timeLimit / 60);

	//------------------------------------------------------------
	// コンボ表示
	//------------------------------------------------------------
	DrawString(10, 150, TEXT("コンボ:"), GetColor(230, 230, 230));

	// コンボごとの表示サイズ変更
	int comboSize = 20 + combo * 1;
	if (comboSize > 30) comboSize = 30;
	SetFontSize(comboSize);

	DrawFormatString(90, 150, GetColor(230, 230, 0), TEXT("%d"), combo);
	
	SetFontSize(16);
	//------------------------------------------------------------
	// 難易度の表示
	//------------------------------------------------------------
	Difficulty d = GameManager::GetInstance().GetDifficulty();

	//難易度ごとに表示する内容を変更
	diffText = TEXT("かんたん");
	diffColor = GetColor(100, 200, 255);       //[かんたん]   水色
	if (d == NORMAL) 
	{
		diffText = TEXT("ふつう");
		diffColor = GetColor(255, 255, 100);   //[ふつう]     黄色
	}
	if (d == HARD)
	{
		diffText = TEXT("むずかしい");
		diffColor = GetColor(255, 100, 100);   //[むずかしい] 赤色
	}
	
	DrawFormatString(250, 70,diffColor,TEXT("難易度: %s"), diffText);

	//------------------------------------------------------------
	// キーボード表示
	//------------------------------------------------------------
	if (currentWord.input[charIndex] != '\0')
	{
		TCHAR target = currentWord.input[charIndex];
		target = toupper(target);
		keyboard.Draw(target,missKey,100, 300);
	}

	//スコアボード表示
    scoreboard.Draw(480, 10);

	//チョークエフェクト表示
	chalk.Draw();
}
