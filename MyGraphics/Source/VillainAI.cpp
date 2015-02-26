#include "VillainAI.h"

bool Path[12] = {true, false, false, false, false, false, false, false, false, false, false, false};

CVillainAI::CVillainAI(void)
{
	//Villain starts outside of mall
	Position.x = 35.f;
	Position.y = -1.f;
	Position.z = 45.f;
}


CVillainAI::~CVillainAI(void)
{
}

void CVillainAI::SetPosition(Vector3 &NewPosition)
{
	Position = NewPosition;
}
void CVillainAI::SetDirection(Vector3 &NewDirection)
{

}

Vector3 CVillainAI::GetPosition(void)
{
	return Position;
}

void CVillainAI::UpdateAI(double dt, Vector3 &PlayerPosition)
{
	//TODO: Update path till if reach item
	//TODO: if reach item, destroy item
	//TODO: generate item from list
	UpdatePath(dt, CVillainAI::DEFAULT);
}
void CVillainAI::UpdatePath(double dt, int NewState)
{
	float Speed = 10.f;
	float RedShelfBack = 55.f;
	float RedShelfFront = 5.f;
	float FridgeFront = 0.f;

	if(Path[0] == true)
	{
		if(Position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, NewState, Speed, dt);
		}
		else
		{
			Path[0] = false;
			Path[1] = true;
		}
	}
	if(Path[1] == true)
	{
		if(Position.x > 9.f)
		{
			MoveXMinus(9.f, NewState, Speed, dt);
		}
		else
		{
			Path[1] = false;
			Path[2] = true;
		}
	}
	if(Path[2] == true)
	{
		if(Position.z < RedShelfFront)
		{
			MoveZPlus(RedShelfFront, NewState, Speed, dt);
		}
		else
		{
			Path[2] = false;
			Path[3] = true;
		}
	}
	if(Path[3] == true)
		{
		if(Position.x > 2.f)
		{
			MoveXMinus(2.f, NewState, Speed, dt);
		}
		else
		{
			Path[3] = false;
			Path[4] = true;
		}
	}
	if(Path[4] == true)
		{
		if(Position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, NewState, Speed, dt);
		}
		else
		{
			Path[4] = false;
			Path[5] = true;
		}
	}
	if(Path[5] == true)
		{
		if(Position.x > -8.f)
		{
			MoveXMinus(-8.f, NewState, Speed, dt);
		}
		else
		{
			Path[5] = false;
			Path[6] = true;
		}
	}
	if(Path[6] == true)
		{
		if(Position.z < RedShelfFront)

		{
			MoveZPlus(RedShelfFront, NewState, Speed, dt);
		}
		else
		{
			Path[6] = false;
			Path[7] = true;
		}
	}
	if(Path[7] == true)
		{
		if(Position.x > -18.f)
		{
			MoveXMinus(-18.f, NewState, Speed, dt);
		}
		else
		{
			Path[7] = false;
			Path[8] = true;
		}
	}
	if(Path[8] == true)
		{
		if(Position.z > -RedShelfBack)

		{
			MoveZMinus(-RedShelfBack, NewState, Speed, dt);
		}
		else
		{
			Path[8] = false;
			Path[9] = true;
		}
	}
	if(Path[9] == true)
		{
		if(Position.x > -29.f)
		{
			MoveXMinus(-29.f, NewState, Speed, dt);
		}
		else
		{
			Path[9] = false;
			Path[10] = true;
		}
	}
	if(Path[10] == true)
		{
		if(Position.z < RedShelfFront)

		{
			MoveZPlus(RedShelfFront, NewState, Speed, dt);
		}
		else
		{
			Path[10] = false;
			Path[11] = true;
		}
	}
	if(Path[11] == true)
		{
		if(Position.x < 29.f)
		{
			MoveXPlus(29.f, NewState, Speed, dt);
		}
		else
		{
			Path[11] = false;
			Path[0] = true;
		}
	}
}

void CVillainAI::MoveZPlus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if(NewState == CVillainAI::DEFAULT)
	{
		Speed = 10.f;
	}
	else if(NewState == CVillainAI::DETECTED)
	{
		Speed = 12.f;
	}
	else if(NewState == CVillainAI::CAUGHT)
	{
		Speed = 0.f;
	}
	//Move till stop point
	if(Position.z < StopPoint)
	{
		Position.z += (float)(dt * Speed);
	}
}
void CVillainAI::MoveZMinus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if(NewState == CVillainAI::DEFAULT)
	{
		Speed = 10.f;
	}
	else if(NewState == CVillainAI::DETECTED)
	{
		Speed = 12.f;
	}
	else if(NewState == CVillainAI::CAUGHT)
	{
		Speed = 0.f;
	}
	//Move till stop point
	if(Position.z > StopPoint)
	{
		Position.z -= (float)(dt * Speed);
	}
}
void CVillainAI::MoveXPlus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if(NewState == CVillainAI::DEFAULT)
	{
		Speed = 10.f;
	}
	else if(NewState == CVillainAI::DETECTED)
	{
		Speed = 12.f;
	}
	else if(NewState == CVillainAI::CAUGHT)
	{
		Speed = 0.f;
	}
	//Move till stop point
	if(Position.x < StopPoint)
	{
		Position.x += (float)(dt * Speed);
	}
}
void CVillainAI::MoveXMinus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if(NewState == CVillainAI::DEFAULT)
	{
		Speed = 10.f;
	}
	else if(NewState == CVillainAI::DETECTED)
	{
		Speed = 12.f;
	}
	else if(NewState == CVillainAI::CAUGHT)
	{
		Speed = 0.f;
	}
	//Move till stop point
	if(Position.x > StopPoint)
	{
		Position.x -= (float)(dt * Speed);
	}
}

