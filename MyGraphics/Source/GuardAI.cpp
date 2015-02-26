#include "GuardAI.h"


CGuardAI::CGuardAI(void)
{
}


CGuardAI::~CGuardAI(void)
{
}

void CGuardAI::setPositionX(float x, float z)
{
	position.x = x;
	position.z = z;
}

Vector3 CGuardAI::getPosition(void)
{
	return position;
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