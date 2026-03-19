#include "PracticeTypingScene_1.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "ResultScene.h"
#include "KeyTable.h"
#include "Scoreboard.h"
#include "ChalkEffect.h"
#include <cstdlib>

//============================================================
// 描画用定数
//============================================================

const int UI_X = 10;         // UIのX座標
const int UI_START_Y = 10;   // UIの開始Y座標
const int UI_SPACE = 30;     // UI同士の間隔

const int TYPING_WORD_X = 300;  // タイピング文字のX座標
const int TYPING_WORD_Y = 200;  // タイピング文字のY座標

const int END_TEXT_X = 550;  // 終了案内のX座標
const int END_TEXT_Y = 430;  // 終了案内のY座標

const int SCOREBOARD_X = 480; // スコアボードのX座標
const int SCOREBOARD_Y = 10;  // スコアボードのY座標

const int KEYBOARD_X = 100;    // キーボード描画のX座標
const int KEYBOARD_Y = 300;    // キーボード描画のY座標

const int COLOR_TEXT = GetColor(230, 230, 230);  //白
const int COLOR_MISS = GetColor(255, 0, 0);        //赤

//============================================================
// コンストラクタ
//============================================================
PracticeTypingScene_1::PracticeTypingScene_1()
{
    //画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    //背景画像読み込み
    gameImage = LoadGraph(TEXT("Resource/blackboard.png"));

    // 最初のターゲット文字をランダムで決定
	target = 'A' + rand() % 26;

    // スコア・ミス数の初期化
	score = 0;
	miss = 0;
    combo = 0;
    maxCombo = 0;

    // ミス
    missTimer = 0;
    missKey = '\0';

    // キー入力状態初期化
    memset(keyNow, 0, sizeof(keyNow));
    memset(keyOld, 0, sizeof(keyOld));
}

//============================================================
// デストラクタ
//============================================================
PracticeTypingScene_1::~PracticeTypingScene_1()
{
    DeleteGraph(gameImage);
}

//============================================================
// 更新処理
//============================================================
void PracticeTypingScene_1::Update()
{
    // チョークエフェクト更新
    chalk.Update();

    // Tabキーでリザルト画面へ
    if (CheckHitKey(KEY_INPUT_TAB))
    {
        GameManager::GetInstance().ChangeScene(new ResultScene(score, miss,maxCombo));
        return;
    }

    // 現在のキー状態取得
    GetHitKeyStateAll(keyNow);

    // A～Zのキー入力判定
    for (int i = 0; i < 26; i++)
    {
        // 押された瞬間だけ判定
        if (keyNow[keyTable[i]] && !keyOld[keyTable[i]])
        {
            //キーを文字に変換
            char inputChar = 'A' + i;

            // タイピング音
            PlaySoundMem(SoundManager::typeSE, DX_PLAYTYPE_BACK);

            //正解
            if (inputChar == target)
            {   
                // チョークエフェクト
                chalk.Spawn(320, 240);

                score++;
                combo++;

                if (combo > maxCombo) {
                    maxCombo = combo;
                }
                // 次のターゲット文字をランダムに生成
                target = 'A' + rand() % 26;
            }
            else
            {
                //ミス
                miss++;
                combo = 0;
                missTimer = 20;
                missKey = inputChar;
            }
            break;
        }
    }
    // 前フレームのキー状態保存
    memcpy(keyOld, keyNow, sizeof(keyNow));

    // ミス表示タイマー
    if (missTimer > 0)
    {
        missTimer--;
    }
    else
    {
        missKey = '\0';
    }
}

//============================================================
// 描画処理
//============================================================
void PracticeTypingScene_1::Draw()
{
    //背景画像を画面全体に表示
    DrawExtendGraph(0, 0, screenW, screenH, gameImage, TRUE);

    // 入力対象文字の表示（ミス時は赤表示）
    SetFontSize(50);

    //通常時　（白）
    int color = COLOR_TEXT;

    if (missTimer > 0)
    {
        //入力ミス（赤）
        color = COLOR_MISS;
    }

    DrawFormatString(TYPING_WORD_X, TYPING_WORD_Y, color, TEXT("%c"), target);
	

    SetFontSize(23);
    // スコア表示
    DrawFormatString(UI_X, UI_START_Y, COLOR_TEXT, TEXT("スコア:%d"), score);
    
    // タイプミス数の表示
    DrawFormatString(UI_X, UI_START_Y + UI_SPACE, COLOR_TEXT, TEXT("ミス:%d"), miss);

    // コンボ表示
    DrawFormatString(UI_X, UI_START_Y + UI_SPACE * 2, COLOR_TEXT, TEXT("コンボ：%d"), combo);

    SetFontSize(16);
    // 終了案内
    DrawString(END_TEXT_X, END_TEXT_Y, TEXT("Tabで終了"), COLOR_TEXT);

    // スコアボード表示
    scoreboard.Draw(SCOREBOARD_X, SCOREBOARD_Y);

    // キーボード表示
    keyboard.Draw(target,missKey, KEYBOARD_X, KEYBOARD_Y);

    // チョーク粉エフェクト表示
    chalk.Draw();
}

