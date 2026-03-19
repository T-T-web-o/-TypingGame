#include "Scoreboard.h"
#include "DxLib.h"

//============================================================
// 描画用定数
//============================================================

const int TITLE_X = 35;        // タイトルのX座標
const int TITLE_Y = 10;        // タイトルのY座標

const int RANK_TEXT_X = 20;    // ランク表示のX座標
const int RANK_TEXT_Y = 50;    // ランク表示のY座標
const int RANK_TEXT_SPACE = 30;// ランク同士の間隔
const int CONDITION_OFFSET = 30; //ランクと条件の間隔

const int TEXT_COLOR = GetColor(230, 230, 230);  //白

//============================================================
// ランク表示用データ
//============================================================
const TCHAR* rankText[] =
{
    TEXT("SS"),
    TEXT("S"),
    TEXT("A"),
    TEXT("B"),
    TEXT("C"),
    TEXT("D")
};

const TCHAR* rankCondition[] =
{
    TEXT(": 30+ミス0"),
    TEXT(": 30"),
    TEXT(": 25"),
    TEXT(": 20"),
    TEXT(": 15"),
    TEXT(": 15未満")
};

const int rankColor[] =
{
    GetColor(0, 0, 0),       // 黒
    GetColor(0, 0, 255),     // 青
    GetColor(255, 255, 0),   // 黄
    GetColor(255, 0, 0),     // 赤
    GetColor(0, 255, 0),     // 緑
    GetColor(0, 255, 255)    // 水
};

// rankText配列の要素数を計算
const int RANK_COUNT = sizeof(rankText) / sizeof(rankText[0]);

//============================================================
// スコアボード描画処理
// ランクの基準表を画面に表示する
// x, y : 表示位置
//============================================================

void Scoreboard::Draw(int x, int y)
{

    // ボードサイズ
    int width = 150;
    int height = 240;

    // 枠の描画
    DrawBox(x, y, x + width, y + height, TEXT_COLOR, FALSE);
    DrawBox(x + 1, y + 1, x + width - 1, y + height - 1, TEXT_COLOR, FALSE);

    SetFontSize(18);

    // タイトル表示
    DrawString(x + TITLE_X, y + TITLE_Y, TEXT("SCORE"), TEXT_COLOR);

    // ランク基準表表示
    for (int i = 0; i < RANK_COUNT; i++)
    {
        int yPos = RANK_TEXT_Y + RANK_TEXT_SPACE * i;

        //ランク文字
        DrawString(x + RANK_TEXT_X, y + yPos , rankText[i], rankColor[i]);

        //ランク条件
        DrawString(x + RANK_TEXT_X + CONDITION_OFFSET, y + yPos , rankCondition[i], TEXT_COLOR);
    }
}
