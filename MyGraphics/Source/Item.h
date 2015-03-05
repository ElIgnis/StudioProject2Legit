/******************************************************************************/
/*!
\file	Item.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Item with details and state machine
*/
/******************************************************************************/
#pragma once

#include"Vector3.h"
#include<string>
#include<vector>

using std::vector;
using std::string;

/******************************************************************************/
/*!
		Class CItem:
\brief	An Item class with state
*/
/******************************************************************************/
class CItem
{
public:
	//Vars
	string ItemName;
	double ItemPrice;
	int GEO_TYPE;
	Vector3 ItemShape;
	Vector3 ItemPosition;
	float MinWidth;
	float MaxWidth;
	float MinLength;
	float MaxLength;
	float MinHeight;
	float MaxHeight;
	int ItemIndex;
	int ItemState;

	//States
	enum States
	{
		DEFAULT,
		TAKEN,
		IN_TROLLEY,
		DESTROYED,
		CHECKED_OUT,
		NUM_STATE,
	};


	//Methods
	void SetDetails(string SetName, double SetPrice, Vector3 &SetPosition, string SetType, int SetIndex);
	void SetShape(Vector3 &NewShape);
	void SetPosition(Vector3 &NewPosition);
	string GetName(void);
	double GetPrice(void);

	CItem(void);
	~CItem(void);
};