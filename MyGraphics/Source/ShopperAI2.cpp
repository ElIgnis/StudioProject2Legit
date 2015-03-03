#include "ShopperAI2.h"

bool ShopperPath[15] = { true, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

CShopperAI2::CShopperAI2()
{
	//Villain starts outside of mall
	Position.x = 37.f;
	Position.y = -3.f;
	Position.z = 40.f;
	Direction.x = 0.f;
	Direction.y = 0.f;
	Direction.z = 0.f;

	//Animation
	RotateLeft = 0;
	Anime_Take = false;
	Anim_Rotate = false;
	Anim_Revert = false;
	RotationSpeed = 100.f;
	ItemAtLeft = false;
	ItemAtRight = false;

	DoNotTurn = false;
	fowardtrolley = true;
	backwardtrolley = false;

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
	CurrentState = ~CShopperAI2::DEFAULT;

	//Detection
	ResetTimer = 20.f;
	DetectionTimer = 0.f;
	RecentlyDestroyed = false;
}


CShopperAI2::~CShopperAI2()
{
}

void CShopperAI2::SetPosition(Vector3 &NewPosition)
{
	Position = NewPosition;
}

void CShopperAI2::SetDirection(Vector3 &NewDirection, double dt)
{
	if (Direction.y < NewDirection.y)
	{
		Direction.y += (float)(dt * RotationSpeed);
		if (Direction.y >= NewDirection.y)
		{
			Anim_Rotate = false;
		}
	}
	else if (Direction.y > NewDirection.y)
	{
		Direction.y -= (float)(dt * RotationSpeed);
		if (Direction.y <= NewDirection.y)
		{
			Anim_Rotate = false;
		}
	}
}

Vector3 CShopperAI2::GetPosition(void)
{
	return Position;
}

Vector3 CShopperAI2::GetDirection(void)
{
	return Direction;
}

void CShopperAI2::UpdateAI(double dt, Vector3 &PlayerPosition)
{
	if (RecentlyDestroyed && CurrentState != CShopperAI2::CAUGHT)
	{
		DetectionTimer += (float)(dt);
	}
	if (DetectionTimer >= ResetTimer)
	{
		DetectionTimer = 0.f;
		RecentlyDestroyed = false;
	}

	float DistanceToPlayer = sqrt((Position.x - PlayerPosition.x) * (Position.x - PlayerPosition.x) + (Position.z - PlayerPosition.z) * (Position.z - PlayerPosition.z));

	//Stops updating AI when caught
	if (CurrentState != CShopperAI2::CAUGHT)
	{
		if (DistanceToPlayer < 0.f)
		{
			DistanceToPlayer *= -1;
		}
		else if (DistanceToPlayer < 8.f && RecentlyDestroyed == true)
		{
			CurrentState = CShopperAI2::DETECTED;
		}
		else
		{
			CurrentState = CShopperAI2::DEFAULT;
		}
		UpdatePath(dt);
	}
}

bool CShopperAI2::TakingItem(CItem *Item, double dt)
{
	//Calculate distance from villain to item
	float DistanceZ = (Position.z - Item->ItemPosition.z);
	//Negative distance fix
	if (DistanceZ < 0)
	{
		DistanceZ *= -1;
	}

	//Check distance
	if (DistanceZ <= 0.2f && Item->ItemState == CItem::DEFAULT)
	{
		//cout << "Plx: " << Position.x << endl;
		//cout << "Plz: " << Position.z << endl;

		//cout << "taken" << endl;

		//Update for animation
		if (Position.x < Item->ItemPosition.x + 4.5f && Position.x > Item->ItemPosition.x)
		{
			ItemAtLeft = true;
			Anime_Take = true;
			DoNotTurn = true;
			fowardtrolley = true;
			backwardtrolley = false;
			
		}
		else if (Position.x > Item->ItemPosition.x - 4.5f && Position.x < Item->ItemPosition.x)
		{
			ItemAtRight = true;
			Anime_Take = true;
			DoNotTurn = true;
			backwardtrolley = true;
			fowardtrolley = false;
		}
	}
	if (Anime_Take)
	{
		if (Item->ItemState == CItem::DEFAULT)
		{
			if (Rotation_Right_Hand <= 90.f)
				Rotation_Right_Hand += (float)(RotationSpeed * dt);
			if (Rotation_Left_Hand >= -90.f)
				Rotation_Left_Hand -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Right_Hand >= 90.f && Rotation_Left_Hand <= -90.f)
		{
			Item->ItemState = CItem::IN_TROLLEY;
			
		}
		if (Item->ItemState == CItem::IN_TROLLEY)
		{
			if (Rotation_Right_Hand >= 0.f && Rotation_Left_Hand <= 0.f)
			{
				Rotation_Right_Hand -= (float)(RotationSpeed * dt);
				Rotation_Left_Hand += (float)(RotationSpeed * dt);
			}
			else
			{
				Anime_Take = false;
				Anim_Revert = true;
				RecentlyDestroyed = true;
				DoNotTurn = true;
				//backwardtrolley = false;
				//fowardtrolley = true;
			}
		}
	}
	if (Anim_Revert)
	{
		SetDirection(Vector3(0, 90.f * (float)(RotateLeft), 0), dt);
		if (Direction.y >= 90.f * (float)(RotateLeft))
		{
			ItemAtLeft = false;
			ItemAtRight = false;
			Anim_Revert = false;
			DoNotTurn = false;
			backwardtrolley = false;
			fowardtrolley = true;
			return true;
		}
	}
	else
		return false;
}

bool CShopperAI2::UpdatePath(double dt)
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
	if (Anime_Take == false)
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
	if (ShopperPath[0] == true)
	{
		if (Position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			ShopperPath[0] = false;
			ShopperPath[1] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[1] == true)
	{
		if (Position.x > Right_RedShelfRight)
		{
			MoveXMinus(Right_RedShelfRight, dt);
		}
		else
		{
			ShopperPath[1] = false;
			ShopperPath[2] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[2] == true)
	{
		if (Position.z < RedShelfFront)
		{
			MoveZPlus(RedShelfFront, dt);
		}
		else
		{
			ShopperPath[2] = false;
			ShopperPath[3] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[3] == true)
	{
		if (Position.x > Right_RedShelfLeft)
		{
			MoveXMinus(Right_RedShelfLeft, dt);
		}
		else
		{
			ShopperPath[3] = false;
			ShopperPath[4] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[4] == true)
	{
		if (Position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			ShopperPath[4] = false;
			ShopperPath[5] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[5] == true)
	{
		if (Position.x > FridgeRight)
		{
			MoveXMinus(FridgeRight, dt);
		}
		else
		{
			ShopperPath[5] = false;
			ShopperPath[6] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[6] == true)
	{
		if (Position.z < FridgeFront)

		{
			MoveZPlus(FridgeFront, dt);
		}
		else
		{
			ShopperPath[6] = false;
			ShopperPath[7] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[7] == true)
	{
		if (Position.x > -FridgeLeft)
		{
			MoveXMinus(-FridgeLeft, dt);
		}
		else
		{
			ShopperPath[7] = false;
			ShopperPath[8] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[8] == true)
	{
		if (Position.z > -RedShelfBack)

		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			ShopperPath[8] = false;
			ShopperPath[9] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[9] == true)
	{
		if (Position.x > -Left_RedShelfRight)
		{
			MoveXMinus(-Left_RedShelfRight, dt);
		}
		else
		{
			ShopperPath[9] = false;
			ShopperPath[10] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[10] == true)
	{
		if (Position.z < RedShelfFront)

		{
			MoveZPlus(RedShelfFront, dt);
		}
		else
		{
			ShopperPath[10] = false;
			ShopperPath[11] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[11] == true)
	{
		if (Position.x > -Left_RedShelfLeft)
		{
			MoveXMinus(-Left_RedShelfLeft, dt);
		}
		else
		{
			ShopperPath[11] = false;
			ShopperPath[12] = true;
			RotateLeft--;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[12] == true)
	{
		if (Position.z > -RedShelfBack)

		{
			MoveZMinus(-RedShelfBack, dt);
		}
		else
		{
			ShopperPath[12] = false;
			ShopperPath[13] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[13] == true)
	{
		if (Position.x > -Left_ColdFridge)
		{
			MoveXMinus(-Left_ColdFridge, dt);
		}
		else
		{
			ShopperPath[13] = false;
			ShopperPath[14] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[14] == true)
	{
		if (Position.z < ColdFridgeFront)

		{
			MoveZPlus(ColdFridgeFront, dt);
		}
		else
		{
			ShopperPath[14] = false;
			ShopperPath[15] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	if (ShopperPath[15] == true)
	{
		if (Position.x < Right_ColdFridge)
		{
			MoveXPlus(Right_ColdFridge, dt);
		}
		else
		{
			ShopperPath[15] = false;
			ShopperPath[0] = true;
			RotateLeft++;
			Anim_Rotate = true;
			return true;
		}
	}
	return false;
}

void CShopperAI2::MoveZPlus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI2::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (Position.z < StopPoint)
	{
		Position.z += (float)(dt * MovementSpeed);
	}
}

void CShopperAI2::MoveZMinus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI2::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (Position.z > StopPoint)
	{
		Position.z -= (float)(dt * MovementSpeed);
	}
}

void CShopperAI2::MoveXPlus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI2::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (Position.x < StopPoint)
	{
		Position.x += (float)(dt * MovementSpeed);
	}
}

void CShopperAI2::MoveXMinus(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI2::DEFAULT)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (Position.x > StopPoint)
	{
		Position.x -= (float)(dt * MovementSpeed);
	}
}

void CShopperAI2::SetState(int NewState)
{
	CurrentState = NewState;
}

int CShopperAI2::GetState(void)
{
	return CurrentState;
}