#pragma once
#include "DxLib.h"

class Keyboard
{
private:
	TCHAR row1[10] = { 'Q','W','E','R','T','Y','U','I','O','P' };
	TCHAR row2[9] = { 'A','S','D','F','G','H','J','K','L' };
	TCHAR row3[7] = { 'Z','X','C','V','B','N','M' };
public:
	void Draw(TCHAR target, int startX, int startY);
};

