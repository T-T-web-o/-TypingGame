#include "ChalkEffect.h"
#include "DxLib.h"
#include <cstdlib>

//============================================================
// コンストラクタ（初期化）
//============================================================
ChalkEffect::ChalkEffect()
{
	// すべてのチョーク粉を未使用状態にする
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		chalkdust[i].life = 0; // life = 0 は粉が出ていない状態
	}
}

//============================================================
// チョーク粉の発生処理
//============================================================
void ChalkEffect::Spawn(float x, float y)
{
	// 一度に15粒の粉を作る
	for (int i = 0; i < 15; i++) 
	{
		// 使用する粉の番号をランダムに決める
		int id = rand() % MAX_CHALKDUST;

		// 発生位置をランダムにずらす
		chalkdust[id].x = x + rand() % 6 - 3;
		chalkdust[id].y = y + rand() % 6 - 3;

		// 横方向の速度（左右ランダム）
		chalkdust[id].vx = (rand() % 7 - 3) * 0.2f;

		// 縦方向の速度（少し下方向へ）
		chalkdust[id].vy = (rand() % 4) * 0.4f;

		// 粉の寿命（フレーム数）
		// 25～39フレームで消える
		chalkdust[id].life = 25 + rand() % 15;
	}
}

//============================================================
// チョーク粉の更新処理
//============================================================
void ChalkEffect::Update()
{
	// チョーク粉を更新
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		// 存在している粉のみ更新
		if (chalkdust[i].life > 0)
		{
			// 速度に基づいて位置を更新
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

//============================================================
// チョーク粉の描画処理
//============================================================
void ChalkEffect::Draw()
{
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		if (chalkdust[i].life > 0)
		{
			// 寿命が少なくなるほど透明になる
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, chalkdust[i].life * 9);

			// 粉を小さい円として描画
			DrawCircle((int)chalkdust[i].x, (int)chalkdust[i].y, 1, GetColor(240, 240, 240), TRUE);
		}
	}

	// 描画設定を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
