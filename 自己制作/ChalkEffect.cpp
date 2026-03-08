#include "ChalkEffect.h"
#include "DxLib.h"
#include <cstdlib>

ChalkEffect::ChalkEffect()
{
	//chalkdust‚Ì‰Šú‰»
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		chalkdust[i].life = 0;
	}
}

void ChalkEffect::Spawn(float x, float y)
{
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		chalkdust[i].x = x;
		chalkdust[i].y = y;

		chalkdust[i].vx = (rand() % 7 - 3) * 0.3f;
		chalkdust[i].vy = (rand() % 5) * 0.5f;

		chalkdust[i].life = 30;
	}
}

void ChalkEffect::Update()
{
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		if (chalkdust[i].life > 0)
		{
			chalkdust[i].x += chalkdust[i].vx;
			chalkdust[i].y += chalkdust[i].vy;

			//d—Í
			chalkdust[i].vy += 0.05f;

			chalkdust[i].life--;
		}
	}
}

void ChalkEffect::Draw()
{
	for (int i = 0; i < MAX_CHALKDUST; i++)
	{
		if (chalkdust[i].life > 0)
		{
			DrawCircle((int)chalkdust[i].x, (int)chalkdust[i].y, 1, GetColor(240, 240, 240), TRUE);
		}
	}
}
