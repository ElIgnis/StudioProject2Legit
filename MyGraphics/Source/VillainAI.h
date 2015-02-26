#pragma once

#include "Vector3.h"
#include "Item.h"

class CVillainAI
{
private:
	Vector3 Position;
	Vector3 Direction;

	enum States
	{
		DEFAULT,
		MOVING,
		CAUGHT,
		DETECTED,
		DESTROYING,
		NUM_STATES,
	};
public:
	CVillainAI(void);
	~CVillainAI(void);

	int RotateLeft;

	void SetPosition(Vector3 &NewPosition);
	void UpdateAI(double dt, Vector3 &PlayerPosition);
	bool UpdatePath(double dt, int NewState);
	void UpdateGoal(CItem *Item);
	void SetDirection(Vector3 &NewDirection);
	void MoveZPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveZMinus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXMinus(double StopPoint, int NewState, double Speed, double dt);
	Vector3 GetPosition(void);
};

