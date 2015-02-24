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

//Marcus
#include "Player.h"

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
		U_LIGHT0_POSITION, //Ceiling light
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

		U_LIGHT1_POSITION, //Exterior light
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

	Light lights[2];

	double fps;
	float WorldOffset;

	std::string plXCoord;
	std::string plZCoord;
	std::string fpsText;

	float textWidth[256];
	int count;

	//Shelf Loading properties
	string ShelfData;
	std::vector<string>ItemTokens;
	char split_char;
	int ItemLine;

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

	CItem *Item;
	CShelf Container;
	CInventory PlayerInvent;
	CInventory Trolley;

	//Item taking
	float Distance;
	float MaxDistance;

	//Cashier loading properties
	string CashierData;


	//AI loading properties

	//UI
	int UIIndex;

	bool toggleLight;

	//Methods
	void RenderSkyBox();
	void RenderObject();
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderShelfItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber);
	void RenderTrolleyItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber);
	void RenderUIOnScreen(Mesh* mesh, Color color, float TranslateX, float TranslateY, float degrees, float RotateY, float ScaleX, float ScaleY, float ScaleZ);

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
	int objectsDestroyed;
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
	//Item
	
};

#endif