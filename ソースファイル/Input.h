#pragma once

class Input
{
private:
	// Œ»İ‚Ì“ü—Íó‘Ô
	static int nowSpace;
    static int nowUp;
	static int nowDown;
	static int nowShift;
	static int nowEsc;

	// ‘O‚Ì“ü—Íó‘Ô
	static int prevSpace;
	static int prevUp;
	static int prevDown;
	static int prevShift;
	static int prevEsc;
public:
	static void Update();

	// ‰Ÿ‚µ‚½uŠÔ
	static bool IsTriggerSpace();
	static bool IsTriggerUp();
	static bool IsTriggerDown();
	static bool IsTriggerShift();
	static bool IsTriggerEsc();
};

