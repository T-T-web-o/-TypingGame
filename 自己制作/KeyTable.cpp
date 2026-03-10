#include "KeyTable.h"
#include "DxLib.h"

//============================================================
// アルファベット入力判定用キーコードテーブル
//
// DxLib のキーコードを A～Z の順番で格納している
// 例：
// keyTable[0] → Aキー
// keyTable[1] → Bキー
// keyTable[2] → Cキー
// ...
// keyTable[25] → Zキー
//
// 文字とキーコードを対応させることで
// タイピング入力判定を簡単にする
//============================================================
int keyTable[26] = {
   KEY_INPUT_A, KEY_INPUT_B, KEY_INPUT_C, KEY_INPUT_D, KEY_INPUT_E,
   KEY_INPUT_F, KEY_INPUT_G, KEY_INPUT_H, KEY_INPUT_I, KEY_INPUT_J,
   KEY_INPUT_K, KEY_INPUT_L, KEY_INPUT_M, KEY_INPUT_N, KEY_INPUT_O,
   KEY_INPUT_P, KEY_INPUT_Q, KEY_INPUT_R, KEY_INPUT_S, KEY_INPUT_T,
   KEY_INPUT_U, KEY_INPUT_V, KEY_INPUT_W, KEY_INPUT_X, KEY_INPUT_Y, KEY_INPUT_Z
};
