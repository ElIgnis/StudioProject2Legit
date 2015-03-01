#include "VillainAI.h"

bool PathOneChecker[16] = {true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
//bool PathOneCoords[16]

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

	//State
	MovementSpeed = 10.f;
	CurrentState = CVillainAI::DEFAULT;

	//Detection
	ResetTimer = 20.f;
	DetectionTimer = 0.f;
	RecentlyDestroyed = false;
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
	if(RecentlyDestroyed && CurrentState != CVillainAI::CAUGHT)
	{
		DetectionTimer += (float)(dt);
	}
	if(DetectionTimer >= ResetTimer)
	{
		DetectionTimer = 0.f;
		RecentlyDestroyed = false;
	}

	float DistanceToPlayer = sqrt((Position.x - PlayerPosition.x) * (Position.x - PlayerPosition.x) + (Position.z - PlayerPosition.z) * (Position.z - PlayerPosition.z));

	//Stops updating AI when caught
	if(CurrentState != CVillainAI::CAUGHT)
	{
		if(DistanceToPlayer < 0.f)
		{
			DistanceToPlayer *= -1;
		}
		else if(DistanceToPlayer < 8.f && RecentlyDestroyed == true)
		{
			CurrentState = CVillainAI::DETECTED;
		}
		else
		{
			CurrentState = CVillainAI::DEFAULT;
		}
		UpdatePath(dt);
	}
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
		
		//cout <<  << endl;

		//Update for animation
		if(Position.x < Item->ItemPosition.x + 4.5f && Position.x > Item->ItemPosition.x)
		{
			ItemAtLeft = true;
			Anim_Wreck = true;
		}
		else if(Position.x > Item->ItemPosition.x -4.5f && Position.x < Item->ItemPosition.x)
		{
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
				RecentlyDestroyed = true;
			}
		}
	}
	if(Anim_Revert)
	{
		SetDirection(Vector3(0, 90.f * (float)(RotateLeft), 0), dt);
		if(Direction.y >= 90.f * (float)(RotateLeft))
		{
			ItemAtLeft = false;
			ItemAtRight = false;
			Anim_Revert = false;
			return true;
		}
	}
	else
	return false;
}

bool CVillainAI::UpdatePath(double dt)
{
	//Red shelf coords
	float RedShelfBack = 56.f;
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
	float ColdFridgeBack = 56.f;
	float Left_ColdFridge = 39.f;
	float Right_ColdFridge = 37.f;
	float ColdFridgeFront = 16.f;

	//Perform walking
	if(Anim_Wreck == false)
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
	if(PathOneChecker[0] == true)
	{
		if(Position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			PathOneChecker[0] = false;
			PathOneChecker[1] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[1] == true)
	{
		if(Position.x > Right_RedShelfRight)
		{
			MoveXMinus(Right_RedShelfRight, dt);
		}
		else
		{
			PathOneChecker[1] = false;
			PathOneChecker[2] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[2] == true)
	{
		if(Position.z < RedShelfFront)
		{
			MoveZPlus(RedShelfFront, dt);
		}
		else
		{
			PathOneChecker[2] = false;
			PathOneChecker[3] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[3] == true)
	{
		if(Position.x > Right_RedShelfLeft)
		{
			MoveXMinus(Right_RedShelfLeft, dt);
		}
		else
		{
			PathOneChecker[3] = false;
			PathOneChecker[4] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[4] == true)
	{
		if(Position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			PathOneChecker[4] = false;
			PathOneChecker[5] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[5] == true)
	{
		if(Position.x > FridgeRight)
		{
			MoveXMinus(FridgeRight, dt);
		}
		else
		{
			PathOneChecker[5] = false;
			PathOneChecker[6] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[6] == true)
	{
		if(Position.z < FridgeFront)

		{
			MoveZPlus(FridgeFront, dt);
		}
		else
		{
			PathOneChecker[6] = false;
			PathOneChecker[7] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[7] == true)
	{
		if(Position.x > -FridgeLeft)
		{
			MoveXMinus(-FridgeLeft, dt);
		}
		else
		{
			PathOneChecker[7] = false;
			PathOneChecker[8] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[8] == true)
	{
		if(Position.z > -RedShelfBack)

		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			PathOneChecker[8] = false;
			PathOneChecker[9] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[9] == true)
	{
		if(Position.x > -Left_RedShelfRight)
		{
			MoveXMinus(-Left_RedShelfRight, dt);
		}
		else
		{
			PathOneChecker[9] = false;
			PathOneChecker[10] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[10] == true)
	{
		if(Position.z < RedShelfFront)

		{
			MoveZPlus(RedShelfFront, dt);
		}
		else
		{
			PathOneChecker[10] = false;
			PathOneChecker[11] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[11] == true)
	{
		if(Position.x > -Left_RedShelfLeft)
		{
			MoveXMinus(-Left_RedShelfLeft, dt);
		}
		else
		{
			PathOneChecker[11] = false;
			PathOneChecker[12] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[12] == true)
	{
		if(Position.z > -RedShelfBack)

		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			PathOneChecker[12] = false;
			PathOneChecker[13] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[13] == true)
	{
		if(Position.x > -Left_ColdFridge)
		{
			MoveXMinus(-Left_ColdFridge, dt);
		}
		else
		{
			PathOneChecker[13] = false;
			PathOneChecker[14] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[14] == true)
	{
		if(Position.z < ColdFridgeFront)

		{
			MoveZPlus(ColdFridgeFront, dt);
		}
		else
		{
			PathOneChecker[14] = false;
			PathOneChecker[15] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if(PathOneChecker[15] == true)
	{
		if(Position.x < Right_ColdFridge)
		{
			MoveXPlus(Right_ColdFridge, dt);
		}
		else
		{
			PathOneChecker[15] = false;
			PathOneChecker[0] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	return false;
}

void CVillainAI::MoveZPlus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if(CurrentState == CVillainAI::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	else if(CurrentState == CVillainAI::DETECTED)
	{
		MovementSpeed = 16.f;
	}
	else if(CurrentState == CVillainAI::CAUGHT)
	{
		MovementSpeed = 0.f;
	}
	//Move till stop point
	if(Position.z < StopPoint)
	{
		Position.z += (float)(dt * MovementSpeed);
	}
}

void CVillainAI::MoveZMinus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if(CurrentState == CVillainAI::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	else if(CurrentState == CVillainAI::DETECTED)
	{
		MovementSpeed = 16.f;
	}
	else if(CurrentState == CVillainAI::CAUGHT)
	{
		MovementSpeed = 0.f;
	}
	//Move till stop point
	if(Position.z > StopPoint)
	{
		Position.z -= (float)(dt * MovementSpeed);
	}
}

void CVillainAI::MoveXPlus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if(CurrentState == CVillainAI::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	else if(CurrentState == CVillainAI::DETECTED)
	{
		MovementSpeed = 16.f;
	}
	else if(CurrentState == CVillainAI::CAUGHT)
	{
		MovementSpeed = 0.f;
	}
	//Move till stop point
	if(Position.x < StopPoint)
	{
		Position.x += (float)(dt * MovementSpeed);
	}
}

void CVillainAI::MoveXMinus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if(CurrentState == CVillainAI::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	else if(CurrentState == CVillainAI::DETECTED)
	{
		MovementSpeed = 16.f;
	}
	else if(CurrentState == CVillainAI::CAUGHT)
	{
		MovementSpeed = 0.f;
	}
	//Move till stop point
	if(Position.x > StopPoint)
	{
		Position.x -= (float)(dt * MovementSpeed);
	}
}

void CVillainAI::SetState(int NewState)
{
	CurrentState = NewState;
}

int CVillainAI::GetState(void)
{
	return CurrentState;
}