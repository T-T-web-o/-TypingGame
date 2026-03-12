#include "PracticeTypingScene_1.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "ResultScene.h"
#include "KeyTable.h"
#include "Scoreboard.h"
#include "ChalkEffect.h"
#include <cstdlib>

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

    // 現在入力すべき文字を画面中央に表示・入力ミスをした文字を赤く表示
    SetFontSize(50);

    //通常時　（白）
    int color = GetColor(240, 240, 240);

    if (missTimer > 0)
    {
        //入力ミス（赤）
        color = GetColor(255, 0, 0);
    }

    DrawFormatString(300, 200, color, TEXT("%c"), target);
	

    SetFontSize(23);
    //------------------------------------------------------------
    // スコア表示
    //------------------------------------------------------------
    DrawFormatString(10, 10, GetColor(240, 240, 240), TEXT("スコア:%d"), score);

    //------------------------------------------------------------
    // タイプミス数の表示
    //------------------------------------------------------------
    DrawFormatString(10, 40, GetColor(240, 240, 240), TEXT("ミス:%d"), miss);

    //------------------------------------------------------------
    // コンボ表示
    //------------------------------------------------------------
    DrawFormatString(10, 70, GetColor(240, 240, 240), TEXT("コンボ：%d"), combo);

    SetFontSize(16);
    //------------------------------------------------------------
    // 終了案内
    //------------------------------------------------------------
    DrawString(550, 430, TEXT("Tabで終了"), GetColor(240, 240, 240));

    // スコアボード表示
    scoreboard.Draw(480, 10);

    // キーボード表示
    keyboard.Draw(target,missKey, 100, 300);

    // チョーク粉エフェクト表示
    chalk.Draw();
}

