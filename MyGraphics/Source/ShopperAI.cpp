#include "ShopperAI.h"

bool ShopperPath[15] = { true, false, false, false, false, false, false, false, false, false, false, false , false , false , false};
bool ShopperPath2[12] = { true, false, false, false, false, false, false, false, false, false, false, false };
bool ShopperPath3[15] = { true, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

CShopperAI::CShopperAI()
{
	//starting point
	position.x = 36;
	position.y = 1;
	position.z = 37;
	direction = 0;
	Rotangle = 0;
	timer = 0;
	SetDirection = false;
	Animate_ON = true;
	Directions = false;
	RENDERINGAI = false;
	//timer_item1 = 0;
	item1 = false;
	item2 = false;
	RenderTrolley = false;
	item_milo = false;
	item_sardine =false;
	item_MnC = false;
	item_maggie = false;
	item_iceCream = false;
	item_choco = false;

	

	//Animation
	Rotate_Leg_Left_Back = false;
	Rotate_Leg_Right_Back = false;
	Rotate_Hand_Left_Back = false;
	Rotate_Hand_Right_Back = false;

	Rotation_Left_Leg = 0;
	Rotation_Right_Leg = 0;
	Rotation_Left_Hand = 0;
	Rotation_Right_Hand = 0;


	//Wl's
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
	//Detection
	RecentlyDestroyed = false;

}


CShopperAI::~CShopperAI()
{
}
//Kel's
void CShopperAI::setPositionX(float x)
{
	position.x = x;
}
void CShopperAI::setPositionZ(float z)
{
	position.z = z;
}

float CShopperAI::getPositionX(void)
{
	return position.x;
}
float CShopperAI::getPositionZ(void)
{
	return position.z;
}

void CShopperAI::setShopperDirection(int r)
{
	Rotangle = r;
}
int CShopperAI::getShopperDirection(void)
{
	return Rotangle;
}
//WL's
Vector3 CShopperAI::GetPosition(void)
{
	return position;
}
Vector3 CShopperAI::GetDirections(void)
{
	return Direction;
}
void CShopperAI::SetPosition(Vector3 &NewPosition)
{
	position = NewPosition;
}
void CShopperAI::SetDirections(Vector3 &NewDirection, double dt)
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
//Kel's
void CShopperAI::ShopperInitialize(void)
{
	//initialize Shopper state
	ShopperSTATE = WALK;
}

void CShopperAI::UpdatePath(double dt, Vector3 &Playerposition)
{
	//TODO: Update path till if reach item
	//TODO: if reach item, take item
	//TODO: generate item from list
	float DistanceToPlayer = sqrt((position.x - Playerposition.x) * (position.x - Playerposition.x) + (position.z - Playerposition.z) * (position.z - Playerposition.z));
	
	//WalkingPath2(dt); //Using Wl's Method
	if (RENDERINGAI == true)
	{
		WalkingPath(dt, CShopperAI::WALK);
	}
	else if (RENDERINGAI == false)
	{
		WalkingPath3(dt, CShopperAI::WALK);
	}
}
//Wl's
bool CShopperAI::TakingItem(CItem *Item, double dt)
{
	//Calculate distance from villain to item
	float DistanceZ = (position.z - Item->ItemPosition.z);
	//Negative distance fix
	if (DistanceZ < 0)
	{
		DistanceZ *= -1;
	}

	//Check distance
	if (DistanceZ <= 0.2f && Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
	{
		//cout << "Plx: " << Position.x << endl;
		//cout << "Plz: " << Position.z << endl;

		//cout <<  << endl;

		//Update for animation
		if (position.x < Item->ItemPosition.x + 4.5f && position.x > Item->ItemPosition.x)
		{
			ItemAtLeft = true;
			Anim_Wreck = true;
		}
		else if (position.x > Item->ItemPosition.x - 4.5f && position.x < Item->ItemPosition.x)
		{
			ItemAtRight = true;
			Anim_Wreck = true;
		}
	}
	if (Anim_Wreck)
	{
		if (Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
		{
			if (Rotation_Right_Hand <= 90.f)
				Rotation_Right_Hand += (float)(RotationSpeed * dt);
			if (Rotation_Left_Hand >= -90.f)
				Rotation_Left_Hand -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Right_Hand >= 90.f && Rotation_Left_Hand <= -90.f)
		{
			Item->ItemState[CItem::NUM_STATE] = CItem::DESTROYED;
		}
		if (Item->ItemState[CItem::NUM_STATE] == CItem::DESTROYED)
		{
			if (Rotation_Right_Hand >= 0.f && Rotation_Left_Hand <= 0.f)
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
	if (Anim_Revert)
	{
		SetDirections(Vector3(0, 90.f * (float)(RotateLeft), 0), dt);
		if (Direction.y >= 90.f * (float)(RotateLeft))
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

void CShopperAI::WalkingPath(double dt, int NewState)
{
	//#######Rotation of Shoppers#############
	if (SetDirection == true)
	{
		//turn Left's
		if (direction == 0)
		{
			if (Rotangle != 0)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 1)
		{
			if (Rotangle != 90)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 2)
		{
			if (Rotangle != 180)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 3)
		{
			if (Rotangle != 270)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		//Turn Right's
		else if (direction == 4)
		{
			if (Rotangle != 0)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{

				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 5)
		{
			if (Rotangle != -90)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 6)
		{
			if (Rotangle != -180)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 7)
		{
			if (Rotangle != -270)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}

		else if (direction == 8)
		{
			if (Rotangle != -90)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
	}

	////Walking ( Last week Coding)
	//if (walkFront = true)
	//{
	//	if (position.z > -56)
	//	{
	//		position.z -= (30 * dt);
	//	}
	//	else if ((position.z <= -56) && (position.x > 8))
	//	{ 
	//		position.x -= (30 * dt);
	//		direction = 1;
	//	}
	//	else if ((position.z <= -55) && (position.x >= 7))
	//	{
	//		direction = 2;
	//		walkFront = false;
	//		walkBack = true;
	//	}
	//}
	//if ((walkBack == true))// && (walkFront ==false))
	//{
	//	position.z += (30 * dt);
	//}

	// speed
	float Speed = 10.f;
	//Shopper2 Path-ing
	float Shopper2 = 15.f;
	float Shopper2_1= 38.f;
	//float Item_1 = -20.f;
	float Shopper2_2 = 55.f;
	float Shopper2_3 = 30.f;
//	float Item_2 = -21.f;
	float Shopper2_4 = 5.f;
	float Shopper2_5 = 17.f;
	float Shopper2_6 = 9.f;
	float Shopper2_7 = 20.f;
	float Shopper2_EXIT = 36.f;

	//Path 2
	if (ShopperPath2[0] == true)
	{
		
		if (position.z > Shopper2)
		{
			MoveZMinus(Shopper2, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1;
			SetDirection = true;

			if (SetDirection == true)
			{
				
				if (Animate_ON == false)
				{
					ShopperPath2[0] = false;
					ShopperPath2[1] = true;
				}
			}

		}
	}
	if (ShopperPath2[1] == true)
	{
		
		if (position.x > -Shopper2_1)
		{
			MoveXMinus(-Shopper2_1, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 4;
			SetDirection = true;
			item1 = true;

			if (SetDirection == true)
			{
				
				if (Animate_ON == false)
				{
					ShopperPath2[1] = false;
					ShopperPath2[2] = true;
				}
			}
		}
	}
	if (ShopperPath2[2] == true)
	{
		if (position.z > -Shopper2_2)
		{
			MoveZMinus(-Shopper2_2, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 5;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[2] = false;
					ShopperPath2[3] = true;
				}
			}
		}
	}
	if (ShopperPath2[3] == true)
	{
		if (position.x < -Shopper2_3)
		{
			MoveXPlus(-Shopper2_3, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 6;
			item2 = true;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[3] = false;
					ShopperPath2[4] = true;
				}
			}
		}
	}
	if (ShopperPath2[4] == true)
	{
		if (position.z < Shopper2_4)
		{
			MoveZPlus(Shopper2_4, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 8;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[4] = false;
					ShopperPath2[5] = true;
				}
			}
		}
	}
	if (ShopperPath2[5] == true)
	{
		if (position.x < -Shopper2_5)
		{
			MoveXPlus(-Shopper2_5, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 0;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[5] = false;
					ShopperPath2[6] = true;
				}
			}
		}
	}

	if (ShopperPath2[6] == true)
	{
		if (position.z > -Shopper2_2)
		{
			MoveZMinus(-Shopper2_2, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 5;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[6] = false;
					ShopperPath2[7] = true;
				}
			}
		}
	}
	if (ShopperPath2[7] == true)
	{
		if (position.x < -Shopper2_6)
		{
			MoveXPlus(Shopper2_6, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 6;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[7] = false;
					ShopperPath2[8] = true;
				}
			}
		}
	}
	if (ShopperPath2[8] == true)
	{
		if (position.z < Shopper2_7)
		{
			MoveZPlus(Shopper2_7, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 8;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[8] = false;
					ShopperPath2[9] = true;
				}
			}
		}
	}
	if (ShopperPath2[9] == true)
	{
		if (position.z >= Shopper2_7)
		{
			NewState = CShopperAI::Pay;
		}
		if (NewState == CShopperAI::Pay)
		{
			timer++;
			item1 = false;
			item2 = false;
		}
		if (timer == 40)
		{
			NewState = CShopperAI::EXIT;
			Animate_ON = true;
		}
		if (NewState == CShopperAI::EXIT)
		{
			item1 = true;
			item2 = true;
			direction = 6;
			SetDirection = true;
			NewState = CShopperAI::WALK;
			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					timer = 0;
					ShopperPath2[9] = false;
					//NewState = CShopperAI::WALK;
				}
			}
		}
		if (NewState == CShopperAI::WALK)
		{
			ShopperPath2[10] = true;
		}
	}		
	if (ShopperPath2[10] == true)
	{
		if (position.z < Shopper2_EXIT)
		{
			MoveZPlus(Shopper2_EXIT, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			ShopperPath2[10] = false;
			RENDERINGAI = false;
		}
	}
}
void CShopperAI::WalkingPath3(double dt, int NewState)
{
	//#######Rotation of Shoppers#############
	if (SetDirection == true)
	{
		//turn Left's
		if (direction == 0)
		{
			if (Rotangle != 0)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 1)
		{
			if (Rotangle != 90)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 2)
		{
			if (Rotangle != 180)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 3)
		{
			if (Rotangle != 270)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		//Turn Right's
		else if (direction == 4)
		{
			if (Rotangle != 0)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{

				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 5)
		{
			if (Rotangle != -90)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 6)
		{
			if (Rotangle != -180)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 7)
		{
			if (Rotangle != -270)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}

		else if (direction == 8)
		{
			if (Rotangle != -90)
			{
				Rotangle += (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 9)
		{
			if (Rotangle != 90)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 10)
		{
			if (Rotangle != 180)
			{
				Rotangle -= (float)(90 * dt);
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
	}
	float Speed = 10.f;
	//Shopper3 Path-ing
	//Trolley
	float trolley = 30.f;
	float take_trolley = 29.f;
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

	//Path 3
	if (ShopperPath3[0] == true)
	{

		if (position.z > trolley)
		{
			MoveZMinus(trolley, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1;
			SetDirection = true;

			if (SetDirection == true)
			{

				if (Animate_ON == false)
				{
					ShopperPath3[0] = false;
					ShopperPath3[1] = true;
				}
			}

		}
	}
	if (ShopperPath3[1] == true)
	{

		if (position.x > take_trolley)
		{
			MoveXMinus(take_trolley, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 4;
			SetDirection = true;
			RenderTrolley = true;

			if (SetDirection == true)
			{

				if (Animate_ON == false)
				{
					ShopperPath3[1] = false;
					ShopperPath3[2] = true;
				}
			}
		}
	}
	if (ShopperPath3[2] == true)
	{
		if (position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1;
			SetDirection = true;
			item_milo = true;
			item_sardine = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[2] = false;
					ShopperPath3[3] = true;
				}
			}
		}
	}
	if (ShopperPath3[3] == true)
	{
		if (position.x > 7.f)
		{
			MoveXMinus(7.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 2;
			SetDirection = true;
			item_maggie = true;
			item_MnC = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[3] = false;
					ShopperPath3[4] = true;
				}
			}
		}
	}
	if (ShopperPath3[4] == true)
	{
		if (position.z < 2.5f)
		{
			MoveZPlus(2.5f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 9;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[4] = false;
					ShopperPath3[5] = true;
				}
			}
		}
	}
	if (ShopperPath3[5] == true)
	{
		if (position.x > 6.f)
		{
			MoveXMinus(6.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 4;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[5] = false;
					ShopperPath3[6] = true;
				}
			}
		}
	}
	if (ShopperPath3[6] == true)
	{
		if (position.z > -ColdFridgeBack)
		{
			MoveZMinus(-ColdFridgeBack, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1;
			SetDirection = true;
			item_choco = true;
			item_iceCream = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[6] = false;
					ShopperPath3[7] = true;
				}
			}
		}
	}
	if (ShopperPath3[7] == true)
	{
		if (position.x > -16.f)
		{
			MoveXMinus(-16.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 2;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[7] = false;
					ShopperPath3[8] = true;
				}
			}
		}
	}
	if (ShopperPath3[8] == true)
	{
		if (position.z < 6.f)
		{
			MoveZPlus(6.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 3;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[8] = false;
					ShopperPath3[9] = true;
				}
			}
		}
	}
	if (ShopperPath3[9] == true)
	{
		if (position.x < -6.5f)
		{
			MoveXPlus(-6.5f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 10;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[9] = false;
					ShopperPath3[10] = true;
				}
			}
		}
	}
	if (ShopperPath3[10] == true)
	{
		if (position.z < 19.f)
		{
			MoveZPlus(19.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 3;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[10] = false;
					ShopperPath3[11] = true;
				}
			}
		}
	}
	if (ShopperPath3[11] == true)
	{
		if (position.z >= 19.f)
		{
			NewState = CShopperAI::Pay;
			RenderTrolley = false;
			item_choco = false;
			item_iceCream = false;
			item_maggie = false;
			item_milo = false;
			item_MnC = false;
			item_sardine = false;
		}
		if (NewState == CShopperAI::Pay)
		{
			timer++;
		}
		if (timer == 100)
		{
			NewState = CShopperAI::EXIT;
		}
		if (NewState == CShopperAI::EXIT)
		{
			direction = 10;
			SetDirection = true;

			NewState = CShopperAI::WALK;
			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					timer = 0;
					item_choco = true;
					item_iceCream = true;
					item_maggie = true;
					item_milo = true;
					item_MnC = true;
					item_sardine = true;
					RenderTrolley = false;
					ShopperPath3[12] = false;
					//NewState = CShopperAI::WALK;
				}
			}
		}
		if (NewState == CShopperAI::WALK)
		{
			ShopperPath3[12] = true;
		}
	}
	if (ShopperPath3[12] == true)
	{
		if (position.z < 36.f)
		{
			MoveZPlus(36.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			ShopperPath3[12] = false;
			RENDERINGAI = true;
		}
	}
}
//Using Wl'sMethOd
bool CShopperAI::WalkingPath2(double dt) 
{
	//Perform walking
	if (Anim_Wreck == false)
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

	//Paths 1
	if (ShopperPath[0] == true)
	{
		if (position.z > -RedShelfBack)
		{
			MoveZMinus2(-RedShelfBack, dt);
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
		if (position.x > Right_RedShelfRight)
		{
			MoveXMinus2(Right_RedShelfRight, dt);
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
		if (position.z < RedShelfFront)
		{
			MoveZPlus2(RedShelfFront, dt);
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
		if (position.x > Right_RedShelfLeft)
		{
			MoveXMinus2(Right_RedShelfLeft, dt);
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
		if (position.z > -RedShelfBack)
		{
			MoveZMinus2(-RedShelfBack, dt);
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
		if (position.x > FridgeRight)
		{
			MoveXMinus2(FridgeRight, dt);
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
		if (position.z < FridgeFront)

		{
			MoveZPlus2(FridgeFront, dt);
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
		if (position.x > -FridgeLeft)
		{
			MoveXMinus2(-FridgeLeft, dt);
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
		if (position.z > -RedShelfBack)

		{
			MoveZMinus2(-RedShelfBack, dt);
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
		if (position.x > -Left_RedShelfRight)
		{
			MoveXMinus2(-Left_RedShelfRight, dt);
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
		if (position.z < RedShelfFront)

		{
			MoveZPlus2(RedShelfFront, dt);
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
		if (position.x > -Left_RedShelfLeft)
		{
			MoveXMinus2(-Left_RedShelfLeft, dt);
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
		if (position.z > -RedShelfBack)

		{
			MoveZMinus2(-RedShelfBack, dt);
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
		if (position.x > -Left_ColdFridge)
		{
			MoveXMinus2(-Left_ColdFridge, dt);
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
		if (position.z < ColdFridgeFront)

		{
			MoveZPlus2(ColdFridgeFront, dt);
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
		if (position.x < Right_ColdFridge)
		{
			MoveXPlus2(Right_ColdFridge, dt);
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

} //Using Wl'sMethod

void CShopperAI::MoveZPlus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	else if (NewState == CShopperAI::ShopperSTATE)
	{
		Speed = 0.f;
	}
	//Move till stop point
	if (position.z < StopPoint)
	{
		position.z += (float)(dt * Speed);
	}
}
void CShopperAI::MoveZMinus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	//Move till stop point
	if (position.z > StopPoint)
	{
		position.z -= (float)(dt * Speed);
	}
}
void CShopperAI::MoveXPlus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	//Move till stop point
	if (position.x < StopPoint)
	{
		position.x += (float)(dt * Speed);
	}
}
void CShopperAI::MoveXMinus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	//Move till stop point
	if (position.x > StopPoint)
	{
		position.x -= (float)(dt * Speed);
	}
}
//Using Wl'sMethOd
void CShopperAI::MoveZPlus2(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI::WALK)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (position.z < StopPoint)
	{
		position.z += (float)(dt * MovementSpeed);
	}
}
void CShopperAI::MoveZMinus2(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI::WALK)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (position.z > StopPoint)
	{
		position.z -= (float)(dt * MovementSpeed);
	}
}
void CShopperAI::MoveXPlus2(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI::WALK)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (position.x < StopPoint)
	{
		position.x += (float)(dt * MovementSpeed);
	}
}
void CShopperAI::MoveXMinus2(double StopPoint, double dt)
{
	//MovementSpeed based on state
	if (CurrentState == CShopperAI::WALK)
	{
		MovementSpeed = 10.f;
	}
	//Move till stop point
	if (position.x > StopPoint)
	{
		position.x -= (float)(dt * MovementSpeed);
	}
}

void CShopperAI::SetState(int NewState)
{
	CurrentState = NewState;
}
int CShopperAI::GetState(void)
{
	return CurrentState;
}