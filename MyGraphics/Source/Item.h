#pragma once

#include "SP2.h"

#include<iostream>

using std::cout;
using std::endl;
using std::string;

class CItem
{
public:
	//Vars
	string ItemName;
	double ItemPrice;
	Vector3 ItemShape;
	
	//States
	enum States
	{
		NORMAL,
		DESTROYED,
		CHECKED_OUT,
		NUM_STATE,
	};

	int ItemState[NUM_STATE];

	//Methods
	void SetDetails(string SetName, double SetPrice);
	void SetShape(Vector3 &NewShape);
	string GetName(void);
	double GetPrice(void);
	

	CItem(void);
	~CItem(void);
};