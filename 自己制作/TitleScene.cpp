#include "TitleScene.h"
#include "DxLib.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "PracticeTypingScene_1.h"
#include "SelectScene.h"
#include "ExplanationScene.h"

//============================================================
// 描画用定数
//============================================================

const int START_TEXT_X = 430;    // スタートテキストのX座標
const int START_TEXT_Y = 420;    // スタートテキストのY座標
const int START_FONT_SIZE = 23;  // スタートテキストのフォントサイズ

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

	SetFontSize(START_FONT_SIZE);
	//------------------------------------------------------------
	// スタート案内
	//------------------------------------------------------------
	DrawString(START_TEXT_X, START_TEXT_Y, TEXT("Enterでスタート"), GetColor(230, 230, 230));
}


