#ifndef _SCENEMODEL_H
#define _SCENEMODEL_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"

//Wl
#include "Item.h"
#include "Shelf.h"
#include "Inventory.h"
#include "Cashier.h"
#include "VillainAI.h"

//Marcus
#include "Player.h"
#include "GuardAI.h"

//kel
#include"ShopperAI.h"
#include "ShopperAI2.h"

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using std::string;

class SP2: public Scene
{
private:
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION, //Light 1
		U_LIGHT0_TYPE,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION, //Light 2
		U_LIGHT1_TYPE,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHT2_POSITION, //Light 3
		U_LIGHT2_TYPE,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		U_LIGHT3_POSITION, //Light 4
		U_LIGHT3_TYPE,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_LIGHT4_POSITION, //Light 5
		U_LIGHT4_TYPE,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,

		U_LIGHT5_POSITION, //Light 6
		U_LIGHT5_TYPE,
		U_LIGHT5_COLOR,
		U_LIGHT5_POWER,
		U_LIGHT5_KC,
		U_LIGHT5_KL,
		U_LIGHT5_KQ,
		U_LIGHT5_SPOTDIRECTION,
		U_LIGHT5_COSCUTOFF,
		U_LIGHT5_COSINNER,
		U_LIGHT5_EXPONENT,

		U_LIGHT6_POSITION, //Light 7
		U_LIGHT6_TYPE,
		U_LIGHT6_COLOR,
		U_LIGHT6_POWER,
		U_LIGHT6_KC,
		U_LIGHT6_KL,
		U_LIGHT6_KQ,
		U_LIGHT6_SPOTDIRECTION,
		U_LIGHT6_COSCUTOFF,
		U_LIGHT6_COSINNER,
		U_LIGHT6_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_TEXT,
		GEO_FRONT,
		GEO_BACK,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_WALL,
		GEO_COLDSHELVE,
		GEO_CEILING,
		GEO_DOORMAN,
		GEO_STANDER,
		GEO_SHELF,
		GEO_REFRIDGE,
		GEO_THIRDSHELF,
		GEO_SIDESHELF,
		GEO_CASHIERTABLE,
		GEO_CASHIER,
		GEO_CAN_COKE,	//Important!! COKE must be at 20 do not insert anything before
		GEO_CAN_MTNDEW,
		GEO_PACK_KINDER,
		GEO_PACK_SNICKER,
		GEO_BOX_ICECREAM,
		GEO_BOX_PIZZA,
		GEO_BOX_CHOC_CEREAL,
		GEO_BOX_CEREAL,
		GEO_CAN_BEANS,
		GEO_CAN_SARDINES,
		GEO_CAN_ROOTBEER,
		GEO_CAN_MILO,
		GEO_PACK_NOODLE,
		GEO_PACK_TOBLERONE,
		GEO_BOX_CHOCO,
		GEO_ENTRY,
		GEO_UI,
		GEO_SENSOR,
		GEO_LIGHTBULB,
		GEO_TROLLEY,
		GEO_WALLPARTITION,
		GEO_CART,
		GEO_CONVEYORBELT,
		GEO_CONVEYORTABLE,
		GEO_HUMAN_HEAD,
		GEO_HUMAN_BODY,
		GEO_HUMAN_ARM,
		GEO_HUMAN_LEG,

		GEO_GUARD_HEAD,
		GEO_GUARD_BODY,
		GEO_GUARD_ARM,
		GEO_GUARD_LEG,

		GEO_LIGHTBALL1,
		GEO_LIGHTBALL2,
		GEO_LIGHTBALL3,
		GEO_LIGHTBALL4,
		GEO_LIGHTBALL5,
		GEO_LIGHTBALL6,
		GEO_LIGHTBALL7,
		GEO_LIGHTBALL8,
		GEO_LIGHTBALL9,
		GEO_HUMAN_MODEL,

		GEO_WALLET,
		GEO_MONEY,

		GEO_DUSTBIN,
		GEO_BENCH,

		GEO_POLICE,
		NUM_GEOMETRY,
	};

public:
	SP2();
	~SP2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light lights[7];

	double fps;
	float WorldOffset;

	std::string fpsText;

	float textWidth[256];
	int count;

	//Shelf Loading properties
	string ShelfData;
	std::vector<string>ItemTokens;
	char split_char;
	int ItemLine;

	//Conveyor
	bool translateBack;
	float translateZ;
	float translateY;

	//Shopper AI Movement
	bool Rotate_Leg_Left_Back;
	bool Rotate_Leg_Right_Back;
	bool Rotate_Hand_Left_Back;
	bool Rotate_Hand_Right_Back;

	float Rotation_Left_Leg;
	float Rotation_Right_Leg;
	float Rotation_Left_Hand;
	float Rotation_Right_Hand;

	//entrance
	float rotationofdoor;
	bool rotateback;

	//tokens indexing
	enum Index
	{
		NAME,
		PRICE,
		POSX,
		POSY,
		POSZ,
		GEO_TYPE,
		NUM_INDEX,
	};
	//Item Pointer
	CItem *Item;

	//Shelf
	CShelf Container;
	CShelf ColdShelf_Right;
	CShelf ColdShelf_Left;
	CShelf RedShelf_Right;
	CShelf RedShelf_Left;
	CShelf Fridge;

	//Inventory
	CInventory PlayerInvent;
	CInventory Trolley;
	float Delay;
	CInventory AITrolley;

	//Item taking
	float Distance;
	float MaxDistance;

	//Trolley
	float RangeOfOne;

	//Cashier loading properties
	string CashierData;

	//AI Villain loading properties
	CVillainAI *VillainOne;
	int RandomNumber;
	int RandomNumber2;

	//AI Guard loading properties
	CGuardAI Guard;

	//AI Shopper Loading Properties
	CShopperAI ShopperAI;
	CShopperAI2 *Shopper1;

	bool toggleLight;

	//Methods
	 //Updates
	void UpdateGame(double dt);
	void CheckCollision(void);
	void Scenario_Shopper(double dt);
	void Scenario_Guard(double dt);
	void Scenario_Villain(double dt);
	void updateShopperAI(double dt);
	void updateShopperAI2(double dt, CShopperAI2 *Shopper1);
	void UpdateVillainAI(double dt, CVillainAI * Villain);
	void ShowEndScreen(double dt);
	void UpdateConveyor(double dt);
	int RollDice(void);
	void checkItemTypeAdd(CItem *Item);
	void checkItemTypeRemove(CItem *Item);
	int RollDiceVillain(void);
	int RollDiceShopper(void);
	 //Renders
	void RenderGame(void);
	void RenderScenarioShopper(void);
	void RenderScenarioGuard(void);
	void RenderScenarioVillain(void);
	void RenderVillainAI(CVillainAI *Villain);

	void RenderShopperAI2(CShopperAI2 *Shopper1);
	void RenderGuardAI(void);
	
	void RenderShopperAI(void);
	void RenderLights(void);
	void RenderSkyBox();
	void RenderObject();
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderShelfItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber);
	void RenderTrolleyItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber);
	void RenderBeltItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber);
	void RenderUIOnScreen(Mesh* mesh, Color color, float TranslateX, float TranslateY, float degrees, float RotateY, float ScaleX, float ScaleY, float ScaleZ);
	void RenderCashier(void);
	void RenderPlayerArm(void);
	void RenderNPC(void);

	//Player functions
	bool startScreen;
	bool chooseModeScreen;
	bool highScoreScreen;
	bool gameStart;
	bool endScreen;

	CPlayer player;
	bool modeCustomer;
	bool modeGuard;
	bool modeVillain;

	//Customer
	float startingAmount;
	float amountSpent;
	float remaindingAmount;
	float amountOvershot;
	//Villain
	unsigned long long objectsDestroyed;
	bool isCaught;
	//Guard
	bool villainCaught;
	bool villainEscaped;

	bool missionComplete;
	bool missionFailed;

	//Time Taken
	string timeElapsed;
	float elapsedTime;
	string countDownTime;
	float countDown;

	//Highscore in Highscore screen
	string customerHS;
	string guardHS;
	string villainHS;

	string EGSShopper;
	string EGSGuard;
	string EGSVillain;

	bool newHighScore;

	bool renderItemOnTrolley;
	bool beltMovement;
	Vector3 beltPos;
	Vector3 cTablePos;
	float movingOnBelt;

	//Cashier
	bool armMoving;
	bool armMovement;
	float armRotation;

	//Player Animation
	bool playerArmSwipeAni;
	float playerArmSwipe;
	//Right Arm 
	bool playerPayingAni;
	bool playerArmPayingRightAni;
	bool playerArmPayingRightAniDown;
	bool playerArmPayingRightAniUp;
	float playerArmPayingRight;
	bool renderWallet;
	//Left Arm
	bool playerArmPayingLeftAni;
	bool playerArmPayingLeftAniIn;
	bool playerArmPayingLeftAniOut;
	float playerArmPayingLeft;
	bool renderMoney;

	//NPC Interaction
	bool NPCInteraction;

	bool customerCheckOut;

	//Random to choose shopping list
	int randomSL[8];
	stringstream ssSL[8];
	string strSL[8];

	int cokeNo;
	int mtnDewNo;
	int kinderNo;
	int snickerNo;
	int iceCreamNo;
	int pizzaNo;
	int cCerealNo;
	int cerealNo;
	int beansNo;
	int sardineNo;
	int rootbeerNo;
	int miloNo;
	int noodlesNo;
	int tobleroneNo;
	int chocolateNo;

	int inventCokeNo;
	int inventMtnDewNo;
	int inventKinderNo;
	int inventSnickerNo;
	int inventIceCreamNo;
	int inventPizzaNo;
	int inventCCerealNo;
	int inventCerealNo;
	int inventBeansNo;
	int inventSardineNo;
	int inventRootbeerNo;
	int inventMiloNo;
	int inventNoodlesNo;
	int inventTobleroneNo;
	int inventChocolateNo;

	//number of objects destroyed by villain
	string desObj;
};

#endif