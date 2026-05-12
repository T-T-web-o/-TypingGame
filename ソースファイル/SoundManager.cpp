#include "SoundManager.h"
#include "DxLib.h"

//============================================================
// 静的メンバ変数定義
// 各SEのハンドルを保持する
//============================================================
int SoundManager::titleSE;
int SoundManager::typeSE;
int SoundManager::selectSE;

//============================================================
// サウンド読み込み処理
//============================================================
void SoundManager::Load()
{
	typeSE = LoadSoundMem(TEXT("Resource/type.mp3"));
	titleSE = LoadSoundMem(TEXT("Resource/Title.mp3"));
	selectSE = LoadSoundMem(TEXT("Resource/Select.mp3"));
}

//============================================================
// サウンド解放処理
//============================================================
void SoundManager::Release()
{
	DeleteSoundMem(typeSE);
	DeleteSoundMem(titleSE);
	DeleteSoundMem(selectSE);
}
