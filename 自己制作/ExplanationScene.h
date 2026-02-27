#pragma once
#include "Scene.h"
class ExplanationScene:public Scene
{
private:
	//====== ”wŒi‰æ‘œ ======
	int otherGameImage;
	int screenW;
	int screenH;

	//“ü—ÍŠÇ—
	bool prevEnter;
	bool nowEnter;

public:
	ExplanationScene();
	~ExplanationScene();
	void Update() override;
	void Draw() override;
};

