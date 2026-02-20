#pragma once
#include "DxLib.h"
#include "Scene.h"

//タイトル用シーン
class TitleScene :public Scene
{
private:
	int titleImage;  //タイトル画像
	int screenW;
	int screenH;
public:
	//コンストラクタ
	TitleScene();

	//デストラクタ
	~TitleScene();

	// 毎フレーム呼ばれる更新処理
	void Update()override;

	// 画面描画処理
	void Draw()override;
};

