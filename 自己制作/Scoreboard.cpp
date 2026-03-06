#include "Scoreboard.h"
#include "DxLib.h"

void Scoreboard::Draw(int x, int y)
{
	int width = 150;
	int height = 240;

	DrawBox(x, y, x + width, y + height, GetColor(240, 240, 240), FALSE);
	DrawBox(x + 1, y + 1, x + width - 1, y + height - 1, GetColor(240, 240, 240), FALSE);

    SetFontSize(18);

    // タイトル
    DrawString(x + 35, y + 10, TEXT("SCORE"), GetColor(240, 240, 240));

    // ランク表
    DrawString(x + 20, y + 50, TEXT("SS: 30+ミス0"), GetColor(240, 240, 240));
    DrawString(x + 20, y + 80, TEXT("S : 30"), GetColor(240, 240, 240));
    DrawString(x + 20, y + 110, TEXT("A : 25"), GetColor(240, 240, 240));
    DrawString(x + 20, y + 140, TEXT("B : 20"), GetColor(240, 240, 240));
    DrawString(x + 20, y + 170, TEXT("C : 15"), GetColor(240, 240, 240));
    DrawString(x + 20, y + 200, TEXT("D : 15未満"), GetColor(240, 240, 240));
}
