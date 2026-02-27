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
	bool prevSpace;
	bool nowSpace;

public:
	ExplanationScene();
	~ExplanationScene();
	void Update() override;
	void Draw() override;
};

