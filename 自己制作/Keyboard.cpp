#include "Keyboard.h"

//============================================================
// キーボードの描画処理
// target で指定されたキーをハイライト表示する
//
// target  : 強調表示するキー
// startX  : キーボード左上のX座標
// startY  : キーボード左上のY座標
//============================================================
void Keyboard::Draw(TCHAR target, int startX, int startY)
{
    //一つのキーのサイズ
    const int KEY_SIZE = 40;

    //キー同士の間隔
    const int KEY_GAP = 5;

    //------------------------------------------------------------
    // 1行目：Q W E R T Y U I O P
    //------------------------------------------------------------
    for (int i = 0; i < 10; i++)
    {
        // 横位置
        int x = startX + i * (KEY_SIZE + KEY_GAP);
     
        // 縦位置
        int y = startY;

        // target と同じキーなら赤でハイライト
        int color = (row1[i] == target)
            ? GetColor(255, 120, 120)    //強調表示 (赤)
            : GetColor(240, 240, 240);   //通常キー (白)

        // キー枠の描画
        DrawBox(x, y, x + KEY_SIZE, y + KEY_SIZE, color, FALSE);
        DrawBox(x + 1, y + 1, x + KEY_SIZE - 1, y + KEY_SIZE - 1, color, FALSE);

        // キー文字を作成
        TCHAR str[2] = { row1[i], '\0' };

        // キー中央に文字を描画
        DrawString(x + KEY_SIZE / 2 - 5, y + KEY_SIZE / 2 - 5,str,GetColor(240, 240, 240));
    }

    //------------------------------------------------------------
    // 2行目：A S D F G H J K L
    // 本物のキーボードに近づけるため少し右にずらす
    //------------------------------------------------------------
    for (int i = 0; i < 9; i++)
    {
        // 横位置（+20）
        int x = startX + 20 + i * (KEY_SIZE + KEY_GAP);

        // 縦位置（1段下)
        int y = startY + KEY_SIZE + KEY_GAP;

        int color = (row2[i] == target)
            ? GetColor(255, 120, 120)
            : GetColor(240, 240, 240);

        DrawBox(x, y, x + KEY_SIZE, y + KEY_SIZE, color, FALSE);
        DrawBox(x + 1, y + 1, x + KEY_SIZE - 1, y + KEY_SIZE - 1, color, FALSE);

        TCHAR str[2] = { row2[i], '\0' };

        DrawString(x + KEY_SIZE / 2 - 5, y + KEY_SIZE / 2 - 5,str,GetColor(240, 240, 240));
    }

    //------------------------------------------------------------
    // 3行目：Z X C V B N M
    // さらに右へずらす
    //------------------------------------------------------------
    for (int i = 0; i < 7; i++)
    {
        // 横位置（+50）
        int x = startX + 50 + i * (KEY_SIZE + KEY_GAP);

        // 縦位置（2段下）
        int y = startY + (KEY_SIZE + KEY_GAP) * 2;

        int color = (row3[i] == target)
            ? GetColor(255, 120, 120)
            : GetColor(240, 240, 240);

        DrawBox(x, y, x + KEY_SIZE, y + KEY_SIZE, color, FALSE);
        DrawBox(x + 1, y + 1, x + KEY_SIZE - 1, y + KEY_SIZE - 1, color, FALSE);

        TCHAR str[2] = { row3[i], '\0' };

        DrawString(x + KEY_SIZE / 2 - 5 ,y + KEY_SIZE / 2 - 5,str,GetColor(240, 240, 240));
    }
  
}
