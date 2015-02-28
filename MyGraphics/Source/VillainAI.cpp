#include "VillainAI.h"

bool Path[16] = {true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

CVillainAI::CVillainAI(void)
{
	//Villain starts outside of mall
	Position.x = 37.f;
	Position.y = 1.f;
	Position.z = 45.f;
	Direction.x = 0.f;
	Direction.y = 0.f;
	Direction.z = 0.f;

	//Animation
	RotateLeft = 0;
	Anim_Wreck = false;
	Anim_Rotate = false;
	Anim_Revert = false;
	RotationSpeed = 100.f;
	ItemAtLeft = false;
	ItemAtRight = false;

	Rotate_Leg_Left_Back = false;
	Rotate_Leg_Right_Back = false;
	Rotate_Hand_Left_Back = false;
	Rotate_Hand_Right_Back = false;

	Rotation_Left_Leg = 0.f;
	Rotation_Right_Leg = 0.f;
	Rotation_Left_Hand = 0.f;
	Rotation_Right_Hand = 0.f;

}

CVillainAI::~CVillainAI(void)
{
}

void CVillainAI::SetPosition(Vector3 &NewPosition)
{
	Position = NewPosition;
}

void CVillainAI::SetDirection(Vector3 &NewDirection, double dt)
{
	if(Direction.y < NewDirection.y)
	{
		Direction.y += (float)(dt * RotationSpeed);
		if(Direction.y >= NewDirection.y)
		{
			Anim_Rotate = false;
		}
	}
	else if(Direction.y > NewDirection.y)
	{
		Direction.y -= (float)(dt * RotationSpeed);
		if(Direction.y <= NewDirection.y)
		{
			Anim_Rotate = false;
		}
	}
	
}

Vector3 CVillainAI::GetPosition(void)
{
	return Position;
}

Vector3 CVillainAI::GetDirection(void)
{
	return Direction;
}

void CVillainAI::UpdateAI(double dt, Vector3 &PlayerPosition)
{
	//TODO:: Check against player position

	UpdatePath(dt, CVillainAI::DEFAULT);
	//TODO: run from player
	
}

bool CVillainAI::DestroyItem(CItem *Item, double dt)
{
	//Calculate distance from villain to item
	float DistanceZ = (Position.z - Item->ItemPosition.z);

	//Negative distance fix
	if(DistanceZ < 0)
	{
		DistanceZ *= -1;
	}

	//Check distance
	if(DistanceZ <= 0.2f && Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
	{
		//cout << "Plx: " << Position.x << endl;
		//cout << "Plz: " << Position.z << endl;
		//cout << "Ix: " << Item->ItemPosition.x << endl;
		//cout << "Iz: " << Item->ItemPosition.z << endl;

		//Update for animation
		if(Position.x < Item->ItemPosition.x + 3.9f && Position.x > Item->ItemPosition.x)
		{
			cout << "Item at left" << endl;
			ItemAtLeft = true;
			Anim_Wreck = true;
		}
		else if(Position.x > Item->ItemPosition.x -3.9f && Position.x < Item->ItemPosition.x)
		{
			cout << "Item at right" << endl;
			ItemAtRight = true;
			Anim_Wreck = true;
		}
	}
	if(Anim_Wreck)
	{
		if(Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
		{
			if(Rotation_Right_Hand <= 90.f)
				Rotation_Right_Hand += (float)(RotationSpeed * dt);
			if(Rotation_Left_Hand >= -90.f)
				Rotation_Left_Hand -= (float)(RotationSpeed * dt);
		}
		if(Rotation_Right_Hand >= 90.f && Rotation_Left_Hand <= -90.f)
		{
			Item->ItemState[CItem::NUM_STATE] = CItem::DESTROYED;
		}
		if(Item->ItemState[CItem::NUM_STATE] == CItem::DESTROYED)
		{
			if(Rotation_Right_Hand >= 0.f && Rotation_Left_Hand <= 0.f)
			{
				Rotation_Right_Hand -= (float)(RotationSpeed * dt);
				Rotation_Left_Hand += (float)(RotationSpeed * dt);
			}
			else
			{
				Anim_Wreck = false;
				Anim_Revert = true;
			}
			
		}
	}
	if(Anim_Revert)
	{
		SetDirection(Vector3(0, 0.f, 0), dt);
		//if(Direction.y > 0)
		//{
		//	
		//	Direction.y -= (float)(dt * RotationSpeed);
		//}
		//if(Direction.y < 0)
		//{
		//	Direction.y += (float)(dt * RotationSpeed);
		//	//SetDirection(Vector3(0, 0.f, 0), dt);
		//	//Direction.y = 0;
		//}
		if(Direction.y <= 0.1 && Direction.y >= -0.1f)
		{
			ItemAtLeft = false;
			ItemAtRight = false;
			Anim_Revert = false;
			Anim_Wreck = false;
			return true;
		}
	}
	if(Item->ItemState[CItem::NUM_STATE] != CItem::DEFAULT)
	{
		return true;
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

	//Perform walking
	//if(Anim_Wreck == false)
	{
		//Left Arm
		if (Rotate_Hand_Left_Back == false)
		{
			Rotation_Left_Hand += (float)(RotationSpeed * dt);
		}
		if (Rotate_Hand_Left_Back == true)
		{
			Rotation_Left_Hand -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Left_Hand >= 30)
		{
			Rotate_Hand_Left_Back = true;
		}
		if (Rotation_Left_Hand <= -30)
		{
			Rotate_Hand_Left_Back = false;
		}
		//Right Arm
		if (Rotate_Hand_Right_Back == false)
		{
			Rotation_Right_Hand += (float)(RotationSpeed * dt);
		}
		if (Rotate_Hand_Right_Back == true)
		{
			Rotation_Right_Hand -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Right_Hand >= 30)
		{
			Rotate_Hand_Right_Back = true;
		}
		if (Rotation_Right_Hand <= -30)
		{
			Rotate_Hand_Right_Back = false;
		}
		//Left Leg
		if (Rotate_Leg_Left_Back == false)
		{
			Rotation_Left_Leg += (float)(RotationSpeed * dt);
		}
		if (Rotate_Leg_Left_Back == true)
		{
			Rotation_Left_Leg -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Left_Leg >= 30)
		{
			Rotate_Leg_Left_Back = true;
		}
		if (Rotation_Left_Leg <= -30)
		{
			Rotate_Leg_Left_Back = false;
		}
		//Right Leg
		if (Rotate_Leg_Right_Back == false)
		{
			Rotation_Right_Leg += (float)(RotationSpeed * dt);
		}
		if (Rotate_Leg_Right_Back == true)
		{
			Rotation_Right_Leg -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Right_Leg >= 30)
		{
			Rotate_Leg_Right_Back = true;
		}
		if (Rotation_Right_Leg <= -30)
		{
			Rotate_Leg_Right_Back = false;
		}
	}
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
			return true;
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
			RotateLeft--;
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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
			Anim_Rotate = true;
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

