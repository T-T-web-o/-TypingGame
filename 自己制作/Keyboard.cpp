#include "Keyboard.h"

// target で指定されたキーを赤くハイライトして描画する関数
// startX, startY はキーボード全体の左上座標
void Keyboard::Draw(TCHAR target, int startX, int startY)
{
    int keySize = 40; //一つのキーの大きさ
    int gap = 5;      //キーとキーの間隔

    //===========================
    // １行目:Q W E R T Y U I O P
    //===========================
    for (int i = 0; i < 10; i++)
    {
        // 横位置：開始位置 + キー幅×（キーサイズ＋キー間隔）
        int x = startX + i * (keySize + gap);

        // 縦位置：1行目なのでそのまま
        int y = startY;

        // target と同じ文字なら赤、それ以外はグレー
        int color = (row1[i] == target)
            ? GetColor(255, 0, 0)        //強調 (赤)
            : GetColor(200, 200, 200);   //普通 (灰色)

        // キーの四角を描画（TRUE = 塗りつぶし）
        DrawBox(x, y, x + keySize, y + keySize, color, TRUE);

        // キーの文字を表示するための文字列を作成
        TCHAR str[2] = { row1[i], '\0' };

        // キー中央あたりに文字を描画
        DrawString(x + keySize / 2 - 8,
            y + keySize / 2 - 8,
            str,
            GetColor(0, 0, 0));
    }

    //========================================
    // 2行目：A S D F G H J K L
    // 少し右にずらして本物のキーボード風にする
    //========================================
    for (int i = 0; i < 9; i++)
    {
        // +20 で右に少しずらしている
        int x = startX + 20 + i * (keySize + gap);

        // 1段下に移動
        int y = startY + keySize + gap;

        int color = (row2[i] == target)
            ? GetColor(255, 0, 0)
            : GetColor(200, 200, 200);

        DrawBox(x, y, x + keySize, y + keySize, color, TRUE);

        TCHAR str[2] = { row2[i], '\0' };
        DrawString(x + keySize / 2 - 8,
            y + keySize / 2 - 8,
            str,
            GetColor(0, 0, 0));
    }

    //========================
    // 3行目：Z X C V B N M
    // さらに右にずらす
    //========================
    for (int i = 0; i < 7; i++)
    {
        // +50 でさらに右へずらす
        int x = startX + 50 + i * (keySize + gap);

        // 2段下へ移動
        int y = startY + (keySize + gap) * 2;

        int color = (row3[i] == target)
            ? GetColor(255, 0, 0)
            : GetColor(200, 200, 200);

        DrawBox(x, y, x + keySize, y + keySize, color, TRUE);

        TCHAR str[2] = { row3[i], '\0' };
        DrawString(x + keySize / 2 - 8,
            y + keySize / 2 - 8,
            str,
            GetColor(0, 0, 0));
    }
}
