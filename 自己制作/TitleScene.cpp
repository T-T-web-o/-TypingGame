#include "TitleScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "PracticeTypingScene_1.h"
#include "SelectScene.h"
#include "ExplanationScene.h"

//============================================================
// コンストラクタ
// タイトル画面の初期化処理
//============================================================
TitleScene::TitleScene()
{
	//画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//タイトル画像読み込み
	titleImage = LoadGraph(TEXT("Resource/Title.png"));
}

//============================================================
// デストラクタ
//============================================================
TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
}

//============================================================
// 更新処理
//============================================================
void TitleScene::Update()
{
	//------------------------------------------------------------
	// Enterキー入力取得
	//------------------------------------------------------------
	nowEnter = (CheckHitKey(KEY_INPUT_RETURN));

	// Enterキーが押されたか判定
	if (nowEnter && !prevEnter)
	{
		// 決定音を再生
		PlaySoundMem(SoundManager::titleSE, DX_PLAYTYPE_BACK);

		// 説明画面へシーン切り替え
		GameManager::GetInstance().ChangeScene(new ExplanationScene());
	}
	// 前フレームの入力を保存
	prevEnter = nowEnter;
}

//============================================================
// 描画処理
//============================================================
void TitleScene::Draw()
{
	//背景画像を画面全体に表示
	DrawExtendGraph(0, 0,screenW, screenH,titleImage,TRUE);

	SetFontSize(23);
	//------------------------------------------------------------
	// スタート案内
	//------------------------------------------------------------
	DrawString(430, 420, TEXT("Enterでスタート"), GetColor(230, 230, 230));
}


