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

	void setTimeTaken(double dt);
	double getTimeTaken(void);

	//SHOPPER FUNCTIONS
	void setShopperScoreSucceed(double dt, int moneyLeft);
	int getShopperScoreSucceed(void);

	void setShopperScoreFailed(double dt, int moneyNeeded);
	int getShopperScoreFailed(void);

	void setShopperHighScore(int score);
	int getShopperHighScore(void);

	//GUARD FUNCTIONS
	void setGuardScoreSucceed(double dt);
	int getGuardScoreSucceed(void);

	void setGuardHighScore(int score);
	int getGuardHighScore(void);

	//VILLAIN FUNCTIONS
	void setVillainScoreSucceed(double dt);
	int getVillainScoreSucceed(void);

	void setVillainScoreFailed(int destroyedOBJ);
	int getVillainScoreFailed(void);

	void setVillainHighScore(int score);
	int getVillainHighScore(void);

private:


};

