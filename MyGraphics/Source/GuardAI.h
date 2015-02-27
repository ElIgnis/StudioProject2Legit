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
		NUM_STATE,
	};
	
	int guardState[NUM_STATE];

	void setPosition(float x, float z);
	Vector3 getPosition(void);
	void UpdateGuard(double dt, Vector3 playerPos);
	void patrolPath(double dt, int guardState);
	void moveZPositive(int guardState, double moveSpeed, double dt, double checkPoint);
	void moveZNegative(int guardState, double moveSpeed, double dt, double checkPoint);
	void moveXPositive(int guardState, double moveSpeed, double dt, double checkPoint);
	void moveXNegative(int guardState, double moveSpeed, double dt, double checkPoint);
	void distToPlayer(Vector3 playerPos);

};

