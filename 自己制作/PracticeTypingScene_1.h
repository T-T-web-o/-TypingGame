#pragma once
#include "DxLib.h"
#include "Scene.h"
#include "Keyboard.h"
#include "Scoreboard.h"
#include "ChalkEffect.h"

// 1文字タイピングゲーム用のシーン
class PracticeTypingScene_1 :public Scene
{
private:
	char target;     // 現在入力対象となっている文字（A～Z）
	int score;       // 正しく入力できた回数
	int miss;        // 間違ったキーを押した回数

	//背景画像
	int gameImage;
	int screenW;
	int screenH;

	//====== 入力管理 ======
	char keyNow[256];        //現在フレームのキー情報
	char keyOld[256];        //前フレームのキー情報

	//キーボード
	Keyboard keyboard;

	//スコアボード
	Scoreboard scoreboard;
	
	//チョークエフェクト
	ChalkEffect chalk;

	//キーボード音
	int typeSE;

	int combo;        // 現在コンボ
	int maxCombo;     // 最大コンボ

public:
	PracticeTypingScene_1();
	~PracticeTypingScene_1();
	void Update()override;// 毎フレーム呼ばれる更新処理
	void Draw()override;  // 画面描画処理

};

