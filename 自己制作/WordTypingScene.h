#pragma once
#include <tchar.h>
#include "Scene.h"
#include "Keyboard.h"
#include "CountDown.h"
#include "Scoreboard.h"
#include "ChalkEffect.h"

static const int MAX_WORDS = 30;

struct WordData
{
	const TCHAR* display; // 表示用（日本語）
	const TCHAR* input;   // 判定用（ローマ字）
};

//単語タイピングゲーム用シーン
class WordTypingScene:public Scene
{
private:
	//====== ゲーム進行用 ======
	WordData currentWord;    //現在の単語
	WordData* wordList;      //難易度ごとの単語リスト
	int wordCount;           //単語の数を保存する変数
	int charIndex;           //単語を何文字目まで入力したかを保存する変数
	int order[MAX_WORDS];    //単語の出現順をランダムにするための変数
	int wordIndex;           //現在何番目の単語なのかを保存する変数

	//====== スコア管理 ======
	int score;               //スコア
	int miss;                //ミス
	int timeLimit;           //制限時間

	//====== 入力管理 ======
	char keyNow[256];        //現在フレームのキー情報
	char keyOld[256];        //前フレームのキー情報

	//====== 内部処理 ======
	void UpdateInput();      //キー入力の更新
	void CheckTyping();      //タイピング判定
	void NextWord();         // 次の単語へ
	bool IsTimeUp() const;   // 時間切れ判定

	//====== 背景画像 ======
	int otherGameImage; 
	int screenW;
	int screenH;

	//====== 音======
	int typeSE; 

	//====== コンボ管理 ======
	int combo;              // 現在コンボ
	int maxCombo;           // 最大コンボ
	bool missFlag = false;  // この単語でミスしたか

	//難易度ごとの表示管理
	const TCHAR* diffText; //かんたん・ふつう・むずかしい
	int diffColor;         //難易度を表示する色

	Keyboard keyboard;

	CountDown countdown;

	Scoreboard scoreboard;

	ChalkEffect chalk;
public:
	WordTypingScene();

	~WordTypingScene();
	// 毎フレーム呼ばれる更新処理
	void Update()override;

	// 画面描画処理
	void Draw()override;
};

