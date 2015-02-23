#include <iostream>
#include <fstream>
#include <string>
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
	score = 500;//moneyLeft * 10 + 300 / dt * 200;
}
int CPlayer::getShopperScoreSucceed(void)
{
	return score;
}

//if Mission fail
void CPlayer::setShopperScoreFailed(double dt, int moneyNeeded)
{
	score = (500 - moneyNeeded + 300) / dt * 10;
}
int CPlayer::getShopperScoreFailed(void)
{
	return score;
}

//Highscore
void setShopperHighScore(int score)
{
	int newScore, Highscore;
	std::ifstream inData;
	std::ofstream outData;
	std::string data;

	inData.open ("MyGraphics\\Source\\Highscore\\HighscoreShopper.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	Highscore = atoi(data.c_str()); //Converting data from string to int 
	
	if (score > Highscore)
	{
		outData << score;
	}
	else 
	{
		Highscore = Highscore;
		outData << Highscore;
	}

	inData.close();
	outData.close();
}

std::string CPlayer::getShopperHighScore(void)
{
	std::ifstream inData;
	std::string data;

	inData.open ("MyGraphics\\Source\\Highscore\\HighscoreShopper.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	inData.close();

	return data;
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
	int newScore, Highscore;
	std::ifstream inData;
	std::ofstream outData;
	std::string data;

	inData.open ("MyGraphics\\Source\\Highscore\\HighscoreGuard.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	Highscore = atoi(data.c_str()); //Converting data from string to int 
	
	if (score > Highscore)
	{
		outData << score;
	}
	else 
	{
		Highscore = Highscore;
		outData << Highscore;
	}

	inData.close();
	outData.close();
}

std::string CPlayer::getGuardHighScore(void)
{
	std::ifstream inData;
	std::string data;

	inData.open ("MyGraphics\\Source\\Highscore\\HighscoreGuard.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	inData.close();

	return data;
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
	int newScore, Highscore;
	std::ifstream inData;
	std::ofstream outData;
	std::string data;

	inData.open ("MyGraphics\\Source\\Highscore\\HighscoreVillain.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	Highscore = atoi(data.c_str()); //Converting data from string to int 
	
	if (score > Highscore)
	{
		outData << score;
	}
	else 
	{
		Highscore = Highscore;
		outData << Highscore;
	}

	inData.close();
	outData.close();
}

std::string CPlayer::getVillainHighScore(void)
{
	std::ifstream inData;
	std::string data;

	inData.open ("MyGraphics\\Source\\Highscore\\HighscoreVillain.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	inData.close();

	return data;
}