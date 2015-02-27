#include "VillainAI.h"

bool Path[16] = {true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

CVillainAI::CVillainAI(void)
{
	//Villain starts outside of mall
	Position.x = 37.f;
	Position.y = 1.f;
	Position.z = 45.f;
	RotateLeft = 0;
	Anim_Wreck = false;
	Anim_Rotate = false;
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
	//TODO:: Check against player position
	//else
	//{
		UpdatePath(dt, CVillainAI::DEFAULT);
	//}
	//TODO: run from player
	
}

bool CVillainAI::DestroyItem(CItem *Item)
{
	//Calculate distance from villain to item
	float Distance = (Position.z - Item->ItemPosition.z);

	//Negative distance fix
	if(Distance < 0)
	{
		Distance *= -1;
	}

	//Update for animation

	if(Distance <= 1.f && Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT 
		||Distance <= 1.f && Item->ItemState[CItem::NUM_STATE] == CItem::DESTROYED)
	{
		
		if(Position.x > Item->ItemPosition.x -1 && Position.x < Item->ItemPosition.x + 1)
		{
			cout << Distance << endl;
		Item->ItemState[CItem::NUM_STATE] = CItem::DESTROYED;
		Anim_Wreck = true;
		return true;
		}
	}
	return false;
}

bool CVillainAI::UpdatePath(double dt, int NewState)
{
	float Speed = 10.f;
	//Red shelf coords
	float RedShelfBack = 55.f;
	float RedShelfFront = 5.f;
	float Right_RedShelfRight = 19.5f;
	float Right_RedShelfLeft = 9.5f;
	float Left_RedShelfRight = 18.5f;
	float Left_RedShelfLeft = 28.5f;

	//Middle Fridge
	float FridgeFront = 2.f;
	float FridgeRight = 1.5f;
	float FridgeLeft = 7.5f;

	//Cold fridge
	float ColdFridgeBack = 53.f;
	float Left_ColdFridge = 39.f;
	float Right_ColdFridge = 37.f;
	float ColdFridgeFront = 15.f;
	
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
			RotateLeft++;
			return true;
		}
	}
	if(Path[1] == true)
	{
		if(Position.x > Right_RedShelfRight)
		{
			MoveXMinus(Right_RedShelfRight, NewState, Speed, dt);
		}
		else
		{
			Path[1] = false;
			Path[2] = true;
			RotateLeft++;
			return true;
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
			RotateLeft--;
			return true;
		}
	}
	if(Path[3] == true)
	{
		if(Position.x > Right_RedShelfLeft)
		{
			MoveXMinus(Right_RedShelfLeft, NewState, Speed, dt);
		}
		else
		{
			Path[3] = false;
			Path[4] = true;
			RotateLeft--;
			return true;
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
			RotateLeft++;
			return true;
		}
	}
	if(Path[5] == true)
	{
		if(Position.x > FridgeRight)
		{
			MoveXMinus(FridgeRight, NewState, Speed, dt);
		}
		else
		{
			Path[5] = false;
			Path[6] = true;
			RotateLeft++;
			return true;
		}
	}
	if(Path[6] == true)
	{
		if(Position.z < FridgeFront)

		{
			MoveZPlus(FridgeFront, NewState, Speed, dt);
		}
		else
		{
			Path[6] = false;
			Path[7] = true;
			RotateLeft--;
			return true;
		}
	}
	if(Path[7] == true)
	{
		if(Position.x > -FridgeLeft)
		{
			MoveXMinus(-FridgeLeft, NewState, Speed, dt);
		}
		else
		{
			Path[7] = false;
			Path[8] = true;
			RotateLeft--;
			return true;
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
			RotateLeft++;
			return true;
		}
	}
	if(Path[9] == true)
	{
		if(Position.x > -Left_RedShelfRight)
		{
			MoveXMinus(-Left_RedShelfRight, NewState, Speed, dt);
		}
		else
		{
			Path[9] = false;
			Path[10] = true;
			RotateLeft++;
			return true;
		}
	}
	if(Path[10] == true)
	{
		if(Position.z < FridgeFront)

		{
			MoveZPlus(FridgeFront, NewState, Speed, dt);
		}
		else
		{
			Path[10] = false;
			Path[11] = true;
			RotateLeft--;
			return true;
		}
	}
	if(Path[11] == true)
	{
		if(Position.x > -Left_RedShelfLeft)
		{
			MoveXMinus(-Left_RedShelfLeft, NewState, Speed, dt);
		}
		else
		{
			Path[11] = false;
			Path[12] = true;
			RotateLeft--;
			return true;
		}
	}
	if(Path[12] == true)
	{
		if(Position.z > -RedShelfBack)

		{
			MoveZMinus(-RedShelfBack, NewState, Speed, dt);
		}
		else
		{
			Path[12] = false;
			Path[13] = true;
			RotateLeft++;
			return true;
		}
	}
	if(Path[13] == true)
	{
		if(Position.x > -Left_ColdFridge)
		{
			MoveXMinus(-Left_ColdFridge, NewState, Speed, dt);
		}
		else
		{
			Path[13] = false;
			Path[14] = true;
			RotateLeft++;
			return true;
		}
	}
	if(Path[14] == true)
	{
		if(Position.z < ColdFridgeFront)

		{
			MoveZPlus(ColdFridgeFront, NewState, Speed, dt);
		}
		else
		{
			Path[14] = false;
			Path[15] = true;
			RotateLeft++;
			return true;
		}
	}
	if(Path[15] == true)
	{
		if(Position.x < Right_ColdFridge)
		{
			MoveXPlus(Right_ColdFridge, NewState, Speed, dt);
		}
		else
		{
			Path[15] = false;
			Path[0] = true;
			RotateLeft++;
			return true;
		}
	}
	return false;
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

