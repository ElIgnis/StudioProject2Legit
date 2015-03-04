/******************************************************************************/
/*!
\file	Utility.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Returns the position of the operator
*/
/******************************************************************************/
#ifndef _UTILITY_H
#define _UTILITY_H

#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44& lhs, Position rhs);

#endif