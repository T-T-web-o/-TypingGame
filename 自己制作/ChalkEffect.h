#pragma once
#include "DxLib.h"

struct ChalkDust
{
    float x;
    float y;
    float vx;
    float vy;
    int life;
};

class ChalkEffect
{
private:
    static const int MAX_CHALKDUST = 30;
    ChalkDust chalkdust[MAX_CHALKDUST];

public:
    ChalkEffect();

    void Spawn(float x, float y);

    void Update();

    void Draw();
};

