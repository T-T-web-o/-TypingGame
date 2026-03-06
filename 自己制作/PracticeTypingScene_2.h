#pragma once
#include "Scene.h"
#include "Keyboard.h"
#include "CountDown.h"
#include "Scoreboard.h"

struct WordData_2
{
	const TCHAR* display; // 表示用（日本語）
	const TCHAR* input;   // 判定用（ローマ字）
};

class PracticeTypingScene_2:public Scene
{
private:
	
	WordData_2 currentWord;    //現在の単語
	WordData_2* wordList;      //単語リスト

	int kanaIndex;           //現在どの文字なのかを保存する変数
	int charIndex;           //単語を何文字目まで入力したかを保存する変数

	//====== 内部処理 =====
	void TypingUpdate();

	//====== スコア管理 ======
	int score;               //スコア
	int miss;                //ミス

	//====== 入力管理 ======
	char keyNow[256];        //現在フレームのキー情報
	char keyOld[256];        //前フレームのキー情報

	//====== 背景画像 ======
	int gameImage;
	int screenW;
	int screenH;

	//====== 音======
	int typeSE;

	//====== コンボ管理 ======
	int combo;             // 現在コンボ
	int maxCombo;          // 最大コンボ
	bool missFlag = false; // この単語でミスしたか

	Keyboard keyboard;

	CountDown countdown;

	Scoreboard scoreboard;

public:
	PracticeTypingScene_2();

	~PracticeTypingScene_2();

	// 毎フレーム呼ばれる更新処理
	void Update()override;

	// 画面描画処理
	void Draw()override;
};

