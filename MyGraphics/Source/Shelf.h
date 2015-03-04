/******************************************************************************/
/*!
\file	Shelf.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Shelf to store items
*/
/******************************************************************************/
#pragma once

#include "Item.h"
/******************************************************************************/
/*!
		Class CShelf:
\brief	An shelf class to store items
*/
/******************************************************************************/
class CShelf
{
public:
	vector<CItem*>Shelf;
	vector<Vector3>Init_Pos;
	Vector3 Position;
	float MinWidth;
	float MaxWidth;
	float MinLength;
	float MaxLength;

	void SetShelfPosition(Vector3 &NewPosition);
	void SetShelfCollision(float Width, float Length);
	CShelf(void);
	~CShelf(void);
};