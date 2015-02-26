#pragma once

#include "Vector3.h"

class CGuardAI
{
private:
	Vector3 position;
public:
	CGuardAI(void);
	~CGuardAI(void);

	enum States
	{
		IDLE,
		PATROL,
		CHASE,
		NUM_STATE
	};
	
	int guardState[NUM_STATE];

	void setPositionX(float x, float z);
	Vector3 getPosition(void);
	void distToPlayer(Vector3 playerPos);

};

