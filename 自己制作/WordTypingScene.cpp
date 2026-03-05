#include "WordTypingScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "ResultScene.h"
#include "KeyTable.h"
#include "CountDown.h"
#include <cstdlib>
#include <cstring>

//難易度[かんたん]の単語リスト
WordData easyWords[] = {
	{ TEXT("犬"), TEXT("inu") },{ TEXT("猫"), TEXT("neko") },{ TEXT("山"), TEXT("yama") },{ TEXT("海"), TEXT("umi") },{ TEXT("空"), TEXT("sora") },
	{ TEXT("川"), TEXT("kawa") },{ TEXT("森"), TEXT("mori") },{ TEXT("花"), TEXT("hana") },{ TEXT("雨"), TEXT("ame") },{ TEXT("雪"), TEXT("yuki") },
	{ TEXT("月"), TEXT("tsuki") },{ TEXT("星"), TEXT("hoshi") },{ TEXT("石"), TEXT("ishi") },{ TEXT("鳥"), TEXT("tori") },{ TEXT("音"), TEXT("oto") },
	{ TEXT("糸"), TEXT("ito") },{ TEXT("貝"), TEXT("kai") },{ TEXT("実"), TEXT("mi") },{ TEXT("火"), TEXT("hi") },{ TEXT("木"), TEXT("ki") },
	{ TEXT("草"), TEXT("kusa") },{ TEXT("竹"), TEXT("take") },{ TEXT("冬"), TEXT("fuyu") },{ TEXT("赤"), TEXT("aka") },{ TEXT("青"), TEXT("ao") },
	{ TEXT("白"), TEXT("shiro") },{ TEXT("黒"), TEXT("kuro") },{ TEXT("春"), TEXT("haru") },{ TEXT("夏"), TEXT("natsu") },{ TEXT("秋"), TEXT("aki") }
};

//難易度[ふつう]の単語リスト
WordData normalWords[] = {
	{ TEXT("林檎"), TEXT("ringo") },{ TEXT("電車"), TEXT("densha") },{ TEXT("勝利"), TEXT("shouri") },{ TEXT("失敗"), TEXT("shippai") },{ TEXT("未来"), TEXT("mirai") },
	{ TEXT("希望"), TEXT("kibou") },{ TEXT("世界"), TEXT("sekai") },{ TEXT("平和"), TEXT("heiwa") },{ TEXT("音楽"), TEXT("ongaku") },{ TEXT("映画"), TEXT("eiga") },
	{ TEXT("旅行"), TEXT("ryokou") },{ TEXT("勇気"), TEXT("yuuki") },{ TEXT("力"), TEXT("chikara") },{ TEXT("写真"), TEXT("shashin") },{ TEXT("手紙"), TEXT("tegami") },
	{ TEXT("勉強"), TEXT("benkyou") },{ TEXT("約束"), TEXT("yakusoku") },{ TEXT("感謝"), TEXT("kansha") },{ TEXT("愛情"), TEXT("aijou") },{ TEXT("仕事"), TEXT("shigoto") },
	{ TEXT("健康"), TEXT("kenkou") },{ TEXT("野球"), TEXT("yakyuu") },{ TEXT("試合"), TEXT("shiai") },{ TEXT("学校"), TEXT("gakkou") },{ TEXT("先生"), TEXT("sensei") },
	{ TEXT("家族"), TEXT("kazoku") },{ TEXT("友達"), TEXT("tomodachi") },{ TEXT("買物"), TEXT("kaimono") },{ TEXT("料理"), TEXT("ryouri") },{ TEXT("時間"), TEXT("jikan") }
};


//難易度[むずかしい]の単語リスト
WordData hardWords[] = {
	{ TEXT("情報"), TEXT("jouhou") },{ TEXT("経済"), TEXT("keizai") },{ TEXT("研究"), TEXT("kenkyuu") },{ TEXT("環境"), TEXT("kankyou") },{ TEXT("国際"), TEXT("kokusai") },
	{ TEXT("歴史"), TEXT("rekishi") },{ TEXT("文化"), TEXT("bunka") },{ TEXT("産業"), TEXT("sangyou") },{ TEXT("法律"), TEXT("houritsu") },{ TEXT("戦略"), TEXT("senryaku") },
	{ TEXT("成長"), TEXT("seichou") },{ TEXT("競争"), TEXT("kyousou") },{ TEXT("責任"), TEXT("sekinin") },{ TEXT("対策"), TEXT("taisaku") },{ TEXT("発展"), TEXT("hatten") },
	{ TEXT("効率"), TEXT("kouritsu") },{ TEXT("開発"), TEXT("kaihatsu") },{ TEXT("生産"), TEXT("seisan") },{ TEXT("経営"), TEXT("keiei") },{ TEXT("企業"), TEXT("kigyou") },
	{ TEXT("拡大"), TEXT("kakudai") },{ TEXT("革命"), TEXT("kakumei") },{ TEXT("創造"), TEXT("souzou") },{ TEXT("技術"), TEXT("gijutsu") },{ TEXT("電力"), TEXT("denryoku") },
	{ TEXT("建築"), TEXT("kenchiku") },{ TEXT("挑戦"), TEXT("chousen") },{ TEXT("経験"), TEXT("keiken") },{ TEXT("計画"), TEXT("keikaku") },{ TEXT("組織"), TEXT("soshiki") }
};

WordTypingScene::WordTypingScene()
{
	//画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//背景画像読み込み
	otherGameImage = LoadGraph(TEXT("Resource/blackboard.png"));

	//タイピング音読み込み
	typeSE = LoadSoundMem(TEXT("Resource/type.mp3"));

	//選択された難易度の取得
	Difficulty d = GameManager::GetInstance().GetDifficulty();

	//選ばれた難易度ごとに[単語リスト][制限時間]を切り替える
	if (d == EASY)
	{
		wordList = easyWords;
		wordCount = _countof(easyWords);
		timeLimit = 30 * 60; //60fps想定
	}
	else if (d == NORMAL)
	{
		wordList = normalWords;
		wordCount = _countof(normalWords);
		timeLimit = 45 * 60;
	}
	else // HARD
	{
		wordList = hardWords;
		wordCount = _countof(hardWords);
		timeLimit = 60 * 60;
	}
	
	//単語をランダムに出すための配列を作成
	for (int i = 0; i < wordCount; i++)
	{
		order[i] = i;
	}

	//単語をランダムにするためのシャッフル処理
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


	//初期化
	charIndex = 0;
	score = 0;
	miss = 0;
	combo = 0;
	maxCombo = 0;
	missFlag = false;
	memset(keyNow, 0, sizeof(keyNow));
	memset(keyOld, 0, sizeof(keyOld));
}

WordTypingScene::~WordTypingScene()
{
	DeleteGraph(otherGameImage);
	DeleteSoundMem(typeSE);
}

void WordTypingScene::Update()
{
	//制限時間を減らす
	timeLimit--;

	//制限時間が終わったらリザルト画面に切り替え
	if (IsTimeUp())
	{
		GameManager::GetInstance().ChangeScene(
			new ResultScene(score, miss,maxCombo)
		);
		return;
	}
	//キー入力状態を更新
	UpdateInput();

	//カウントダウンが終わったらゲームスタート
	countdown.Update();

	if (!countdown.IsFinished())
	{
		return;
	}

	//タイピングの正誤判定
	CheckTyping();
}

void WordTypingScene::UpdateInput()
{
	// 現在フレームの全キー状態を取得
    // keyNow に「押されている / 押されていない」を格納する
	GetHitKeyStateAll(keyNow);
}

void WordTypingScene::CheckTyping()
{
	// 今入力すべき正解文字
	char correctChar = currentWord.input[charIndex];

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

			if (inputChar == correctChar)
			{
				// ====== 正解 ======
				charIndex++;

				// 単語終了チェック
				if (currentWord.input[charIndex] == '\0')
				{
					if (!missFlag)
					{
						combo++;
						if (combo > maxCombo) {
							maxCombo = combo;
						}
					}
					score++;
					NextWord();
				}
			}
			else
			{
				// ====== ミス ======
				miss++;
				combo = 0;
				missFlag = true;
			}
			break; // 1入力で終了
		}
	}
	// 前フレーム保存
	memcpy(keyOld, keyNow, sizeof(keyNow));
}

//次のワードにいく処理
void WordTypingScene::NextWord()
{
	wordIndex++;

	//すべての単語ができったら、リザルト画面に切り替え
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

//制限時間を過ぎたかを判定
bool WordTypingScene::IsTimeUp() const
{
	return timeLimit <= 0;
}

void WordTypingScene::Draw()
{

	//背景画像を画面全体に表示
	SetFontSize(16);
	DrawExtendGraph(0, 0, screenW, screenH, otherGameImage, TRUE);

	countdown.Draw(400, 200);

	// まだ開始していないならここで終了
	if (!countdown.IsFinished())
	{
		return;
	}

	DrawString(250, 10, TEXT("タイムアタック"), GetColor(255, 255, 255));

	//タイピングする文字の表示
	SetFontSize(22);
	DrawFormatString(250, 200, GetColor(230, 230, 230), TEXT("Word:%s"), currentWord.display);

	//入力済みの文字を緑色で表示
	for (int i = 0; currentWord.input[i] != '\0'; i++)
	{
		int color;

		if (i < charIndex)
		{
			//入力済み（緑）
			color = GetColor(100, 255, 100);
		}
		else
		{
			// まだ（白）
			color = GetColor(255, 255, 255);
		}

		DrawFormatString(270+ i * 15,260,color,TEXT("%c"),currentWord.input[i]);
	}

	SetFontSize(16);
	DrawFormatString(10, 10, GetColor(230, 230, 230), TEXT("スコア:%d"), score);             //スコアの表示
	DrawFormatString(10, 40, GetColor(230, 230, 230), TEXT("ミス:%d"), miss);                //タイピングミス数の表示
	DrawFormatString(10, 70, GetColor(230, 230, 230), TEXT("残り時間:%d"), timeLimit / 60);  //制限時間を表示
	DrawFormatString(10, 100, GetColor(230, 230, 0), TEXT("コンボ：%d"), combo);              //コンボ表示

	//======難易度の表示======
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
	
	DrawFormatString(400, 100,diffColor,TEXT("難易度: %s"), diffText);
	//=======================

	//======キーボード表示======
	if (currentWord.input[charIndex] != '\0')
	{
		TCHAR target = currentWord.input[charIndex];
		target = toupper(target);
		keyboard.Draw(target, 100, 300);
	}
	//==========================
}
