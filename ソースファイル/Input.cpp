#include "Input.h"
#include "DxLib.h"

//staticメンバ変数
int Input::nowSpace = 0;
int Input::nowUp = 0;
int Input::nowDown = 0;
int Input::nowShift = 0;

int Input::prevSpace = 0;
int Input::prevUp = 0;
int Input::prevDown = 0;
int Input::prevShift = 0;


void Input::Update()
{
	// 前フレームの値を保存
	prevSpace = nowSpace;
	prevUp = nowUp;
	prevDown = nowDown;
	prevShift = nowShift;

	// 今の入力を保存
	nowSpace = CheckHitKey(KEY_INPUT_SPACE);
	nowUp = CheckHitKey(KEY_INPUT_UP);
	nowDown = CheckHitKey(KEY_INPUT_DOWN);
	nowShift = CheckHitKey(KEY_INPUT_LSHIFT);
}

bool Input::IsTriggerSpace()
{
	return nowSpace && !prevSpace;
}

bool Input::IsTriggerUp()
{
	return nowUp && !prevUp;
}

bool Input::IsTriggerDown()
{
	return nowDown && !prevDown;
}

bool Input::IsTriggerShift()
{
	return nowShift && !prevShift;
}
