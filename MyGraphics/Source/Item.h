#pragma once

#include"Vector3.h"
#include<string>
#include<vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

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

	//States
	enum States
	{
		DEFAULT,
		TAKEN,
		DESTROYED,
		CHECKED_OUT,
		NUM_STATE,
	};

	int ItemState[NUM_STATE];

	//Methods
	void SetDetails(string SetName, double SetPrice, Vector3 &SetPosition, string SetType);
	void SetShape(Vector3 &NewShape);
	void SetPosition(Vector3 &NewPosition);
	string GetName(void);
	double GetPrice(void);
	

	CItem(void);
	~CItem(void);
};