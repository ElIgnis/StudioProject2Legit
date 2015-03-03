#include <iostream>
#include <fstream>
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

//CUSTOMER FUNCTIONS
//Score
void CPlayer::setShopperScoreSucceed(double dt)
{
	score = 5000 + (300 / dt * 200);
}

//if Mission fail
void CPlayer::setShopperScoreFailed(double dt)
{
	score = 300 / dt * 200;
}

int CPlayer::getShopperScore(void)
{
	return score;
}

//Highscore
void CPlayer::setShopperHighScore(int score)
{
	int Highscore;
	std::ifstream inData;
	std::ofstream outData;
	std::string data, highScoreString;

	inData.open ("Source//Highscore//HighscoreShopper.txt"); //Open text file

	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	Highscore = atoi(data.c_str()); //Converting data from string to int 
	
	if (Highscore > score)			//Compared score to highscore
	{
		Highscore = Highscore;
	}
	else 
	{
		Highscore = score;
	}

	std::stringstream highScoreSS;
	highScoreSS << Highscore;
	highScoreString = highScoreSS.str();

	outData.open ("Source//Highscore//HighscoreShopper.txt");
	outData << highScoreString;

	inData.close();
	outData.close();
}

int CPlayer::getShopperHighScore(void)
{
	int highScore;
	std::ifstream inData;
	std::string data;

	inData.open ("Source//Highscore//HighscoreShopper.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	inData.close();

	highScore = std::stoi(data.c_str());

	return highScore;
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
void CPlayer::setGuardHighScore(int score)
{
	int Highscore;
	std::ifstream inData;
	std::ofstream outData;
	std::string data, highScoreString;

	inData.open ("Source//Highscore//HighscoreGuard.txt"); //Open text file

	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	Highscore = atoi(data.c_str()); //Converting data from string to int 
	
	if (Highscore > score)			//Compared score to highscore
	{
		Highscore = Highscore;
	}
	else 
	{
		Highscore = score;
	}

	std::stringstream highScoreSS;
	highScoreSS << Highscore;
	highScoreString = highScoreSS.str();

	outData.open ("Source//Highscore//HighscoreGuard.txt");
	outData << highScoreString;

	inData.close();
	outData.close();
}

int CPlayer::getGuardHighScore(void)
{
	int highScore;
	std::ifstream inData;
	std::string data;

	inData.open ("Source//Highscore//HighscoreGuard.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	inData.close();

	highScore = std::stoi(data.c_str());

	return highScore;
}

//VILLAIN FUNCTIONS
//Score
void CPlayer::setVillainScoreSucceed(double dt)
{
	score = 500 + 300 / dt * 200;
}
int CPlayer::getVillainScore(void)
{
	return score;
}

//if mission fail
void CPlayer::setVillainScoreFailed(int destroyedOBJ)
{
	score = destroyedOBJ * 10;
}

//Highscore
void CPlayer::setVillainHighScore(int score)
{
	int Highscore;
	std::ifstream inData;
	std::ofstream outData;
	std::string data, highScoreString;

	inData.open ("Source//Highscore//HighscoreVillain.txt"); //Open text file

	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	Highscore = atoi(data.c_str()); //Converting data from string to int 
	
	if (Highscore > score)			//Compared score to highscore
	{
		Highscore = Highscore;
	}
	else 
	{
		Highscore = score;
	}

	std::stringstream highScoreSS;
	highScoreSS << Highscore;
	highScoreString = highScoreSS.str();

	outData.open ("Source//Highscore//HighscoreVillain.txt");
	outData << highScoreString;

	inData.close();
	outData.close();
}

int CPlayer::getVillainHighScore(void)
{
	int highScore;
	std::ifstream inData;
	std::string data;

	inData.open ("Source//Highscore//HighscoreVillain.txt"); //Open text file
	
	while (!inData.eof()) //Reading from text file
	{
		getline (inData, data);
	}

	inData.close();

	highScore = std::stoi(data.c_str());

	return highScore;
}