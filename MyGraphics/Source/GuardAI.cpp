#include "GuardAI.h"

bool changeDirection[8] = {false, false, false, false, false, false, false, false};

CGuardAI::CGuardAI(void)
{
}


CGuardAI::~CGuardAI(void)
{
}

void CGuardAI::setPosition(float x, float z)
{
	position.x = x;
	position.z = z;
}

Vector3 CGuardAI::getPosition(void)
{
	return position;
}

void CGuardAI::UpdateGuard(double dt, Vector3 playerPos)
{
	patrolPath(dt, PATROL);
}
void CGuardAI::patrolPath(double dt, int guardState)
{
	float guardSpeed;
	float checkPoint[8] = {-56, -12, 13, 5, -56, 31, 13, -32};

	changeDirection[0] = true;
	if (changeDirection[0] == true)
	{
		if (position.z > checkPoint[0])
		{
			moveZNegative(guardState, guardSpeed, dt, checkPoint[0]);
		}
		else
		{
			changeDirection[0] = false;
			changeDirection[1] = true;
		}
	}

	if (changeDirection[1] == true)
	{
		if (position.x < checkPoint[1])
		{
			moveXPositive(guardState, guardSpeed, dt, checkPoint[1]);
		}
		else
		{
			changeDirection[1] = false;
			changeDirection[2] = true;
		}
	}

	if (changeDirection[2] == true)
	{
		if (position.z < checkPoint[2])
		{
			moveZPositive(guardState, guardSpeed, dt, checkPoint[2]);
		}
		else
		{
			changeDirection[2] = false;
			changeDirection[3] = true;
		}
	}

	if (changeDirection[3] == true)
	{
		if (position.x < checkPoint[3])
		{
			moveXPositive(guardState, guardSpeed, dt, checkPoint[3]);
		}
		else
		{
			changeDirection[3] = false;
			changeDirection[4] = true;
		}
	}

	if (changeDirection[4] == true)
	{
		if (position.z > checkPoint[4])
		{
			moveZNegative(guardState, guardSpeed, dt, checkPoint[4]);
		}
		else
		{
			changeDirection[4] = false;
			changeDirection[5] = true;
		}
	}

	if (changeDirection[5] == true)
	{
		if (position.x < checkPoint[5])
		{
			moveXPositive(guardState, guardSpeed, dt, checkPoint[5]);
		}
		else
		{
			changeDirection[5] = false;
			changeDirection[6] = true;
		}
	}

	if (changeDirection[6] == true)
	{
		if (position.z < checkPoint[6])
		{
			moveZPositive(guardState, guardSpeed, dt, checkPoint[6]);
		}
		else
		{
			changeDirection[6] = false;
			changeDirection[7] = true;
		}
	}

	if (changeDirection[7] == true)
	{
		if (position.x > checkPoint[7])
		{
			moveXNegative(guardState, guardSpeed, dt, checkPoint[7]);
		}
		else
		{
			changeDirection[7] = false;
			changeDirection[0] = true;
		}
	}

}
void CGuardAI::moveXPositive(int guardState, double moveSpeed, double dt, double checkPoint)
{
	if (guardState == IDLE)
	{
		moveSpeed = 0;
	}
	else if (guardState == PATROL)
	{
		moveSpeed = 10;
	}
	else if (guardState == CHASE)
	{
		moveSpeed == 60;
	}

	if (position.x < checkPoint)
	{
		position.x += (float)moveSpeed * dt;
	}
}

void CGuardAI::moveXNegative(int guardState, double moveSpeed, double dt, double checkPoint)
{
	if (guardState == IDLE)
	{
		moveSpeed = 0;
	}
	else if (guardState == PATROL)
	{
		moveSpeed = 10;
	}
	else if (guardState == CHASE)
	{
		moveSpeed == 60;
	}

	if (position.x > checkPoint)
	{
		position.x -= (float)moveSpeed * dt;
	}
}

void CGuardAI::moveZPositive(int guardState, double moveSpeed, double dt, double checkPoint)
{
	if (guardState == IDLE)
	{
		moveSpeed = 0;
	}
	else if (guardState == PATROL)
	{
		moveSpeed = 10;
	}
	else if (guardState == CHASE)
	{
		moveSpeed == 60;
	}

	if (position.z < checkPoint)
	{
		position.z += (float)moveSpeed * dt;
	}
}

void CGuardAI::moveZNegative(int guardState, double moveSpeed, double dt, double checkPoint)
{
	if (guardState == IDLE)
	{
		moveSpeed = 0;
	}
	else if (guardState == PATROL)
	{
		moveSpeed = 10;
	}
	else if (guardState == CHASE)
	{
		moveSpeed == 60;
	}

	if (position.z > checkPoint)
	{
		position.z -= (float)moveSpeed * dt;
	}
}

void CGuardAI::distToPlayer(Vector3 playerPos)
{
	float diffInX, diffInZ;

	if (position.x > playerPos.x)
		diffInX = position.x - playerPos.x;
	else
		diffInX = playerPos.x - position.x;
	if (position.z > playerPos.z)
		diffInZ = position.z - playerPos.z;
	else
		diffInZ = playerPos.z - position.z;
}