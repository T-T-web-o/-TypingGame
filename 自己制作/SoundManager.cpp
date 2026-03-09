#include "SoundManager.h"
#include "DxLib.h"

int SoundManager::titleSE;
int SoundManager::typeSE;
int SoundManager::selectSE;

void SoundManager::Load()
{
	typeSE = LoadSoundMem(TEXT("Resource/type.mp3"));
	titleSE = LoadSoundMem(TEXT("Resource/Decision.mp3"));
	selectSE = LoadSoundMem(TEXT("Resource/Selection.mp3"));
}

void SoundManager::Release()
{
	DeleteSoundMem(typeSE);
	DeleteSoundMem(titleSE);
	DeleteSoundMem(selectSE);
}
