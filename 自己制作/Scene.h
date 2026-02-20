#pragma once

// 全シーンの基底クラス（インターフェース）
// タイトル・ゲーム・リザルトなど、すべてのシーンはこのクラスを継承する
class Scene
{
public:
	// 仮想デストラクタ
	// 派生クラスを delete したときに正しく解放されるようにするため
	virtual ~Scene(){}

	// 毎フレーム呼ばれる更新処理
	virtual void Update() = 0;

	// 画面描画処理
	virtual void Draw() = 0;
};

