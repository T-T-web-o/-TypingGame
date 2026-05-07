#include "ExplanationScene.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "SelectScene.h"
#include "NameInputScene.h"
#include "DxLib.h"

//============================================================
// 描画用定数
//============================================================

const int GUIDE_TITLE_X = 260;             // 「ゲーム説明」タイトルのX座標
const int GUIDE_TITLE_Y = 10;              // 「ゲーム説明」タイトルのY座標

const int GUIDE_TEXT_X = 100;              // 説明文のX座標
const int GUIDE_TEXT_Y = 40;               // 説明文のY座標

const int CONTROL_TEXT_X = 20;             // 操作説明のX座標
const int CONTROL_TEXT_Y_START = 80;       // 操作説明のY座標
const int CONTROL_TEXT_SPACE = 30;         // 操作説明同士の間隔

const int MODE_TEXT_X = 300;               // モード一覧のX座標
const int MODE_TEXT_Y_START = 80;          // モード一覧のY座標
const int MODE_TEXT_SPACE = 30;            // モード一覧同士の間隔

const int MODE_DESC_TITLE_X = 20;          // モードタイトルのX座標
const int MODE_DESC_TITLE_Y_START = 220;   // モードタイトルのY座標
const int MODE_DESC_TITLE_SPACE = 70;      // モード同士の間隔

const int MODE_DESC_TEXT_X = 40;           // モード説明文のX座標
const int MODE_DESC_TEXT_Y_OFFSET = 30;    // タイトルからの縦オフセット

const int START_TEXT_X = 460;              // 「Enterでスタート」のX座標
const int START_TEXT_Y = 430;              // 「Enterでスタート」のY座標

const int COLOR_TEXT = GetColor(240, 240, 240);    // 白
const int COLOR_BLUE = GetColor(80, 160, 220);     // 青
const int COLOR_YELLOW = GetColor(240, 220, 120);  // 黄
const int COLOR_GREEN = GetColor(170, 255, 170);   // 緑

// 操作説明テキス
const TCHAR* controlText[] =
{
	TEXT("[操作説明]"),             // タイトル
	TEXT("Enter:ゲームスタート"),   // Enterで開始
	TEXT("Space:選択"),             // Spaceで選択
	TEXT("Tab:ゲーム終了")          // Tabで終了
};

// 操作説明の文字色
const int controlColor[] =
{
	COLOR_BLUE,     // タイトルは青青
	COLOR_GREEN,    // 以下は緑
	COLOR_GREEN,    
	COLOR_GREEN     
};

// 配列の要素数を自動で取得
const int CONTROL_COUNT = sizeof(controlText) / sizeof(controlText[0]);

// ゲームモード一覧
const TCHAR* modeText[] =
{
	TEXT("[ゲームモード]"),                   // タイトル
	TEXT("・一文字タイピング練習"),           // モード１
	TEXT("・アルファベットタイピング練習"),   // モード２
	TEXT("・単語タイピング")                  // モード３
};

// モード一覧の数
const int MODE_COUNT = sizeof(modeText) / sizeof(modeText[0]);

// モードタイトル
const TCHAR* modeTitle[] =
{
	TEXT("・一文字タイピング練習"),           
	TEXT("・アルファベットタイピング練習"),   
	TEXT("・単語タイピング")                 
};

// モードタイトル数
const int MODE_DESC_COUNT = sizeof(modeTitle) / sizeof(modeTitle[0]);

// 各モードの説明
const TCHAR* modeDesc[] =
{
	TEXT("ひらがなをローマ字で入力する基本練習モード"),     // モード１の説明
	TEXT("A～Zをタイピングしてキーボード操作に慣れよう"),   // モード２の説明
	TEXT("英単語を素早く入力してスコアとコンボを伸ばそう")  // モード３の説明
};


//============================================================
// コンストラクタ（説明画面の初期化）
//============================================================
ExplanationScene::ExplanationScene()
{
	// 画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	//背景画像(黒板)読み込み
	ExplanationImage = LoadGraph(TEXT("Resource/blackboard.png"));

}


//============================================================
// デストラクタ（使用した画像の解放）
//============================================================
ExplanationScene::~ExplanationScene()
{
	DeleteGraph(ExplanationImage);
}

//============================================================
// 説明画面の更新処理
//============================================================
void ExplanationScene::Update()
{
	//ENTERキーの入力状況を取得
	nowEnter = CheckHitKey(KEY_INPUT_RETURN);

	
	// ENTERキーが押されたら
	if (nowEnter && !prevEnter)
	{
		//効果音再生
		PlaySoundMem(SoundManager::titleSE, DX_PLAYTYPE_BACK);

		// ゲーム選択シーンに切り替え
		GameManager::GetInstance().ChangeScene(new NameInputScene());
	}
	// 前フレームの入力状態を保存
	prevEnter = nowEnter;
}

//============================================================
// 説明画面の描画処理
//============================================================
void ExplanationScene::Draw()
{
	//背景画像を画面全体に表示
	SetFontSize(20);
	DrawExtendGraph(0, 0, screenW, screenH, ExplanationImage, TRUE);

	// ゲーム説明
	DrawString(GUIDE_TITLE_X, GUIDE_TITLE_Y, TEXT("ゲーム説明"), GetColor(255, 220, 100));

	DrawString(GUIDE_TEXT_X, GUIDE_TEXT_Y, TEXT("表示された文字を正しくタイピングしよう！"), COLOR_TEXT);

	// 操作説明
	for (int i = 0; i < CONTROL_COUNT; i++)
	{
		DrawString(CONTROL_TEXT_X, CONTROL_TEXT_Y_START + CONTROL_TEXT_SPACE * i, controlText[i], controlColor[i]);
	}

	// ゲーム紹介
	for (int i = 0; i < MODE_COUNT; i++)
	{
		DrawString(MODE_TEXT_X,MODE_TEXT_Y_START + MODE_TEXT_SPACE * i,modeText[i],(i == 0) ? COLOR_BLUE : COLOR_TEXT);
	}

	// 各モードの説明
	for (int i = 0; i < MODE_DESC_COUNT; i++)
	{
		int y = MODE_DESC_TITLE_Y_START + MODE_DESC_TITLE_SPACE * i;

		DrawString(MODE_DESC_TITLE_X, y, modeTitle[i], COLOR_YELLOW);

		DrawString(MODE_DESC_TEXT_X, y + MODE_DESC_TEXT_Y_OFFSET, modeDesc[i], COLOR_TEXT);
	}

	//  スタート案内
	DrawString(START_TEXT_X, START_TEXT_Y, TEXT("Enterでスタート"), GetColor(230, 230, 230));
	
}
