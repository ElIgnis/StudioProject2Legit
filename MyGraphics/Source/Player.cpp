/******************************************************************************/
/*!
\file	Player.cpp
\author Marcus Lim Tow Siang
\par	email: 141732S\@mymail.nyp.edu.sg
\brief
Player with score reading/recording
*/
/******************************************************************************/
#include <iostream>
#include <fstream>
#include "Player.h"
/******************************************************************************/
/*!
\brief
Default Constructor

\exception None
\return None
*/
/******************************************************************************/
CPlayer::CPlayer()
{
	score = 0;
}
/******************************************************************************/
/*!
\brief
Default Destructor
*/
/******************************************************************************/
CPlayer::~CPlayer()
{
}
/******************************************************************************/
/*!
\brief
Sets position of player

\param Pos - position to update
*/
/******************************************************************************/
void CPlayer::setPos(Vector3 Pos)
{
	position = Pos;
}
/******************************************************************************/
/*!
\brief
Sets position of player

\return vector3 position
*/
/******************************************************************************/
Vector3 CPlayer::getPos(void)
{ 
	return position;
}
/******************************************************************************/
/*!
\brief
Sets score of shopper on success

\param dt - delta time update
*/
/******************************************************************************/
void CPlayer::setShopperScoreSucceed(double dt)
{
	score = 5000 + (300 / dt * 200);
}
/******************************************************************************/
/*!
\brief
Sets score of shopper on failure

\param dt - delta time update
*/
/******************************************************************************/
void CPlayer::setShopperScoreFailed(double dt)
{
	score = 300 / dt * 200;
}
/******************************************************************************/
/*!
\brief
Gets score of shopper

\return score of shopper
*/
/******************************************************************************/
int CPlayer::getShopperScore(void)
{
	return score;
}
/******************************************************************************/
/*!
\brief
Sets high score of shopper

\param score - sets high score of shopper
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Gets high score of shopper

\return high score of shopper
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Sets score of guard on success

\param dt - delta time update
*/
/******************************************************************************/
void CPlayer::setGuardScoreSucceed(double dt)
{
	score = 1800 - 10 * dt;
}
/******************************************************************************/
/*!
\brief
Sets score of guard on failure

*/
/******************************************************************************/
void CPlayer::setGuardScoreFailed()
{
	score = 0;
}
/******************************************************************************/
/*!
\brief
Gets score of guard on success

\return score of guard
*/
/******************************************************************************/
int CPlayer::getGuardScoreSucceed(void)
{
	return score;
}
/******************************************************************************/
/*!
\brief
Sets high score of guard

\param score - sets high score of guard
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Gets high score of guard

\return high score of guard
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Sets score of villain on success

\param dt - delta time update
*/
/******************************************************************************/
void CPlayer::setVillainScoreSucceed(double dt)
{
	score = 500 + 300 / dt * 200;
}
/******************************************************************************/
/*!
\brief
Gets score of villain

\return score of villain
*/
/******************************************************************************/
int CPlayer::getVillainScore(void)
{
	return score;
}
/******************************************************************************/
/*!
\brief
Sets score of villain on failure

\param destroyedOBJ - delta time update
*/
/******************************************************************************/
void CPlayer::setVillainScoreFailed(int destroyedOBJ)
{
	score = destroyedOBJ * 10;
}
/******************************************************************************/
/*!
\brief
Sets high score of villain

\param score - sets high score of villain
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Gets score of villain

\return high score of villain
*/
/******************************************************************************/
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