#pragma once
#include "DxLib.h"

//============================================================
// チョーク粉エフェクト用のデータ構造
//============================================================
struct ChalkDust
{
    float x;   //  X座標
    float y;   //  Y座標
    float vx;  //  X方向の速度
    float vy;  //  Y方向の速度
    int life;  //  寿命（lifeが０になるとチョークの粉が消える）
};

//============================================================
// チョーク粉エフェクト管理クラス
//============================================================
class ChalkEffect
{
private:
    //  同時に表示できる粉の数
    static const int MAX_CHALKDUST = 100;  

    //　チョークの粉の配列
    ChalkDust chalkdust[MAX_CHALKDUST];    

public:
    // コンストラクタ（チョーク粉の初期化）
    ChalkEffect();

    //チョーク粉を発生させる
    void Spawn(float x, float y);

    //チョーク粉の状態を更新
    void Update();

    //チョーク粉の描画
    void Draw();
};

