#pragma once
#include "Scene.h"

// どの選択段階にいるかを管理するための列挙型
enum SelectState
{
	SELECT_GAME,        //ゲームの種類選択状態
	SELECT_DIFFICULTY,   //ゲームの難易度選択状態
	SELECT_MODE
};

//モード選択用シーン
class SelectScene:public Scene
{
private:
	// 現在の選択状態（ゲーム選択中か、難易度選択中か）
	SelectState state;

	int selectImage; //背景画像ハンドル
	int screenW;
	int screenH;

	//選択中の番号
	int cursor;
	int maxcursor;

	//入力管理
    bool prevSpace;
	bool nowSpace;
	bool prevUp;
	bool nowUp;
	bool prevDown;
	bool nowDown;

public:
	// 初期状態（SELECT_GAME など）を設定するために使用
	SelectScene();

	//デストラクタ
	~SelectScene();
	
	// 毎フレーム呼ばれる更新処理
	void Update()override;

	// 画面描画処理
	void Draw()override;
};

