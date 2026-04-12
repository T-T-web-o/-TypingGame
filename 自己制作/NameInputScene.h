#pragma once
#include "Scene.h"
#include <tchar.h>

class NameInputScene : public Scene
{
private:
	//------------------------------------------------------------
	// 背景画像
	//------------------------------------------------------------
	int NameInputImage;
	int screenW;    //画面幅
	int screenH;    //画面高さ

	TCHAR name[16];
	int length;

	char keyNow[256];
	char keyOld[256];
public:
	NameInputScene();

	void Update() override;
	void Draw() override;
};

