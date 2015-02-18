#pragma once

#include "Vector3.h"
#include "Application.h"

class CPlayer
{
private:
	Vector3 position;
	int score;
	int money;
	int highScore;
	double timeTaken;

public:
	CPlayer(void);
	~CPlayer(void);
	
	//COMMON FUNCTIONS
	void setPos(Vector3 Pos);
	Vector3 getPos(void);

	void setHighScore(int score);

	void setTimeTaken(double dt);
	double getTimeTaken(void);

	//SHOPPER FUNCTIONS
	void setShopperScoreSucceed(double dt, int moneyLeft);
	int getShopperScoreSucceed(void);

	void setShopperScoreFailed(double dt, int moneyNeeded);
	int getShopperScoreFailed(void);

	void setShopperMoney(int a);
	int getShopperMoney(void);

	//GUARD FUNCTIONS
	void setGuardScoreSucceed(double dt);
	int getGuardScoreSucceed(void);

	void setGuardScoreFailed(double dt);
	int getGuardScoreFailed(void);

	//VILLAIN FUNCTIONS
	void setVillainScoreSucceed(double dt);
	int getVillainScoreSucceed(void);

	void setVillainScoreFailed(int destroyedOBJ);
	int getVillainScoreFailed(void);

private:


};

