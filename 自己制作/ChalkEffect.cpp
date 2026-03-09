#include "ChalkEffect.h"
#include "DxLib.h"
#include <cstdlib>

ChalkEffect::ChalkEffect()
{
	//チョークの粉を初期化
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		chalkdust[i].life = 0; // life = 0 は粉が出ていない状態
	}
}

void ChalkEffect::Spawn(float x, float y)
{
	// チョーク粉を発生させる処理
	// 一度に15粒の粉を作る
	for (int i = 0; i < 15; i++) 
	{
		// 使用する粉の番号をランダムに決める
		int id = rand() % MAX_CHALKDUST;

		// 粉の位置を設定
		// 発生位置(x,y)から少しだけランダムにずらす
		chalkdust[id].x = x + rand() % 6 - 3;
		chalkdust[id].y = y + rand() % 6 - 3;

		// 横方向の速度
		// 左右ランダムに飛ばす
		chalkdust[id].vx = (rand() % 7 - 3) * 0.2f;

		// 縦方向の速度
		// 少し下方向に動く
		chalkdust[id].vy = (rand() % 4) * 0.4f;

		// 粉の寿命（フレーム数）
		// 25～39フレームで消える
		chalkdust[id].life = 25 + rand() % 15;
	}
}

void ChalkEffect::Update()
{
	// チョーク粉を更新
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		// すべてのチョーク粉を更新
		if (chalkdust[i].life > 0)
		{
			// 速度を使って位置を移動
			chalkdust[i].x += chalkdust[i].vx;
			chalkdust[i].y += chalkdust[i].vy;

			//空気抵抗
			chalkdust[i].vx *= 0.98f;

			//重力
			chalkdust[i].vy += 0.05f;

			// 寿命を1フレーム減らす
			chalkdust[i].life--;
		}
	}
}

void ChalkEffect::Draw()
{
	// チョーク粉を描画
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		if (chalkdust[i].life > 0)
		{
			// lifeが少なくなるほど薄くなる
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, chalkdust[i].life * 9);

			// 粉を小さい円として描画
			DrawCircle((int)chalkdust[i].x, (int)chalkdust[i].y, 1, GetColor(240, 240, 240), TRUE);
		}
	}

	// 描画設定を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
