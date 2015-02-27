#pragma once

#include "Vector3.h"
#include "Application.h"
#include <string>
#include <sstream>

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

	//SHOPPER FUNCTIONS
	void setShopperScoreSucceed(double dt, int moneyLeft);
	int getShopperScore(void);
	void setShopperScoreFailed(double dt, int moneyNeeded);
	
	void setShopperHighScore(int score);
	int getShopperHighScore(void);

	void setShopperObjective(void);
	std::string getShopperObjective(void);

	//GUARD FUNCTIONS
	void setGuardScoreSucceed(double dt);
	int getGuardScoreSucceed(void);

	void setGuardHighScore(int score);
	int getGuardHighScore(void);

	//VILLAIN FUNCTIONS
	void setVillainScoreSucceed(double dt);
	int getVillainScore(void);
	void setVillainScoreFailed(int destroyedOBJ);

	void setVillainHighScore(int score);
	int getVillainHighScore(void);
};

