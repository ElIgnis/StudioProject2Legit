/******************************************************************************/
/*!
\file	Utility.cpp
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Returns the position of the operator
*/
/******************************************************************************/
#include "Utility.h"
/******************************************************************************/
/*!
\brief
Returns the position of the operator
*/
/******************************************************************************/
Position operator*(const Mtx44& lhs, Position rhs)
{
	float b[4];
	for(int i = 0; i < 4; i++)
		b[i] = lhs.a[0 * 4 + i] * rhs.x + lhs. a[1 * 4 + i] * rhs.y + lhs.a[2 * 4 + i] * rhs.z + lhs.a[3 * 4 + i] * 1;
	return Position(b[0], b[1], b[2]);
}