#include "PracticeTypingScene_1.h"
#include "GameManager.h"
#include "ResultScene.h"
#include "KeyTable.h"
#include <cstdlib>


//コンストラクタ
PracticeTypingScene_1::PracticeTypingScene_1()
{
    //画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    //背景画像読み込み
    gameImage = LoadGraph(TEXT("Resource/game.png"));

    //タイピング音読み込み
    typeSE = LoadSoundMem(TEXT("Resource/type.mp3"));

    // 最初に表示するターゲット文字を A～Z の中からランダムに決定
	target = 'A' + rand() % 26;

    // スコア・ミス数の初期化
	score = 0;
	miss = 0;
    combo = 0;
    maxCombo = 0;

    //押された瞬間のみ反応
    memset(keyNow, 0, sizeof(keyNow));
    memset(keyOld, 0, sizeof(keyOld));
}

PracticeTypingScene_1::~PracticeTypingScene_1()
{
    DeleteGraph(gameImage);
    DeleteSoundMem(typeSE);
}

void PracticeTypingScene_1::Update()
{
    // Tabキーが押されたら結果画面へ遷移
    if (CheckHitKey(KEY_INPUT_TAB))
    {
        GameManager::GetInstance().ChangeScene(new ResultScene(score, miss,maxCombo));
        return;
    }

    // 現在のターゲット文字を配列インデックスに変換
    // 例：'A' → 0, 'B' → 1 ...
    int correctIndex = target - 'A';

    // 現在フレームの全キー状態を取得
    // keyNow に「押されている / 押されていない」を格納する
    GetHitKeyStateAll(keyNow);

    //A～Zのどれが押されたかを判定
    for (int i = 0; i < 26; i++)
    {
        if (keyNow[keyTable[i]] && !keyOld[keyTable[i]])
        {
            PlaySoundMem(typeSE, DX_PLAYTYPE_BACK);

            //正解だったら
            if (i == correctIndex)
            {   
                score++;
                combo++;
                if (combo > maxCombo) {
                    maxCombo = 0;
                }
                // 次のターゲット文字をランダムに生成
                target = 'A' + rand() % 26;
            }
            else
            {
                //ミス
                miss++;
                combo = 0;
            }
            break;
        }
    }
    // 次のフレーム用に入力状態を保存
    memcpy(keyOld, keyNow, sizeof(keyNow));
}

void PracticeTypingScene_1::Draw()
{
    //背景画像を画面全体に表示
    DrawExtendGraph(0, 0, screenW, screenH, gameImage, TRUE);

    // 現在入力すべき文字を画面中央に表示
    SetFontSize(30);
	DrawFormatString(300, 200, GetColor(255, 255, 255),TEXT("%c"), target);

    SetFontSize(16);
    //スコアの表示
    DrawFormatString(100, 140, GetColor(255, 255, 255), TEXT("スコア:%d"), score);          

    //タイピングミス数の表示
    DrawFormatString(100, 160, GetColor(255, 255, 255), TEXT("ミス:%d"), miss);            

    //コンボ表示
    DrawFormatString(100, 180, GetColor(255, 255, 255), TEXT("コンボ：%d"), combo);

    //リザルト画面へ移行表示 
    DrawString(380, 320, TEXT("Tabで終了"), GetColor(230, 230, 230));

    keyboard.Draw(target, 100, 350);
}

