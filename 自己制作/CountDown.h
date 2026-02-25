#pragma once
class CountDown
{
private:
	enum GameState
	{
		WAIT_START,   // スペース待ち
		COUNTDOWN,    // 3,2,1
		END
	};
	//現在の状況
	GameState state;
	int countdownTimer;
public:
	CountDown();

	void Update();
	void Draw(int x, int y);

	bool IsFinished() const;
};

