#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

//COMMONS FUNCTIONS

//Position
void CPlayer::setPos(Vector3 Pos)
{
	position = Pos;
}
Vector3 CPlayer::getPos(void)
{ 
	return position;
}

//Time Taken
void CPlayer::setTimeTaken(double dt)
{
	timeTaken = dt;
}
double CPlayer::getTimeTaken(void)
{
	return timeTaken;
}

//CUSTOMER FUNCTIONS
//Score
void CPlayer::setShopperScoreSucceed(double dt, int moneyLeft)
{
	score = 0;
}
int CPlayer::getShopperScoreSucceed(void)
{
	return score;
}

//if Mission fail
void CPlayer::setShopperScoreFailed(double dt, int moneyNeeded)
{
	score = 0;
}
int CPlayer::getShopperScoreFailed(void)
{
	return score;
}

//Highscore
void setShopperHighScore(int score)
{
}

//GUARD FUNCTIONS
//Score
void CPlayer::setGuardScoreSucceed(double dt)
{
	score = 1800 - 10 * dt;
}
int CPlayer::getGuardScoreSucceed(void)
{
	return score;
}

//Highscore
void setGuardHighScore(int score)
{
}

//VILLAIN FUNCTIONS
//Score
void CPlayer::setVillainScoreSucceed(double dt)
{
	score = 500 + 300 / dt * 200;
}
int CPlayer::getVillainScoreSucceed(void)
{
	return score;
}

//if mission fail
void CPlayer::setVillainScoreFailed(int destroyedOBJ)
{
	score = destroyedOBJ * 10;
}
int CPlayer::getVillainScoreFailed(void)
{
	return score;
}

//Highscore
void setVillainHighScore(int score)
{
}