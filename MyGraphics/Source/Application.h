/******************************************************************************/
/*!
\file	Application.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Application handler with timer and key input detection
*/
/******************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

/******************************************************************************/
/*!
		Class Application:
\brief	An application handler
*/
/******************************************************************************/
class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif