#pragma once
#include "Scene.h"
#include <tchar.h>

// 入力状態の管理
enum InputState
{ 
	STATE_INPUT,    // 入力中の状態
	STATE_CONFIRM   // 入力内容の確認状態 　
};

// 名前入力シーン
class NameInputScene : public Scene
{
private:
	//------------------------------------------------------------
	// 背景画像
	//------------------------------------------------------------
	int NameInputImage;
	int screenW;    //画面幅
	int screenH;    //画面高さ

	// 名前のデータ
	TCHAR name[16]; //　入力された名前
	int length;     //  名前の長さ

	InputState state; // 現在の入力状態(入力中 or 確認中)

	bool isDuplicate; // 同じ名前が存在するか

	// キー入力管理
	char keyNow[256];
	char keyOld[256];

public:
	NameInputScene();

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;
};

