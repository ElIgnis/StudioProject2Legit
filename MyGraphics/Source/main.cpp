/******************************************************************************/
/*!
\file	main.cpp
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Runs the overall program
*/
/******************************************************************************/
#include "Application.h"
/******************************************************************************/
/*!
\brief
Main function of visual studio

\return 
Integer
*/
/******************************************************************************/
int main( void )
{
	Application app;
	app.Init();
	app.Run();
	app.Exit();
}