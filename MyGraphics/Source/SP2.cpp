#include "SP2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Vertex.h"
#include "LoadTGA.h"

#include <iomanip>

SP2::SP2()
{
}

SP2::~SP2()
{
}

void SP2::Init()
{
	//Vars
	fps = 0;
	count = 0;
	split_char = ',';
	ItemLine = 0;
	string TextOnScreen = " ";
	Distance = 0;
	MaxDistance = 3.5;
	WorldOffset = 3.6f;
	translateBack = false;
	translateZ = 3;
	translateY = 0;
	Delay = 0.f;
	std::string data = " ";
	RangeOfOne = 1.f;
	rotationofdoor = 0;
	rotateback = false;

	//ShopperAI Init
	Rotate_Leg_Left_Back = false;
	Rotate_Leg_Right_Back = false;
	Rotate_Hand_Left_Back = false;
	Rotate_Hand_Right_Back = false;

	Rotation_Left_Leg = 0;
	Rotation_Right_Leg = 0;
	Rotation_Left_Hand = 0;
	Rotation_Right_Hand = 0;

	//UI
	//Screen
	startScreen = true;
	chooseModeScreen = false;
	highScoreScreen = false;
	gameStart = false;
	endScreen = false;

	newHighScore = false;

	modeCustomer = false;
	modeGuard = true;
	modeVillain = false;

	missionComplete = false;
	missionFailed = false;

	elapsedTime = 0.f;
	countDown = 180;

	startingAmount = 100;
	amountOvershot = 0;
	remaindingAmount = 0;

	isCaught = false;
	objectsDestroyed = 0;

	villainEscaped = false;
	villainCaught = false;
	
	renderItemOnTrolley = true;
	beltMovement = false;
	beltPos.x = -3.14; 
	beltPos.y = 1.12;
	beltPos.z = 17.33;
	cTablePos.x = -3.15;
	cTablePos.y = -2;
	cTablePos.z = 21.7;

	playerArmSwipeAni = false;

	playerArmPayingRightAniUp = false;
	playerArmPayingRightAniDown = false;

	NPCInteraction = false;

	//UI in shopper mode
	sardineNo = 0;
	miloNo = 0;
	tobleroneNo = 0;
	cokeNo = 0;
	cCerealNo = 0;
	noodlesNo = 0;
	rootbeerNo = 0;
	beansNo = 0;
	pizzaNo = 0;

	//File reading - Non-Monospacing
	std::ifstream inFile;
	inFile.open("Source//charWidth.txt");
	if(inFile.good())
	{
		while(getline(inFile, data))
		{
			textWidth[count] = std::stof(data);
			count++;
		}
		inFile.close();
	}

	//Shelf Item details
	std::ifstream inShelfItem;
	inShelfItem.open("Source//ShelfInfo.txt");
	if(inShelfItem.good())
	{
		while(getline(inShelfItem, ShelfData))
		{
			std::istringstream split(ShelfData);
			if(ShelfData[0] == '#')
			{
				continue;
			}
			for(string each; std::getline(split, each, split_char);)
			{
				ItemTokens.push_back(each);
			}
			//Create new objects
			Item = new CItem;

			Item->SetDetails((ItemTokens.at(SP2::NAME + (ItemLine * SP2::NUM_INDEX)))
				, stod(ItemTokens.at(SP2::PRICE + (ItemLine * SP2::NUM_INDEX)))
				, Vector3(stof(ItemTokens.at(SP2::POSX + (ItemLine * SP2::NUM_INDEX)))
				, stof(ItemTokens.at(SP2::POSY + (ItemLine * SP2::NUM_INDEX)))
				, stof(ItemTokens.at(SP2::POSZ + (ItemLine * SP2::NUM_INDEX))))
				, (ItemTokens.at(SP2::GEO_TYPE + (ItemLine * SP2::NUM_INDEX)))
				, ItemLine);

			ItemLine++;
			Container.Shelf.push_back(Item);
			Init_Container.Shelf.push_back(Item);
		}
		inShelfItem.close();
	}
	//Initialize trolley position
	Trolley.SetPosition(Vector3(30.f, 0.f, 30.f));

	//Cashier details
	armRotation = 0.f;
	armMoving = false;

	//AI details
	srand(time(NULL));
	VillainOne = new CVillainAI;
	RollDiceVillain();
	RollDiceShopper();
	
	Shopper1 = new CShopperAI2;

	Guard.InitGuard(35.0f, -60.0f, 10.0f, 30.0f);

	//Random Shopping List
	for (int i = 0; i < 8 ; i++)	//Random number 
	{
		randomSL[i] = rand() % 14 + 20;
		if(randomSL[i] == 20)
		{
			strSL[i] = "Coke";
			cokeNo++;
		}
		else if(randomSL[i] == 21)
		{
			strSL[i] = "Mountain Dew";
			mtnDewNo++;
		}
		else if(randomSL[i] == 22)
		{
			strSL[i] = "Kinder Bueno";
			kinderNo++;
		}
		else if(randomSL[i] == 23)
		{
			strSL[i] = "Snicker";
			snickerNo++;
		}
		else if(randomSL[i] == 24)
		{
			strSL[i] = "Ice Cream";
			iceCreamNo++;
		}
		else if(randomSL[i] == 25)
		{
			strSL[i] = "Pizza";
			pizzaNo++;
		}
		else if(randomSL[i] == 26)
		{
			strSL[i] = "Chocolate Cereal";
			cCerealNo++;
		}
		else if(randomSL[i] == 27)
		{
			strSL[i] = "Cereal";
			cerealNo++;
		}
		else if(randomSL[i] == 28)
		{
			strSL[i] = "Beans";
			beansNo++;
		}
		else if(randomSL[i] == 29)
		{
			strSL[i] = "Sardine";
			sardineNo++;
		}
		else if(randomSL[i] == 30)
		{
			strSL[i] = "Root Beer";
			rootbeerNo++;
		}
		else if(randomSL[i] == 31)
		{
			strSL[i] = "Milo";
			miloNo++;
		}
		else if(randomSL[i] == 32)
		{
			strSL[i] = "Instant Noodles";
			noodlesNo++;
		}
		else if(randomSL[i] == 33)
		{
			strSL[i] = "Toblerone";
			tobleroneNo++;
		}
		else if(randomSL[i] == 34)
		{
			strSL[i] = "Chocolate";
			chocolateNo++;
		}
	}

	//Sound
	engine = createIrrKlangDevice();

	// Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable back face culling
	glEnable(GL_CULL_FACE);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader" );
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	//Initialize camera settings
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//Initialize all meshes to NULL
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	Init_Collision();
	Init_Lights();
	Init_GEOMS();
	std::cout << Container.Shelf.at(0)->ItemPosition << std::endl;
	std::cout << Init_Container.Shelf.at(0)->ItemPosition << std::endl << std::endl;
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void SP2::RestartGame(void)
{
	//Reinitialize menu screens
	chooseModeScreen = false;
	highScoreScreen = false;
	gameStart = false;
	endScreen = false;
	startScreen = true;

	//Reinitialize Player && Trolley
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	Trolley.Init_Trolley();

	//Reinitialize AI
	VillainOne->Init_Villain();
	ShopperAI.ShopperInitialize();
	Shopper1->ShopperInitialize();
	AITrolley.Init_Inventory();
	
	//Empty player vectors
	PlayerInvent.Init_Inventory();
	Trolley.Init_Inventory();
	
	//Reset shelf item position
	for(int i = 0; i < ItemLine; i++)
	{
		Container.Shelf.at(i)->ItemState = CItem::DEFAULT;
		Container.Shelf.at(i)->SetPosition(Init_Container.Shelf.at(i)->ItemPosition);
	}
	
}

void SP2::Init_Collision(void)
{
	//Initialize shelf position
	ColdShelf_Right.SetShelfPosition(Vector3(40.1f, 0.f, -20.f));
	ColdShelf_Right.SetShelfCollision(6, 78);
	ColdShelf_Left.SetShelfPosition(Vector3(-42.4f, 0.f, -20.f));
	ColdShelf_Left.SetShelfCollision(6, 78);
	RedShelf_Right.SetShelfPosition(Vector3(14.5f, 0.f, -26.f));
	RedShelf_Right.SetShelfCollision(10, 60);
	RedShelf_Left.SetShelfPosition(Vector3(-23.5f, 0.f, -26.f));
	RedShelf_Left.SetShelfCollision(10, 60);
	Fridge.SetShelfPosition(Vector3(-3.f, 0.f, -25.f));
	Fridge.SetShelfCollision(6.2, 54);

	//Initialize Shelf collision
	camera.SetBounds(ColdShelf_Right.MinWidth, ColdShelf_Right.MaxWidth, ColdShelf_Right.MinLength, ColdShelf_Right.MaxLength);
	camera.SetBounds(ColdShelf_Left.MinWidth, ColdShelf_Left.MaxWidth, ColdShelf_Left.MinLength, ColdShelf_Left.MaxLength);
	camera.SetBounds(RedShelf_Right.MinWidth, RedShelf_Right.MaxWidth, RedShelf_Right.MinLength, RedShelf_Right.MaxLength);
	camera.SetBounds(RedShelf_Left.MinWidth, RedShelf_Left.MaxWidth, RedShelf_Left.MinLength, RedShelf_Left.MaxLength);
	camera.SetBounds(Fridge.MinWidth, Fridge.MaxWidth, Fridge.MinLength, Fridge.MaxLength);

	//Initialize Wall collision
	camera.SetBounds(43.f, 48.f, -62.f, 41.f); //Right of super
	camera.SetBounds(-45.f, 45.f, -63.f, -60.f); //Back of super
	camera.SetBounds(-50.f, -44.f, -62.f, 41.f); //Right of super
	camera.SetBounds(4.5f, 33.f, 38.f, 42.f); // _ of L shape wall
	camera.SetBounds(4.f, 8.f, 16.f, 38.f); // | of L shape wall

	//Initialize Exit collision(From Right to left, right is towards entrance)
	camera.SetBounds(2.8f, 4.f, 36.f, 40.f);
	camera.SetBounds(-2.f, 0.5f, 36.f, 40.f);
	camera.SetBounds(-8.f, -5.5f, 36.f, 40.f);
	camera.SetBounds(-14.f, -11.5f, 36.f, 40.f);
	camera.SetBounds(-20.f, -17.5f, 36.f, 40.f);
	camera.SetBounds(-26.f, -23.5f, 36.f, 40.f);
	camera.SetBounds(-32.f, -29.5f, 36.f, 40.f);
	camera.SetBounds(-38.f, -35.5f, 36.f, 40.f);
	camera.SetBounds(-44.f, -41.5f, 36.f, 40.f);

	//Initialize Cashier collision
	camera.SetBounds(-6.f, 3.f, 14.f, 28.f);
	camera.SetBounds(-20.f, -11.f, 14.f, 28.f);
	camera.SetBounds(-35.f, -26.f, 14.f, 28.f);

	//Initialize Food Stand collision
	camera.SetBounds(21.5f, 28.5f, 1.5f, 6.5f);
}

void SP2::Init_Lights(void)
{
		Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 4000.f);
	projectionStack.LoadMatrix(projection);

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID,"lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID,"lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID,"lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID,"lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID,"lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID,"lights[2].exponent");

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID,"lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID,"lights[3].exponent");

	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID,"lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID,"lights[4].exponent");

	m_parameters[U_LIGHT5_POSITION] = glGetUniformLocation(m_programID, "lights[5].position_cameraspace");
	m_parameters[U_LIGHT5_TYPE] = glGetUniformLocation(m_programID, "lights[5].type");
	m_parameters[U_LIGHT5_COLOR] = glGetUniformLocation(m_programID, "lights[5].color");
	m_parameters[U_LIGHT5_POWER] = glGetUniformLocation(m_programID, "lights[5].power");
	m_parameters[U_LIGHT5_KC] = glGetUniformLocation(m_programID, "lights[5].kC");
	m_parameters[U_LIGHT5_KL] = glGetUniformLocation(m_programID, "lights[5].kL");
	m_parameters[U_LIGHT5_KQ] = glGetUniformLocation(m_programID, "lights[5].kQ");
	m_parameters[U_LIGHT5_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[5].spotDirection");
	m_parameters[U_LIGHT5_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[5].cosCutoff");
	m_parameters[U_LIGHT5_COSINNER] = glGetUniformLocation(m_programID,"lights[5].cosInner");
	m_parameters[U_LIGHT5_EXPONENT] = glGetUniformLocation(m_programID,"lights[5].exponent");

	m_parameters[U_LIGHT6_POSITION] = glGetUniformLocation(m_programID, "lights[6].position_cameraspace");
	m_parameters[U_LIGHT6_TYPE] = glGetUniformLocation(m_programID, "lights[6].type");
	m_parameters[U_LIGHT6_COLOR] = glGetUniformLocation(m_programID, "lights[6].color");
	m_parameters[U_LIGHT6_POWER] = glGetUniformLocation(m_programID, "lights[6].power");
	m_parameters[U_LIGHT6_KC] = glGetUniformLocation(m_programID, "lights[6].kC");
	m_parameters[U_LIGHT6_KL] = glGetUniformLocation(m_programID, "lights[6].kL");
	m_parameters[U_LIGHT6_KQ] = glGetUniformLocation(m_programID, "lights[6].kQ");
	m_parameters[U_LIGHT6_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[6].spotDirection");
	m_parameters[U_LIGHT6_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[6].cosCutoff");
	m_parameters[U_LIGHT6_COSINNER] = glGetUniformLocation(m_programID,"lights[6].cosInner");
	m_parameters[U_LIGHT6_EXPONENT] = glGetUniformLocation(m_programID,"lights[6].exponent");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID,"numLights");
	glUseProgram(m_programID);
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0.f, 0.f, 100.f);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1.25f;
	lights[0].kC = 1.0f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_POINT;
	lights[1].position.Set(-20.f, 3.f, -30.f);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 0.6f;
	lights[1].kC = 1.f;
	lights[1].kL = 0.001f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 1.f, 0.f);

	lights[2].type = Light::LIGHT_POINT;
	lights[2].position.Set(0.f, 3.f, -30.f);
	lights[2].color.Set(1, 1, 1);
	lights[2].power = 0.6f;
	lights[2].kC = 1.f;
	lights[2].kL = 0.001f;
	lights[2].kQ = 0.001f;
	lights[2].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[2].cosInner = cos(Math::DegreeToRadian(30));
	lights[2].exponent = 3.f;
	lights[2].spotDirection.Set(0.f, 1.f, 0.f);

	lights[3].type = Light::LIGHT_POINT;
	lights[3].position.Set(20.f, 3.f, -30.f);
	lights[3].color.Set(1, 1, 1);
	lights[3].power = 0.6f;
	lights[3].kC = 1.f;
	lights[3].kL = 0.001f;
	lights[3].kQ = 0.001f;
	lights[3].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[3].cosInner = cos(Math::DegreeToRadian(30));
	lights[3].exponent = 3.f;
	lights[3].spotDirection.Set(0.f, 1.f, 0.f);

	lights[4].type = Light::LIGHT_POINT;
	lights[4].position.Set(-20.f, 3.f, 30.f);
	lights[4].color.Set(1, 1, 1);
	lights[4].power = 0.6f;
	lights[4].kC = 1.f;
	lights[4].kL = 0.001f;
	lights[4].kQ = 0.001f;
	lights[4].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[4].cosInner = cos(Math::DegreeToRadian(30));
	lights[4].exponent = 3.f;
	lights[4].spotDirection.Set(0.f, 1.f, 0.f);

	lights[5].type = Light::LIGHT_POINT;
	lights[5].position.Set(0.f, 3.f, 30.f);
	lights[5].color.Set(1, 1, 1);
	lights[5].power = 0.6f;
	lights[5].kC = 1.f;
	lights[5].kL = 0.001f;
	lights[5].kQ = 0.001f;
	lights[5].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[5].cosInner = cos(Math::DegreeToRadian(30));
	lights[5].exponent = 3.f;
	lights[5].spotDirection.Set(0.f, 1.f, 0.f);

	lights[6].type = Light::LIGHT_POINT;
	lights[6].position.Set(20.f, 3.f, 30.f);
	lights[6].color.Set(1, 1, 1);
	lights[6].power = 0.6f;
	lights[6].kC = 1.f;
	lights[6].kL = 0.001f;
	lights[6].kQ = 0.001f;
	lights[6].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[6].cosInner = cos(Math::DegreeToRadian(30));
	lights[6].exponent = 3.f;
	lights[6].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 3);
	glUniform1i(m_parameters[U_LIGHT2_TYPE], lights[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &lights[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], lights[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], lights[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], lights[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], lights[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], lights[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], lights[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], lights[2].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 4);
	glUniform1i(m_parameters[U_LIGHT3_TYPE], lights[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &lights[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], lights[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], lights[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], lights[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], lights[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], lights[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], lights[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], lights[3].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 5);
	glUniform1i(m_parameters[U_LIGHT4_TYPE], lights[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &lights[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], lights[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], lights[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], lights[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], lights[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], lights[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], lights[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], lights[4].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 6);
	glUniform1i(m_parameters[U_LIGHT5_TYPE], lights[5].type);
	glUniform3fv(m_parameters[U_LIGHT5_COLOR], 1, &lights[5].color.r);
	glUniform1f(m_parameters[U_LIGHT5_POWER], lights[5].power);
	glUniform1f(m_parameters[U_LIGHT5_KC], lights[5].kC);
	glUniform1f(m_parameters[U_LIGHT5_KL], lights[5].kL);
	glUniform1f(m_parameters[U_LIGHT5_KQ], lights[5].kQ);
	glUniform1f(m_parameters[U_LIGHT5_COSCUTOFF], lights[5].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT5_COSINNER], lights[5].cosInner);
	glUniform1f(m_parameters[U_LIGHT5_EXPONENT], lights[5].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 7);
	glUniform1i(m_parameters[U_LIGHT6_TYPE], lights[6].type);
	glUniform3fv(m_parameters[U_LIGHT6_COLOR], 1, &lights[6].color.r);
	glUniform1f(m_parameters[U_LIGHT6_POWER], lights[6].power);
	glUniform1f(m_parameters[U_LIGHT6_KC], lights[6].kC);
	glUniform1f(m_parameters[U_LIGHT6_KL], lights[6].kL);
	glUniform1f(m_parameters[U_LIGHT6_KQ], lights[6].kQ);
	glUniform1f(m_parameters[U_LIGHT6_COSCUTOFF], lights[6].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT6_COSINNER], lights[6].cosInner);
	glUniform1f(m_parameters[U_LIGHT6_EXPONENT], lights[6].exponent);
}

void SP2::Init_GEOMS(void)
{
		//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//HelveticaLTStd-Cond.tga");

	//Skybox
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("UP", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//Skybox_top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("UP", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Skybox_down.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("UP", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Skybox_right.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("UP", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Skybox_left.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("UP", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//Skybox_front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("UP", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Skybox_back.tga");

	//Wall&Floor
	meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("WALL", "OBJ//Wall3.obj");
	meshList[GEO_WALL]->textureID = LoadTGA("Image//Wall2.tga");
	meshList[GEO_WALL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WALL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_WALL]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_WALL]->material.kShininess = 1.f;

	//ColdShelves
	meshList[GEO_COLDSHELVE] = MeshBuilder::GenerateOBJ("ColdShelve", "OBJ//ColdShelves.obj");
	meshList[GEO_COLDSHELVE]->textureID = LoadTGA("Image//ColdShelve.tga");
	meshList[GEO_COLDSHELVE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COLDSHELVE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_COLDSHELVE]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_COLDSHELVE]->material.kShininess = 1.f;

	//Doorman
	meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("Doorman", "OBJ//doorman.obj");
	meshList[GEO_DOORMAN]->textureID = LoadTGA("Image//doorman.tga");
	meshList[GEO_DOORMAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DOORMAN]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_DOORMAN]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_DOORMAN]->material.kShininess = 1.f;

	//Trolley
	meshList[GEO_TROLLEY] = MeshBuilder::GenerateOBJ("Trolley", "OBJ//Trolley.obj");
	meshList[GEO_TROLLEY]->textureID = LoadTGA("Image//Trolley.tga");
	meshList[GEO_TROLLEY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TROLLEY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_TROLLEY]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_TROLLEY]->material.kShininess = 1.f;

	//Stander
	meshList[GEO_STANDER] = MeshBuilder::GenerateOBJ("Stander", "OBJ//Stander.obj");
	meshList[GEO_STANDER]->textureID = LoadTGA("Image//Stander.tga");
	meshList[GEO_STANDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_STANDER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_STANDER]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_STANDER]->material.kShininess = 1.f;

	//Refridge
	meshList[GEO_REFRIDGE] = MeshBuilder::GenerateOBJ("Refridge", "OBJ//Refridge.obj");
	meshList[GEO_REFRIDGE]->textureID = LoadTGA("Image//Refridge.tga");
	meshList[GEO_REFRIDGE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REFRIDGE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_REFRIDGE]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_REFRIDGE]->material.kShininess = 1.f;

	//Shelf
	meshList[GEO_THIRDSHELF] = MeshBuilder::GenerateOBJ("ThirdShelf", "OBJ//thirdShelf.obj");
	meshList[GEO_THIRDSHELF]->textureID = LoadTGA("Image//thirdShelf.tga");
	meshList[GEO_THIRDSHELF]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_THIRDSHELF]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_THIRDSHELF]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_THIRDSHELF]->material.kShininess = 1.f;

	//CashierTable
	meshList[GEO_CASHIERTABLE] = MeshBuilder::GenerateOBJ("SideShelf", "OBJ//CashierTable.obj");
	meshList[GEO_CASHIERTABLE]->textureID = LoadTGA("Image//table.tga");
	meshList[GEO_CASHIERTABLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CASHIERTABLE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CASHIERTABLE]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CASHIERTABLE]->material.kShininess = 1.f;

	//CashierRegister
	meshList[GEO_CASHIER] = MeshBuilder::GenerateOBJ("Cashier", "OBJ//Cashiers.obj");
	meshList[GEO_CASHIER]->textureID = LoadTGA("Image//Cashiers.tga");
	meshList[GEO_CASHIER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CASHIER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CASHIER]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CASHIER]->material.kShininess = 1.f;

	//Shelf Items
	//Coke
	meshList[GEO_CAN_COKE] = MeshBuilder::GenerateOBJ("Can_Coke", "OBJ//Can_Coke0.obj");
	meshList[GEO_CAN_COKE]->textureID = LoadTGA("Image//Can_Coke_Tex.tga");
	meshList[GEO_CAN_COKE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_COKE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_COKE]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CAN_COKE]->material.kShininess = 1.f;

	//Mountain Dew
	meshList[GEO_CAN_MTNDEW] = MeshBuilder::GenerateOBJ("Can_MtnDew", "OBJ//Can_MtnDew.obj");
	meshList[GEO_CAN_MTNDEW]->textureID = LoadTGA("Image//Can_MtnDew_Tex.tga");
	meshList[GEO_CAN_MTNDEW]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_MTNDEW]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_MTNDEW]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CAN_MTNDEW]->material.kShininess = 1.f;

	//Kinder Bueno
	meshList[GEO_PACK_KINDER] = MeshBuilder::GenerateOBJ("Packet_KinderBueno", "OBJ//Packet_KinderBueno.obj");
	meshList[GEO_PACK_KINDER]->textureID = LoadTGA("Image//Packet_KinderBueno_Tex.tga");
	meshList[GEO_PACK_KINDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_KINDER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_KINDER]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_PACK_KINDER]->material.kShininess = 1.f;

	//Snicker
	meshList[GEO_PACK_SNICKER] = MeshBuilder::GenerateOBJ("Packet_Snickers", "OBJ//Packet_Snickers.obj");
	meshList[GEO_PACK_SNICKER]->textureID = LoadTGA("Image//Packet_Snickers_Tex.tga");
	meshList[GEO_PACK_SNICKER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_SNICKER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_SNICKER]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_PACK_SNICKER]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_ICECREAM] = MeshBuilder::GenerateOBJ("Box_IceCream", "OBJ//Box_IceCream.obj");
	meshList[GEO_BOX_ICECREAM]->textureID = LoadTGA("Image//Box_IceCream_Tex.tga");
	meshList[GEO_BOX_ICECREAM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_ICECREAM]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_ICECREAM]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_BOX_ICECREAM]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_PIZZA] = MeshBuilder::GenerateOBJ("Box_Pizza", "OBJ//Box_Pizza.obj");
	meshList[GEO_BOX_PIZZA]->textureID = LoadTGA("Image//Box_Pizza_Tex.tga");
	meshList[GEO_BOX_PIZZA]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_PIZZA]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_PIZZA]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_BOX_PIZZA]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_CHOC_CEREAL] = MeshBuilder::GenerateOBJ("Box_Chocolate_Cereal", "OBJ//Box_Chocolate_Cereal.obj");
	meshList[GEO_BOX_CHOC_CEREAL]->textureID = LoadTGA("Image//Box_ChocolateC_Tex.tga");
	meshList[GEO_BOX_CHOC_CEREAL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_CHOC_CEREAL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_CHOC_CEREAL]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_BOX_CHOC_CEREAL]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_CEREAL] = MeshBuilder::GenerateOBJ("Box_Cereal", "OBJ//Box_Cereal.obj");
	meshList[GEO_BOX_CEREAL]->textureID = LoadTGA("Image//Box_Cereal_Tex.tga");
	meshList[GEO_BOX_CEREAL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_CEREAL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_CEREAL]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_BOX_CEREAL]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_CAN_BEANS] = MeshBuilder::GenerateOBJ("Can_Beans", "OBJ//Can_Beans.obj");
	meshList[GEO_CAN_BEANS]->textureID = LoadTGA("Image//Can_Beans_Tex.tga");
	meshList[GEO_CAN_BEANS]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_BEANS]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_BEANS]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CAN_BEANS]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_CAN_SARDINES] = MeshBuilder::GenerateOBJ("Can_Sardines", "OBJ//Can_Sardines.obj");
	meshList[GEO_CAN_SARDINES]->textureID = LoadTGA("Image//Can_Sardines_Tex.tga");
	meshList[GEO_CAN_SARDINES]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_SARDINES]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_SARDINES]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CAN_SARDINES]->material.kShininess = 5.f;

	//Entry
	meshList[GEO_ENTRY] = MeshBuilder::GenerateOBJ("Cashier", "OBJ//Entry.obj");
	meshList[GEO_ENTRY]->textureID = LoadTGA("Image//Entry.tga");
	meshList[GEO_ENTRY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENTRY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_ENTRY]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_ENTRY]->material.kShininess = 5.f;

	//Rootbeer
	meshList[GEO_CAN_ROOTBEER] = MeshBuilder::GenerateOBJ("Can_Rootbeer", "OBJ//Can_Rootbeer.obj");
	meshList[GEO_CAN_ROOTBEER]->textureID = LoadTGA("Image//Can_Rootbeer_Tex.tga");
	meshList[GEO_CAN_ROOTBEER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_ROOTBEER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_ROOTBEER]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CAN_ROOTBEER]->material.kShininess = 5.f;

	//Milo
	meshList[GEO_CAN_MILO] = MeshBuilder::GenerateOBJ("Can_Milo", "OBJ//Can_Milo.obj");
	meshList[GEO_CAN_MILO]->textureID = LoadTGA("Image//Can_Milo_Tex.tga");
	meshList[GEO_CAN_MILO]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_MILO]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_MILO]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CAN_MILO]->material.kShininess = 5.f;

	//Noodle
	meshList[GEO_PACK_NOODLE] = MeshBuilder::GenerateOBJ("Pack_Noodle", "OBJ//Packet_Noodle.obj");
	meshList[GEO_PACK_NOODLE]->textureID = LoadTGA("Image//Packet_Noodle_Tex.tga");
	meshList[GEO_PACK_NOODLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_NOODLE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_NOODLE]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_PACK_NOODLE]->material.kShininess = 5.f;

	//Toblerone
	meshList[GEO_PACK_TOBLERONE] = MeshBuilder::GenerateOBJ("Pack_Toblerone", "OBJ//Packet_Toblerone.obj");
	meshList[GEO_PACK_TOBLERONE]->textureID = LoadTGA("Image//Packet_Toblerone_Tex.tga");
	meshList[GEO_PACK_TOBLERONE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_TOBLERONE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_TOBLERONE]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_PACK_TOBLERONE]->material.kShininess = 5.f;

	//Chocolate
	meshList[GEO_BOX_CHOCO] = MeshBuilder::GenerateOBJ("Box_Choco", "OBJ//Box_Choco.obj");
	meshList[GEO_BOX_CHOCO]->textureID = LoadTGA("Image//Box_Choco_Tex.tga");
	meshList[GEO_BOX_CHOCO]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_CHOCO]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_CHOCO]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_BOX_CHOCO]->material.kShininess = 5.f;

	//Text
	meshList[GEO_UI] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f);
	meshList[GEO_UI]->textureID = LoadTGA("Image//UI.tga");

	//LightBulb
	meshList[GEO_LIGHTBULB] = MeshBuilder::GenerateOBJ("LightBulb", "OBJ//Lightbulb.obj");
	meshList[GEO_LIGHTBULB]->textureID = LoadTGA("Image//Lightbulb.tga");
	meshList[GEO_LIGHTBULB]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LIGHTBULB]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_LIGHTBULB]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_LIGHTBULB]->material.kShininess = 5.f;

	//Sensor
	meshList[GEO_SENSOR] = MeshBuilder::GenerateOBJ("Sensor", "OBJ//Sensor.obj");
	meshList[GEO_SENSOR]->textureID = LoadTGA("Image//Sensor.tga");
	meshList[GEO_SENSOR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SENSOR]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_SENSOR]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_SENSOR]->material.kShininess = 5.f;

	//Wall Partition
	meshList[GEO_WALLPARTITION] = MeshBuilder::GenerateOBJ("Partition", "OBJ//Partition.obj");
	meshList[GEO_WALLPARTITION]->textureID = LoadTGA("Image//Partition.tga");
	meshList[GEO_WALLPARTITION]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WALLPARTITION]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_WALLPARTITION]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_WALLPARTITION]->material.kShininess = 5.f;

	//ConveyorTable
	meshList[GEO_CONVEYORTABLE] = MeshBuilder::GenerateOBJ("ConveyorTable", "OBJ//Conveyortable.obj");
	meshList[GEO_CONVEYORTABLE]->textureID = LoadTGA("Image//Conveyor.tga");
	meshList[GEO_CONVEYORTABLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CONVEYORTABLE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CONVEYORTABLE]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CONVEYORTABLE]->material.kShininess = 5.f;

	//ConveyorBelt
	meshList[GEO_CONVEYORBELT] = MeshBuilder::GenerateOBJ("Conveyor Strap", "OBJ//Conveyorstrap.obj");
	meshList[GEO_CONVEYORBELT]->textureID = LoadTGA("Image//Conveyor.tga");
	meshList[GEO_CONVEYORBELT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CONVEYORBELT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CONVEYORBELT]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_CONVEYORBELT]->material.kShininess = 5.f;

	//HUMAN
	//head
	meshList[GEO_HUMAN_HEAD] = MeshBuilder::GenerateOBJ("Head", "OBJ//Human_Head.obj");
	meshList[GEO_HUMAN_HEAD]->textureID = LoadTGA("Image//Villain.tga");
	meshList[GEO_HUMAN_HEAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HUMAN_HEAD]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_HUMAN_HEAD]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_HUMAN_HEAD]->material.kShininess = 5.f;
	//Body
	meshList[GEO_HUMAN_BODY] = MeshBuilder::GenerateOBJ("Body", "OBJ//Human_Body.obj");
	meshList[GEO_HUMAN_BODY]->textureID = LoadTGA("Image//Villain.tga");
	meshList[GEO_HUMAN_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HUMAN_BODY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_HUMAN_BODY]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_HUMAN_BODY]->material.kShininess = 5.f;
	//Arm
	meshList[GEO_HUMAN_ARM] = MeshBuilder::GenerateOBJ("Arm", "OBJ//Human_Arm.obj");
	meshList[GEO_HUMAN_ARM]->textureID = LoadTGA("Image//Villain.tga");
	meshList[GEO_HUMAN_ARM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HUMAN_ARM]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_HUMAN_ARM]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_HUMAN_ARM]->material.kShininess = 5.f;
	//Leg
	meshList[GEO_HUMAN_LEG] = MeshBuilder::GenerateOBJ("Leg", "OBJ//Human_Leg.obj");
	meshList[GEO_HUMAN_LEG]->textureID = LoadTGA("Image//Villain.tga");
	meshList[GEO_HUMAN_LEG]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HUMAN_LEG]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_HUMAN_LEG]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_HUMAN_LEG]->material.kShininess = 5.f;

	//GUARD
	//head
	meshList[GEO_GUARD_HEAD] = MeshBuilder::GenerateOBJ("Head", "OBJ//Human_Head.obj");
	meshList[GEO_GUARD_HEAD]->textureID = LoadTGA("Image//Guard.tga");
	meshList[GEO_GUARD_HEAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GUARD_HEAD]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_GUARD_HEAD]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_GUARD_HEAD]->material.kShininess = 5.f;
	//Body
	meshList[GEO_GUARD_BODY] = MeshBuilder::GenerateOBJ("Body", "OBJ//Human_Body.obj");
	meshList[GEO_GUARD_BODY]->textureID = LoadTGA("Image//Guard.tga");
	meshList[GEO_GUARD_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GUARD_BODY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_GUARD_BODY]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_GUARD_BODY]->material.kShininess = 5.f;
	//Arm
	meshList[GEO_GUARD_ARM] = MeshBuilder::GenerateOBJ("Arm", "OBJ//Human_Arm.obj");
	meshList[GEO_GUARD_ARM]->textureID = LoadTGA("Image//Guard.tga");
	meshList[GEO_GUARD_ARM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GUARD_ARM]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_GUARD_ARM]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_GUARD_ARM]->material.kShininess = 5.f;
	//Leg
	meshList[GEO_GUARD_LEG] = MeshBuilder::GenerateOBJ("Leg", "OBJ//Human_Leg.obj");
	meshList[GEO_GUARD_LEG]->textureID = LoadTGA("Image//Guard.tga");
	meshList[GEO_GUARD_LEG]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GUARD_LEG]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_GUARD_LEG]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_GUARD_LEG]->material.kShininess = 5.f;

	//Human Model
	meshList[GEO_HUMAN_MODEL] = MeshBuilder::GenerateOBJ("Sensor", "OBJ//HumanModel.obj");
	//meshList[GEO_HUMAN_MODEL]->textureID = LoadTGA("Image//Conveyor.tga");
	meshList[GEO_HUMAN_MODEL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HUMAN_MODEL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_HUMAN_MODEL]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_HUMAN_MODEL]->material.kShininess = 5.f;

	//Wallet
	meshList[GEO_WALLET] = MeshBuilder::GenerateOBJ("Wallet", "OBJ//Wallet.obj");
	meshList[GEO_WALLET]->textureID = LoadTGA("Image//Wallet.tga");
	meshList[GEO_WALLET]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WALLET]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_WALLET]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_WALLET]->material.kShininess = 5.f;
	//Money
	meshList[GEO_MONEY] = MeshBuilder::GenerateOBJ("Money", "OBJ//Money.obj");
	meshList[GEO_MONEY]->textureID = LoadTGA("Image//Money.tga");
	meshList[GEO_MONEY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MONEY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_MONEY]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_MONEY]->material.kShininess = 5.f;


	meshList[GEO_POLICE] = MeshBuilder::GenerateQuad("Stop", Color(1, 1, 1), 40);
	meshList[GEO_POLICE]->textureID = LoadTGA("Image//ShopTheft.tga");
	meshList[GEO_MONEY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MONEY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_MONEY]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_MONEY]->material.kShininess = 5.f;

	meshList[GEO_DUSTBIN] = MeshBuilder::GenerateOBJ("DustBin", "OBJ//Dustbin.obj");
	meshList[GEO_DUSTBIN]->textureID = LoadTGA("Image//Dustbin.tga");
	meshList[GEO_DUSTBIN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUSTBIN]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_DUSTBIN]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_DUSTBIN]->material.kShininess = 5.f;

	meshList[GEO_BENCH] = MeshBuilder::GenerateOBJ("Bench", "OBJ//Bench.obj");
	meshList[GEO_BENCH]->textureID = LoadTGA("Image//Bench.tga");
	meshList[GEO_BENCH]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BENCH]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BENCH]->material.kSpecular.Set(0.05f, 0.05f, 0.05f);
	meshList[GEO_BENCH]->material.kShininess = 5.f;

}

void SP2::Update(double dt)
{
	if (startScreen == true)
	{
		if (Application::IsKeyPressed('1'))
		{
			chooseModeScreen = true;
			startScreen = false;
			highScoreScreen = false;
			gameStart = false;
			endScreen = false;
		}

		if (Application::IsKeyPressed('2'))
		{
			chooseModeScreen = false;
			startScreen = false;
			highScoreScreen = true;
			gameStart = false;
			endScreen = false;
		}

		if (Application::IsKeyPressed('3'))
		{
			exit(0);
		}
	}

	//Choose Mode
	else if (chooseModeScreen == true)
	{
		if (Application::IsKeyPressed('1')) //Play as Customer
		{
			startScreen = false;
			modeCustomer = true;
			modeGuard = false;
			modeVillain = false;
			chooseModeScreen = false;
			gameStart = true;
		}
		 if (Application::IsKeyPressed('2')) //Play as Security Guard
		{
			startScreen = false;
			modeCustomer = false;
			modeGuard = true;
			modeVillain = false;
			chooseModeScreen = false;
			gameStart = true;
		}
		else if (Application::IsKeyPressed('3')) //Play as Villain
		{
			startScreen = false;
			modeCustomer = false;
			modeGuard = false;
			modeVillain = true;
			chooseModeScreen = false;
			gameStart = true;
		}
	}

	//High score
	else if (highScoreScreen == true)
	{
		//Highscore screen
		std::stringstream customerHighScoreHSS;
		customerHighScoreHSS << player.getShopperHighScore();
		customerHS = customerHighScoreHSS.str();

		std::stringstream guardHighScoreHSS;
		guardHighScoreHSS << player.getGuardHighScore();
		guardHS = guardHighScoreHSS.str();

		std::stringstream villainHighScoreHSS;
		villainHighScoreHSS << player.getVillainHighScore();
		villainHS = villainHighScoreHSS.str();

		if (Application::IsKeyPressed('1'))
		{
			chooseModeScreen = false;
			startScreen = true;
			highScoreScreen = false;
			gameStart = false;
			endScreen = false;
		}
	}

	//Game start
	else if (gameStart == true)
	{
		UpdateGame(dt);
	}
	//Game end
	else if (endScreen == true)
	{
		ShowEndScreen(dt);
	}

	if (beltMovement == true)
	{
		UpdateConveyor(dt);
	}

	if(endScreen == true)
	{
		if(Application::IsKeyPressed(VK_RETURN))
		{
			RestartGame();
		}
	}
}

void SP2::UpdateGame(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	camera.Update(dt);

	player.setPos(camera.position);

	//FPS value
	fps = 1 / dt;
	std::stringstream ss;
	ss << fps;
	fpsText = ss.str();

	//Time Taken
	elapsedTime += (float)(1*dt);
	std::stringstream s_timeElapsed;
	s_timeElapsed << std::fixed << std::setprecision(2) << elapsedTime;
	timeElapsed = s_timeElapsed.str();
	//Count down timer for Guard
	countDown -= (float)(1 * dt);
	std::stringstream s_countDown;
	s_countDown << std::fixed << std::setprecision(2) << countDown;
	countDownTime = s_countDown.str();

	//Player functions
	//Playing as Customer
	if (modeCustomer == true)
	{
		Scenario_Shopper(dt);
	}
	//Playing as Security Guard
	else if (modeGuard == true)
	{
		Scenario_Guard(dt);
	}
	//Playing as Villain
	else if (modeVillain == true)
	{
		Scenario_Villain(dt);
	}

	//Update AI
	UpdateVillainAI(dt, VillainOne);

	updateShopperAI(dt);
	updateShopperAI2(dt, Shopper1);
	Guard.UpdateGuard(player.getPos(), modeCustomer, modeVillain, dt);
	CheckCollision();
	PlaySound();
}

void SP2::PlaySound(void)
{
	//ISound * bgm = engine->play2D("Media//test.mp3", false);
	ISound *TrolleyRolling;
	//Trolley rolling sound
	if(Trolley.EquippedTrolley)
	{
		if(Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D'))
		{
			if(!engine->isCurrentlyPlaying("Media//Trolley.wav")) //Check if sound is playing
			{
				TrolleyRolling = engine->play2D("Media//Trolley.wav", false);      //Plays sound
			}
		}
	}
	//Walking sound
	else if(!Trolley.EquippedTrolley)
	{
		if(Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D'))
		{
			if(!engine->isCurrentlyPlaying("Media//Walking.wav")) //Check if sound is playing
			{
				engine->play2D("Media//Walking.wav", false);      //Plays sound
			}
		}
	}
	//if(Application::IsKeyPressed(VK_SPACE))
	{
		/*if(!engine->isCurrentlyPlaying("Media//test.ogg"))
		engine->play2D("Media//test.ogg", false);*/
	}
	 //TODO BGM?(Environmental sound)
}

void SP2::CheckCollision(void)
{
	if (Trolley.UpdateTrolleyBox(player.getPos()) == true)
		{
			camera.Limiter();
		}
}

void SP2::Scenario_Shopper(double dt)
{
	if(CheckingOut)
	{
		movingOnBelt += (float)(0.5 * dt);
		for(int i = 0; i < Trolley.Inventory.size(); i++)
		{
			//Setting of position of Items on conveyor Belt
			if (camera.position.x > -5 && camera.position.x < -2)
			{
				Trolley.Inventory.at(i)->SetPosition(Vector3(cTablePos.x, cTablePos.y + 3.5, cTablePos.z - 2 * i));
			}
			else if (camera.position.x > -20 && camera.position.x < -17)
			{
				Trolley.Inventory.at(i)->SetPosition(Vector3(cTablePos.x - 15, cTablePos.y + 3.5, cTablePos.z - 2 * i));	
			}
			else if (camera.position.x > -35 && camera.position.x < -32)
			{
				Trolley.Inventory.at(i)->SetPosition(Vector3(cTablePos.x - 30, cTablePos.y + 3.5, cTablePos.z - 2 * i));
			}

			//Render when item is on the conveyor belt
			if (Trolley.Inventory.at(i)->ItemPosition.z + movingOnBelt >  cTablePos.z - 3)
			{
				Trolley.Inventory.at(i)->render = true;
			}
			else
			{
				Trolley.Inventory.at(i)->render = false;
			}
			if (Trolley.Inventory.at(i)->ItemPosition.z + movingOnBelt > cTablePos.z + 0.5)
			{
				Trolley.Inventory.at(i)->render = false;
				if (Trolley.Inventory.at(0)->render == false)
				{
					armMoving = true;
				}
				if(i == Trolley.Inventory.size() - 1)
				{
					renderItemOnTrolley = true;
					beltMovement = false;
					CheckingOut = false;
				}
			}
		}
	}
	//Taking animation
	playerArmSwipe -= (float)(45 * dt);
	if (playerArmSwipe < -90)
	{
		playerArmSwipe = 0.f;
		playerArmSwipeAni = false;
	}
	//Paying animation
	if (playerPayingAni == true)
	{
		if (playerArmPayingRightAni == true)
		{
			if (playerArmPayingRight > 0)
			{
				playerArmPayingRightAni = false;
			}
			else if (playerArmPayingRight < -90)
			{
				renderWallet = true;
				playerArmPayingRightAniUp = true;
				playerArmPayingRightAniDown = false;
			}

			if (playerArmPayingRightAniDown == true)
			{
				playerArmPayingRight -= (float)(30 * dt);
			}
			if (playerArmPayingRightAniUp == true)
			{
				playerArmPayingRight += (float)(30 * dt);
			}
		}

		if (playerArmPayingRightAni == false && playerArmPayingLeftAni == true)
		{
			if (playerArmPayingLeft > 0)
			{
				renderMoney = false;
				playerArmPayingLeftAni = false;
				if(!engine->isCurrentlyPlaying("Media//Cash Register.mp3")) //Check if sound is playing
				{
					engine->play2D("Media//Cash Register.mp3", false);      //Plays cash register sound
				}
			}
			else if (playerArmPayingLeft < -30)
			{
				renderMoney = true;
				playerArmPayingLeftAniOut = true;
				playerArmPayingLeftAniIn = false;
			}

			if (playerArmPayingLeftAniIn == true)
			{
				playerArmPayingLeft -= (float)(30 * dt);
			}
			if (playerArmPayingLeftAniOut == true)
			{
				playerArmPayingLeft += (float)(20 * dt);
			}
		}
	}
	if (renderMoney == false)
	{
		renderWallet = false;
		playerPayingAni = false;
	}

	float RotationSpeed = 100.f;
	float DelayInterval = 1.f;
	if(Delay < DelayInterval)
	{
		Delay += dt;
	}
	if(Delay > DelayInterval)
	{
		//Adding items
		if(Application::IsKeyPressed('E'))
		{
			for(int i = 0; i < ItemLine; i++)
			{
				//Taking items from shelf(Check by invisible box around item)
				if(camera.target.x > Container.Shelf.at(i)->MinWidth && camera.target.x < Container.Shelf.at(i)->MaxWidth
					&& camera.target.y > Container.Shelf.at(i)->MinHeight && camera.target.y < Container.Shelf.at(i)->MaxHeight
					&& camera.target.z > Container.Shelf.at(i)->MinLength && camera.target.z < Container.Shelf.at(i)->MaxLength)
				{
					playerArmSwipeAni = true;
					//Distance is updated
					Distance = (camera.position.x - Container.Shelf.at(i)->ItemPosition.x) 
						+ (camera.position.y - Container.Shelf.at(i)->ItemPosition.y)
						+ (camera.position.z - Container.Shelf.at(i)->ItemPosition.z);

					//Only able to take items when within range and items that are on the shelf
					if(Distance <= MaxDistance && Container.Shelf.at(i)->ItemState == CItem::DEFAULT)
					{
						if(PlayerInvent.Add_ShelfToInvent(Container.Shelf.at(i), i))
						{
							//Play packet grabbing sound
							if(Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_KINDER
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_NOODLE
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_SNICKER
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_TOBLERONE)
							{
								if(!engine->isCurrentlyPlaying("Media//Packet.wav"))
									engine->play2D("Media//Packet.wav", false);
							}
							//Plays box grabbing sound
							if(Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_CEREAL
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_CHOCO
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_CHOC_CEREAL
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_ICECREAM
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_PIZZA)
							{
								if(!engine->isCurrentlyPlaying("Media//Box.wav"))
									engine->play2D("Media//Box.wav", false);
							}
							//Plays can grabbing sound
							if(Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_BEANS
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_COKE
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_MILO
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_MTNDEW
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_ROOTBEER
								||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_SARDINES)
							{
								if(!engine->isCurrentlyPlaying("Media//Can.wav"))
									engine->play2D("Media//Can.wav", false);
							}
							checkItemTypeAdd(Container.Shelf.at(i));
							break;
						}
					}
				}
			}
		}

		//Putting back items back on shelf
		if(Application::IsKeyPressed('G'))
		{
			for(int i = 0; i < ItemLine; i++)
			{
				//Taking of items
				if(camera.target.x > Container.Shelf.at(i)->MinWidth && camera.target.x < Container.Shelf.at(i)->MaxWidth
					&& camera.target.y > Container.Shelf.at(i)->MinHeight && camera.target.y < Container.Shelf.at(i)->MaxHeight
					&& camera.target.z > Container.Shelf.at(i)->MinLength && camera.target.z < Container.Shelf.at(i)->MaxLength)
				{
					//Distance is updated
					Distance = (camera.position.x - Container.Shelf.at(i)->ItemPosition.x) 
						+ (camera.position.y - Container.Shelf.at(i)->ItemPosition.y)
						+ (camera.position.z - Container.Shelf.at(i)->ItemPosition.z);

					//Only able to put back taken items
					if(Distance <= MaxDistance && Container.Shelf.at(i)->ItemState == CItem::TAKEN)
					{
						//Play packet grabbing sound
						if(Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_KINDER
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_NOODLE
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_SNICKER
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_PACK_TOBLERONE)
						{
							if(!engine->isCurrentlyPlaying("Media//Packet.wav"))
								engine->play2D("Media//Packet.wav", false);
						}
						//Plays box grabbing sound
						if(Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_CEREAL
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_CHOCO
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_CHOC_CEREAL
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_ICECREAM
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_BOX_PIZZA)
						{
							if(!engine->isCurrentlyPlaying("Media//Box.wav"))
								engine->play2D("Media//Box.wav", false);
						}
						//Plays can grabbing sound
						if(Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_BEANS
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_COKE
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_MILO
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_MTNDEW
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_ROOTBEER
							||Container.Shelf.at(i)->GEO_TYPE == SP2::GEO_CAN_SARDINES)
						{
							if(!engine->isCurrentlyPlaying("Media//Can.wav"))
								engine->play2D("Media//Can.wav", false);
						}
						checkItemTypeRemove(Container.Shelf.at(i));
						PlayerInvent.Minus_InventToShelf(Container.Shelf.at(i), i);
						break;
					}
				}
			}
		}
		//Swapping items
		if(Application::IsKeyPressed('T'))
		{
			for(int i = 0; i < ItemLine; i++)
			{
				//Taking of items
				if(camera.target.x > Container.Shelf.at(i)->MinWidth && camera.target.x < Container.Shelf.at(i)->MaxWidth
					&& camera.target.y > Container.Shelf.at(i)->MinHeight && camera.target.y < Container.Shelf.at(i)->MaxHeight
					&& camera.target.z > Container.Shelf.at(i)->MinLength && camera.target.z < Container.Shelf.at(i)->MaxLength)
				{
					//Distance is updated
					Distance = (camera.position.x - Container.Shelf.at(i)->ItemPosition.x) 
						+ (camera.position.y - Container.Shelf.at(i)->ItemPosition.y)
						+ (camera.position.z - Container.Shelf.at(i)->ItemPosition.z);

					//Only able to swap with default item
					if(Distance <= MaxDistance && Container.Shelf.at(i)->ItemState == CItem::DEFAULT)
					{
						PlayerInvent.SwapFromInvent(Container.Shelf.at(i), i);
						break;
					}
				}
			}
		}

		if(playerPayingAni == true)
		{
			Trolley.EquippedTrolley = false;
			for(int i = 0; i < ItemLine; i++)
			{
				//Taking of items
				if(camera.target.x > Container.Shelf.at(i)->MinWidth && camera.target.x < Container.Shelf.at(i)->MaxWidth
					&& camera.target.y > Container.Shelf.at(i)->MinHeight && camera.target.y < Container.Shelf.at(i)->MaxHeight
					&& camera.target.z > Container.Shelf.at(i)->MinLength && camera.target.z < Container.Shelf.at(i)->MaxLength)
				{
					//Distance is updated
					Distance = (camera.position.x - Container.Shelf.at(i)->ItemPosition.x) 
						+ (camera.position.y - Container.Shelf.at(i)->ItemPosition.y)
						+ (camera.position.z - Container.Shelf.at(i)->ItemPosition.z);

					//Only able to destroy default items
					if(Distance <= MaxDistance && Container.Shelf.at(i)->ItemState == CItem::DEFAULT)
					{
						Container.Shelf.at(i)->ItemState = CItem::DESTROYED;
						break;
					}
				}
			}
		}
		/*if(renderMoney == false)
		{
			Trolley.EquippedTrolley = true;
		}*/

		//Checkout items
		if(Application::IsKeyPressed(VK_RETURN))
		{
			if(camera.position.x > 35
				&& camera.position.z < -57 
				&& camera.position.z > -61)
			{
				NPCInteraction = true;
			}

			if ((camera.position.x > cTablePos.x - 5
				&& camera.position.x < cTablePos.x - 2
				&& camera.position.z > cTablePos.z - 10
				&& camera.position.z < cTablePos.z - 5)
				|| (camera.position.x > cTablePos.x - 20
				&& camera.position.x < cTablePos.x - 17
				&& camera.position.z > cTablePos.z - 10
				&& camera.position.z < cTablePos.z -5)
				|| (camera.position.x > cTablePos.x - 35
				&& camera.position.x < cTablePos.x - 32
				&& camera.position.z > cTablePos.z - 10
				&& camera.position.z < cTablePos.z - 5 ))
			{
				CheckingOut = true;
				customerCheckOut = true;
				//Paying animation
				playerPayingAni = true;
				playerArmPayingRightAni = true;
				playerArmPayingRightAniDown = true;

				playerArmPayingLeftAni = true;
				playerArmPayingLeftAniIn = true;

				movingOnBelt = 0.f;
				beltMovement = true;
				renderItemOnTrolley = false;
				armRotation = -90.f;

				//Checkout
				for (int i = 0; i < Trolley.Inventory.size(); i++)
				{
					amountSpent += Trolley.Inventory.at(i)->GetPrice();
					Trolley.Inventory.at(i)->CHECKED_OUT;
				}

				int i = 0;
				for(vector<CItem*>::iterator iter = Trolley.Inventory.begin(); iter != Trolley.Inventory.end(); ++iter, i++)
				{
					RenderTrolleyItems((*iter)->ItemName, (*iter)->ItemPrice, Vector3((*iter)->ItemPosition.x, (*iter)->ItemPosition.y, (*iter)->ItemPosition.z), (*iter)->GEO_TYPE, i);
				}
			}
		}
		Delay = 0;
	}

	//Equip Trolley
	if(Application::IsKeyPressed('F'))
	{
		//Equip trolley condition
		if(camera.position.x > Trolley.RotationMinWidth
			&& camera.position.x < Trolley.RotationMaxWidth
			&& camera.position.z > Trolley.RotationMinLength
			&& camera.position.z < Trolley.RotationMaxLength
			&& camera.RotationYAxis > Trolley.TrolleyDirection.y - (RangeOfOne * 3)
			&& camera.RotationYAxis < Trolley.TrolleyDirection.y + (RangeOfOne * 3))
		{
			Trolley.EquippedTrolley = true;
		}
		if(Trolley.EquippedTrolley)
		{
			//Remove items from invent and add to trolley
			for(int i = 0; i < PlayerInvent.Inventory.size(); i++)
			{
				if(Trolley.Add_InventToTrolley(PlayerInvent.Inventory.at(i), PlayerInvent.Inventory.at(i)->ItemIndex))
				{
					PlayerInvent.Minus_InventToTrolley(PlayerInvent.Inventory.at(i), PlayerInvent.Inventory.at(i)->ItemIndex);
					break;
				}
			}
		}
	}
	if(Application::IsKeyPressed('Y'))
	{
		if(Trolley.EquippedTrolley)
		{
			Trolley.EquippedTrolley = false;
			//engine->stopAllSounds(); //Stops playing trolley rolling sound
		}
	}
	
	//Update trolley only when equipped
	if(Trolley.EquippedTrolley)
	{
		if(camera.IsCrouched)
		{
			Trolley.EquippedTrolley = false;
		}
		//CW Rotation
		if(Application::IsKeyPressed(VK_RIGHT))
		{
			Trolley.TrolleyDirection.y -= (float)(RotationSpeed * dt);
			//Reset angle for calculation
			if(Trolley.TrolleyDirection.y <= -180.f)
			{
				Trolley.TrolleyDirection.y = 180.f;
			}
		}
		//CCW Rotation
		if(Application::IsKeyPressed(VK_LEFT))
		{
			//Reset angle for calculation
			Trolley.TrolleyDirection.y += (float)(RotationSpeed * dt);
			if(Trolley.TrolleyDirection.y >= 180.f)
			{
				Trolley.TrolleyDirection.y = -180.f;
			}
		}

		//Update position
		Trolley.SetPosition(Vector3(camera.position.x, camera.position.y, camera.position.z));

		//Update range able to take trolley(+- 1.f range)
		Trolley.RotationMinWidth = cos(Math::DegreeToRadian(Trolley.TrolleyDirection.y)) + Trolley.TrolleyPosition.x - RangeOfOne;
		Trolley.RotationMaxWidth = cos(Math::DegreeToRadian(Trolley.TrolleyDirection.y)) + Trolley.TrolleyPosition.x + RangeOfOne;
		Trolley.RotationMinLength = cos(Math::DegreeToRadian(Trolley.TrolleyDirection.y)) + Trolley.TrolleyPosition.z - RangeOfOne;
		Trolley.RotationMaxLength = cos(Math::DegreeToRadian(Trolley.TrolleyDirection.y)) + Trolley.TrolleyPosition.z + RangeOfOne;

		//Item removal from trolley by keypress
		//TODO: UI for removal
		int input;

		if(Application::IsKeyPressed('1'))
		{
			input = 0;
		}
		if(Application::IsKeyPressed('2'))
		{
			input = 1;
		}
		if(Application::IsKeyPressed('3'))
		{
			input = 2;
		}
		if(Application::IsKeyPressed('4'))
		{
			input = 3;
		}
		if(Application::IsKeyPressed('5'))
		{
			input = 4;
		}
		if(Application::IsKeyPressed('6'))
		{
			input = 5;
		}
		if(Application::IsKeyPressed('7'))
		{
			input = 6;
		}
		if(Application::IsKeyPressed('8'))
		{
			input = 7;
		}
		
		if(input < Trolley.Inventory.size() && PlayerInvent.Inventory.size() < 2)
		{
			if(PlayerInvent.Add_TrolleyToInvent(Trolley.Inventory.at(input), Trolley.Inventory.at(input)->ItemIndex))
			{
				Trolley.Minus_TrolleyToInvent(Trolley.Inventory.at(input), Trolley.Inventory.at(input)->ItemIndex);
			}
		}
	}
	//if(!Trolley.EquippedTrolley)
	//{
	//	camera.TrolleyBounds(Trolley.TrolleyPosition);
	//}
	//If the player shoplifts, the guard will chase after the player
	for (size_t i = 0; i < PlayerInvent.InventoryIndexing.size(); ++i)
	{
		if (player.getPos().z >= 40.0f && Container.Shelf.at(PlayerInvent.InventoryIndexing[i])->ItemState != CItem::CHECKED_OUT)
		{
			Guard.shoplifted = true;
			Guard.setShoplifter(player.getPos());
		}
	}


	//If the guard catches the player for shoplifting, the game ends
	if (Guard.returnState() == "CAUGHT")
	{
		missionComplete = false;
		gameStart = false;
		endScreen = true;
	}

	if (customerCheckOut == true && player.getPos().z > 40.f)
	{
		if (inventCokeNo == cokeNo
			&& inventMtnDewNo == mtnDewNo
			&& inventKinderNo == kinderNo
			&& inventSnickerNo == snickerNo
			&& inventIceCreamNo == iceCreamNo
			&& inventPizzaNo == pizzaNo
			&& inventCCerealNo == cCerealNo
			&& inventCerealNo == cerealNo
			&& inventBeansNo == beansNo
			&& inventSardineNo == sardineNo
			&& inventRootbeerNo == rootbeerNo
			&& inventMiloNo == miloNo
			&& inventNoodlesNo == noodlesNo
			&& inventTobleroneNo == tobleroneNo
			&& inventChocolateNo == chocolateNo)
		{
			missionComplete = true;
		}
		else
		{
			missionComplete = false;
		}

		gameStart = false;
		endScreen = true;
	}
}

void SP2::Scenario_Guard(double dt)
{
	//Catch Villain
	if(Application::IsKeyPressed('X'))
	{
		float DistanceToPlayer = sqrt((VillainOne->GetPosition().x - camera.position.x) * (VillainOne->GetPosition().x - camera.position.x) + (VillainOne->GetPosition().z - camera.position.z) * (VillainOne->GetPosition().z - camera.position.z));

		if(DistanceToPlayer < 0.f)
		{
			DistanceToPlayer *= -1;
		}

		if(DistanceToPlayer < 3.f && VillainOne->RecentlyDestroyed == true)
		{
			VillainOne->SetState(CVillainAI::CAUGHT);
			gameStart = false;
			endScreen = true;
			missionComplete = true;
		}
	}
}

void SP2::Scenario_Villain(double dt)
{
	//Destroying items
	if(Application::IsKeyPressed('E'))
	{
		for(int i = 0; i < ItemLine; i++)
		{
			//Taking of items
			if(camera.target.x > Container.Shelf.at(i)->MinWidth && camera.target.x < Container.Shelf.at(i)->MaxWidth
				&& camera.target.y > Container.Shelf.at(i)->MinHeight && camera.target.y < Container.Shelf.at(i)->MaxHeight
				&& camera.target.z > Container.Shelf.at(i)->MinLength && camera.target.z < Container.Shelf.at(i)->MaxLength)
			{
				//Distance is updated
				Distance = (camera.position.x - Container.Shelf.at(i)->ItemPosition.x) 
					+ (camera.position.y - Container.Shelf.at(i)->ItemPosition.y)
					+ (camera.position.z - Container.Shelf.at(i)->ItemPosition.z);

				//Only able to destroy default items
				if(Distance <= MaxDistance && Container.Shelf.at(i)->ItemState == CItem::DEFAULT)
				{
					Container.Shelf.at(i)->ItemState = CItem::DESTROYED;
					objectsDestroyed++;
					break;
				}
			}
		}
	}
	std::stringstream objDesSS;
	objDesSS << objectsDestroyed;
	desObj = objDesSS.str();

	//If the Guard has caught the player (Villain), the game ends
	if(Guard.returnState() == "CAUGHT")
	{
		gameStart = false;
		endScreen = true;
		missionComplete = false;
		
	}
	//Mission complete
	if (objectsDestroyed >= 15)
	{
		if (player.getPos().z > 40)
		{
			gameStart = false;
			endScreen = true;
			missionComplete = true;
		}
	}
}

void SP2::updateShopperAI(double dt)
{
	//####ANIMATION#####
	//Left Arm
	if (Rotate_Hand_Left_Back == false)
	{
		Rotation_Left_Hand += (float)(40 * dt);
	}
	if (Rotate_Hand_Left_Back == true)
	{
		Rotation_Left_Hand -= (float)(40 * dt);
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
		Rotation_Right_Hand += (float)(40 * dt);
	}
	if (Rotate_Hand_Right_Back == true)
	{
		Rotation_Right_Hand -= (float)(40 * dt);
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
		Rotation_Left_Leg += (float)(40 * dt);
	}
	if (Rotate_Leg_Left_Back == true)
	{
		Rotation_Left_Leg -= (float)(40 * dt);
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
		Rotation_Right_Leg += (float)(40 * dt);
	}
	if (Rotate_Leg_Right_Back == true)
	{
		Rotation_Right_Leg -= (float)(40 * dt);
	}
	if (Rotation_Right_Leg >= 30)
	{
		Rotate_Leg_Right_Back = true;
	}
	if (Rotation_Right_Leg <= -30)
	{
		Rotate_Leg_Right_Back = false;
	}
	//UpdateSHopperAI
	ShopperAI.UpdatePath(dt, camera.position);

}

void SP2::updateShopperAI2(double dt, CShopperAI2 *Shopper1)
{
	if (Shopper1->TakingItem(Container.Shelf.at(RandomNumber2), dt) == true)
	{
		AITrolley.Add_ShelfToTrolley(Container.Shelf.at(RandomNumber2), RandomNumber2);
		RollDiceShopper();
	}
	//Shopper Taking with rotation
	else if (Shopper1->Anime_Take == true)
	{
		if (Shopper1->ItemAtLeft)
		{
			Shopper1->SetDirection(Vector3(0.f, -90.f + 90.f * (float)(Shopper1->RotateLeft), 0.f), dt);
			
		}
		else if (Shopper1->ItemAtRight)
		{
			Shopper1->SetDirection(Vector3(0.f, -90.f + 90.f * (float)(Shopper1->RotateLeft), 0.f), dt);
		}
	}
	//Shopper rotation ONLY
	else if (Shopper1->Anim_Rotate == true && Shopper1->Anime_Take == false)
	{
		Shopper1->SetDirection(Vector3(0, 90.f * (float)(Shopper1->RotateLeft), 0), dt);
		AITrolley.SetDirection(Vector3(Shopper1->GetDirection()));
	}
	else
	{
		Shopper1->UpdateAI(dt, camera.position);
	}
}

void SP2::UpdateVillainAI(double dt, CVillainAI * Villain)
{

	//Reroll random number when item is destroyed
	if(Villain->DestroyItem(Container.Shelf.at(RandomNumber), dt) == true)
	{
		RollDiceVillain();
	}
	//Villain wrecking with rotation
	else if(Villain->Anim_Wreck == true)
	{
		if(Villain->ItemAtLeft)
		{
			Villain->SetDirection(Vector3(0.f, -90.f + 90.f * (float)(Villain->RotateLeft), 0.f), dt);
		}
		else if(Villain->ItemAtRight)
		{
			Villain->SetDirection(Vector3(0.f, -90.f + 90.f * (float)(Villain->RotateLeft), 0.f), dt);
		}
	}	
	//Villain rotation ONLY
	else if(Villain->Anim_Rotate == true && Villain->Anim_Wreck == false)
	{
		Villain->SetDirection(Vector3(0, 90.f * (float)(Villain->RotateLeft), 0), dt);
	}	
	else
	{
		Villain->UpdateAI(dt, camera.position);
	}
	
	//Guard.UpdateGuard(dt, camera.position);
}

int SP2::RollDiceVillain(void)
{
	RandomNumber = rand() % ItemLine;
	//Filtering out items that are too far
	while(Container.Shelf.at(RandomNumber)->ItemState != CItem::DEFAULT 
		|| Container.Shelf.at(RandomNumber)->ItemPosition.x > 41.6f
		|| Container.Shelf.at(RandomNumber)->ItemPosition.x < -43.5f)
	{
		RandomNumber = rand() % ItemLine;
	}
	return RandomNumber;

}

int SP2::RollDiceShopper(void)
{
	RandomNumber2 = rand() % ItemLine;
	while (Container.Shelf.at(RandomNumber2)->ItemState != CItem::DEFAULT
		|| Container.Shelf.at(RandomNumber2)->ItemPosition.x > 41.6f
		|| Container.Shelf.at(RandomNumber2)->ItemPosition.x < -43.5f
		|| RandomNumber2 == RandomNumber)
	{
		RandomNumber2 = rand() % ItemLine;
	}
	return RandomNumber2;
}

void SP2::ShowEndScreen(double dt)
{
	chooseModeScreen = false;
	startScreen = false;
	highScoreScreen = false;
	gameStart = false;

	if (player.getShopperScore() > player.getShopperHighScore() || player.getGuardScoreSucceed() > player.getGuardHighScore() || player.getVillainScore() > player.getVillainHighScore())
	{
		newHighScore = true;
	}
	else
	{
		newHighScore = false;
	}

	//Shopper
	std::stringstream customerEGS;
	customerEGS << player.getShopperScore();
	EGSShopper = customerEGS.str();

	//Guard
	std::stringstream guardEGS;
	guardEGS << player.getGuardScoreSucceed();
	EGSGuard = guardEGS.str();

	//Villain
	std::stringstream villainEGS;
	villainEGS << player.getVillainScore();
	EGSVillain = villainEGS.str();

	if (Application::IsKeyPressed('1'))
	{
		chooseModeScreen = false;
		startScreen = true;
		highScoreScreen = false;
		gameStart = false;
		endScreen = false;
	}

	//Score calculation
	if (modeCustomer == true)
	{
		//Calculate score & Set high score
		if (missionComplete == true)
		{
			player.setShopperScoreSucceed(elapsedTime);
			//Set high score
			player.setShopperHighScore(player.getShopperScore());
		}
		else
		{
			player.setShopperScoreFailed(elapsedTime);
			//Set high score
			player.setShopperHighScore(player.getShopperScore());
		}
	}

	else if (modeGuard == true)
	{
		if (missionComplete == true)
		{
			player.setGuardScoreSucceed(elapsedTime);
			//Set high score
			player.setGuardHighScore(player.getGuardScoreSucceed());
		}
	}

	else if (modeVillain == true)
	{
		if (missionComplete == true)
		{
			player.setVillainScoreSucceed(elapsedTime);
			//Set high score
			player.setVillainHighScore(player.getVillainScore());
		}
		else
		{
			player.setVillainScoreFailed(objectsDestroyed);
			//Set high score
			player.setVillainHighScore(player.getVillainScore());
		}
	}
}

void SP2::UpdateConveyor(double dt)
{
	//ConveyorBelt code
	//white
	if (translateBack == false)
	{
		if (beltMovement == true)
		{
			translateZ += (float)(0.5 * dt);
		}
	}
	else
	{
		translateZ = 0.1 ;
	}
	if (translateZ >= 8.75)
	{
		translateBack = true;
		translateY = -0.1;
	}
	else if (translateZ <= 0.4)
	{
		translateBack = false;
		translateY = 0;
	}

	if (armMoving == true)
	{
		if(armMovement == true)
		{
			armRotation += (float)(80 * dt);
			if(armRotation > 0)
			{
				armMovement = false;
			}
		}
		else
		{
			armRotation -= (float)(30 * dt);
			if(armRotation < -90)
			{
				armMovement = true;
				if(!engine->isCurrentlyPlaying("Media//Beep.wav")) //Check if sound is playing
				{
					engine->play2D("Media//Beep.wav", false);      //Plays beeping sound
				}
			}
		}
	}

}

void SP2::checkItemTypeAdd(CItem *Item)
{
	if (Item->GEO_TYPE == SP2::GEO_CAN_COKE)
		inventCokeNo++;
	if (Item->GEO_TYPE == SP2::GEO_CAN_MTNDEW)
		inventMtnDewNo++;
	if (Item->GEO_TYPE == SP2::GEO_PACK_KINDER)
		inventKinderNo++;
	if (Item->GEO_TYPE == SP2::GEO_PACK_SNICKER)
		inventSnickerNo++;
	if (Item->GEO_TYPE == SP2::GEO_BOX_ICECREAM)
		inventIceCreamNo++;
	if (Item->GEO_TYPE == SP2::GEO_BOX_PIZZA)
		inventPizzaNo++;
	if (Item->GEO_TYPE == SP2::GEO_BOX_CHOC_CEREAL)
		inventCCerealNo++;
	if (Item->GEO_TYPE == SP2::GEO_BOX_CEREAL)
		inventCerealNo++;
	if (Item->GEO_TYPE == SP2::GEO_CAN_BEANS)
		inventBeansNo++;
	if (Item->GEO_TYPE == SP2::GEO_CAN_SARDINES)
		inventSardineNo++;
	if (Item->GEO_TYPE == SP2::GEO_CAN_ROOTBEER)
		inventRootbeerNo++;
	if (Item->GEO_TYPE == SP2::GEO_CAN_MILO)
		inventMiloNo++;
	if (Item->GEO_TYPE == SP2::GEO_PACK_NOODLE)
		inventNoodlesNo++;
	if (Item->GEO_TYPE == SP2::GEO_PACK_TOBLERONE)
		inventTobleroneNo++;
	if (Item->GEO_TYPE == SP2::GEO_BOX_CHOCO)
		inventChocolateNo++;
}

void SP2::checkItemTypeRemove(CItem *Item)
{
	if (Item->GEO_TYPE == SP2::GEO_CAN_COKE)
		inventCokeNo--;
	if (Item->GEO_TYPE == SP2::GEO_CAN_MTNDEW)
		inventMtnDewNo--;
	if (Item->GEO_TYPE == SP2::GEO_PACK_KINDER)
		inventKinderNo--;
	if (Item->GEO_TYPE == SP2::GEO_PACK_SNICKER)
		inventSnickerNo--;
	if (Item->GEO_TYPE == SP2::GEO_BOX_ICECREAM)
		inventIceCreamNo--;
	if (Item->GEO_TYPE == SP2::GEO_BOX_PIZZA)
		inventPizzaNo--;
	if (Item->GEO_TYPE == SP2::GEO_BOX_CHOC_CEREAL)
		inventCCerealNo--;
	if (Item->GEO_TYPE == SP2::GEO_BOX_CEREAL)
		inventCerealNo--;
	if (Item->GEO_TYPE == SP2::GEO_CAN_BEANS)
		inventBeansNo--;
	if (Item->GEO_TYPE == SP2::GEO_CAN_SARDINES)
		inventSardineNo--;
	if (Item->GEO_TYPE == SP2::GEO_CAN_ROOTBEER)
		inventRootbeerNo--;
	if (Item->GEO_TYPE == SP2::GEO_CAN_MILO)
		inventMiloNo--;
	if (Item->GEO_TYPE == SP2::GEO_PACK_NOODLE)
		inventNoodlesNo--;
	if (Item->GEO_TYPE == SP2::GEO_PACK_TOBLERONE)
		inventTobleroneNo--;
	if (Item->GEO_TYPE == SP2::GEO_BOX_CHOCO)
		inventChocolateNo--;
}

void SP2::Render()
{
	//Start Screen
	if (startScreen == true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderTextOnScreen(meshList[GEO_TEXT], "Start Game", Color (1, 1, 1), 4.f, 8.5f, 7.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "High Score", Color (1, 1, 1), 4.f, 8.5f, 6.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color (1, 1, 1), 4.f, 9.3f, 5.f);
	}
	if (chooseModeScreen == true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderTextOnScreen(meshList[GEO_TEXT], "Play as Customer", Color (1, 1, 1), 4.f, 8.f, 7.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Play as Security Guard", Color (1, 1, 1), 4.f, 8.f, 6.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Play as Villain", Color (1, 1, 1), 4.f, 8.f, 5.f);
	}
	if (highScoreScreen == true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderTextOnScreen(meshList[GEO_TEXT], "Customer:"+customerHS, Color (1, 0, 0), 4.f, 8.f, 7.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Security Guard:"+guardHS, Color (1, 0, 0), 4.f, 8.f, 6.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Villain:"+villainHS, Color (1, 0, 0), 4.f, 8.f, 5.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main Menu ", Color (1, 1, 1), 4.f, 7.5f, 4.f);
	}

	//End Game Screen
	if (endScreen == true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (modeCustomer == true)
		{
			if (Guard.returnState() == "CAUGHT")
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, -15, 0);
			RenderMesh(meshList[GEO_POLICE], false);
			modelStack.PopMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Game Over! - Shoplifting is a CRIME!", Color (1, 0, 0), 5.f, 2.5f, 11.f);
		}
			RenderTextOnScreen(meshList[GEO_TEXT], "Score:", Color (0, 1, 0), 5.f, 7.5f, 8.f);
			RenderTextOnScreen(meshList[GEO_TEXT], EGSShopper, Color (0, 1, 0), 5.f, 8.f, 7.f);
		}
		else if (modeGuard == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Score:", Color (1, 1, 1), 5.f, 7.5f, 8.f);
			RenderTextOnScreen(meshList[GEO_TEXT], EGSGuard, Color (1, 1, 1), 5.f, 8.f, 7.f);
		}
		else if (modeVillain == true)
		{
			if (Guard.returnState() == "CAUGHT")
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Game Over! - The Security Guard caught you!", Color (1, 1, 1), 5.f, 1.5f, 11.f);
			}
			RenderTextOnScreen(meshList[GEO_TEXT], "Score:", Color (1, 1, 1), 5.f, 7.5f, 8.f);
			RenderTextOnScreen(meshList[GEO_TEXT], EGSVillain, Color (1, 1, 1), 5.f, 8.f, 7.f);
		}

		RenderTextOnScreen(meshList[GEO_TEXT], "Return to Main Menu", Color (1, 1, 1), 4.f, 7.5f, 3.f);
		if (newHighScore == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "NEW HIGHSCORE! ", Color (1, 1, 1), 6.f, 4.5f, 8.f);
		}
	}

	if (gameStart == true)
	{
		RenderGame();
	}
}

void SP2::RenderGame(void)
{
	float textSize = 3.f;

	RenderLights();

	modelStack.PushMatrix();
	modelStack.Translate(-20.f, 0.f, -20.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	float a = 0.1f;
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -WorldOffset, 0);
	RenderSkyBox();
	RenderObject();

	//Render Items on shelf
	for(int i = 0; i < ItemLine; i++)
	{
		RenderShelfItems(Container.Shelf.at(i)->ItemName, Container.Shelf.at(i)->ItemPrice, Vector3(Container.Shelf.at(i)->ItemPosition.x, Container.Shelf.at(i)->ItemPosition.y, Container.Shelf.at(i)->ItemPosition.z), Container.Shelf.at(i)->GEO_TYPE, i);
	}

	//Render AI models
	RenderVillainAI(VillainOne);
	modelStack.PopMatrix();

	//Render Guard AI Model
	RenderGuardAI();

	//Render Shopper AI Models
	
	RenderShopperAI2(Shopper1);
	RenderShopperAI();

	//Text display for FPS(Remove X,Z before submission)
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:"+fpsText, Color(1, 0, 0), textSize, 22.5f, 19.f);
	if (modeCustomer == true || modeVillain == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], timeElapsed, Color (1, 1, 1), 5.f, 8.f, 11.f);
	}
	else if (modeGuard == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], countDownTime, Color (1, 1, 1), 5.f, 8.f, 11.f);
	}

	if (modeCustomer == true)
	{
		RenderScenarioShopper();
	}
	else if (modeVillain == true)
	{
		RenderScenarioVillain();
	}
	else if (modeGuard == true)
	{
		RenderScenarioGuard();
	}
}

void SP2::RenderLights(void)
{
	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();
	//Light arrangement
	// 1  2  3
	// 4  5  6 x - Entrance

	//Directional Light
	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Mtx44 rotation;
		rotation.SetToRotation(90.f, 1.f, 0.f, 0.f);
		Vector3 lightDirection_cameraspace = viewStack.Top() * rotation * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//Light 1
	if(lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);	
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);

		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//Light 2
	if(lights[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[2].position.x, lights[2].position.y, lights[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);

		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//Light 3
	if(lights[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[3].position.x, lights[3].position.y, lights[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);

		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//Light 4
	if(lights[4].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[4].position.x, lights[4].position.y, lights[4].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[4].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);

		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[4].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT4_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//Light 5
	if(lights[5].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[5].position.x, lights[5].position.y, lights[5].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[5].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[5].position;
		glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightPosition_cameraspace.x);

		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[5].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT5_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[5].position;
		glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//Light 6
	if(lights[6].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[6].position.x, lights[6].position.y, lights[6].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT6_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[6].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[6].position;
		glUniform3fv(m_parameters[U_LIGHT6_POSITION], 1, &lightPosition_cameraspace.x);

		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[6].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT6_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[6].position;
		glUniform3fv(m_parameters[U_LIGHT6_POSITION], 1, &lightPosition_cameraspace.x);
	}

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
}

void SP2::RenderScenarioShopper(void)
{
	//Player Arms
	//Render Player Arms
	if (Trolley.EquippedTrolley == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x , camera.position.y, camera.position.z);
		modelStack.Rotate(camera.playerArmRotation, 0, 1, 0);

		modelStack.PushMatrix();
		modelStack.Translate(-1, -2, 0.25);
		modelStack.Rotate(90, 1, 0, 0);
		RenderMesh(meshList[GEO_HUMAN_ARM], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1, -2, 0.25);
		modelStack.Rotate(90, 1, 0, 0);
		RenderMesh(meshList[GEO_HUMAN_ARM], true);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
	else if (playerArmSwipeAni == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x , camera.position.y, camera.position.z);
		modelStack.Rotate(camera.playerArmRotation, 0, 1, 0);

		modelStack.PushMatrix();
		modelStack.Translate(-1.5, -1.5, -1);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Translate(-1, 0, 0);
		modelStack.Rotate(-playerArmSwipe, 0, 0, 1);
		RenderMesh(meshList[GEO_HUMAN_ARM], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.5, -1.5, -1);
		modelStack.Rotate(90, 1, 0, 0);
		RenderMesh(meshList[GEO_HUMAN_ARM], true);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
	else if (playerPayingAni == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x , camera.position.y, camera.position.z);
		modelStack.Rotate(camera.playerArmRotation, 0, 1, 0);

		modelStack.PushMatrix();
		modelStack.Translate(-1.5, -1.5, -1);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(-playerArmPayingLeft, 0, 0, 1);
		RenderMesh(meshList[GEO_HUMAN_ARM], true);
		if(renderMoney == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0.5, -3, 0);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Rotate(60, 0, 1, 0);
			//modelStack.Rotate(-20, 0, 0, 1);
			RenderMesh(meshList[GEO_MONEY], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.5, -1.5, -1);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(playerArmPayingRight, 1, 0, 0);
		RenderMesh(meshList[GEO_HUMAN_ARM], true);
		if(renderWallet == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-0.5, -3, 0.5);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Rotate(-45, 0, 1, 0);
			RenderMesh(meshList[GEO_WALLET], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
	else
	{
		RenderPlayerArm();
	}

	float difference = -4.0;
	float angle = Trolley.TrolleyDirection.y * M_PI / 180.0f;
	float s = sin(angle);
	float c = cos(angle);
	Vector3 newTrolley(Trolley.TrolleyPosition.x + (difference * s) + (difference * c), 0.0f, Trolley.TrolleyPosition.x + (difference * c) + (difference * s));

	long double xvalue = static_cast<double>(Trolley.Offset.x);
	long double zvalue = static_cast<double>(Trolley.Offset.z);
	long double xXvalue = static_cast<double>(s);
	long double zZvalue = static_cast<double>(c);
	long double Yvalue = static_cast<double>(angle);

	//UI Rendering
	int UI_PlayerStart = 10;
	int PlayerDifference = 12;
	int PlayerIncrement  = PlayerDifference /2;
	int UI_PlayerEnd = UI_PlayerStart + PlayerDifference;

	int UI_TrolleyStart = 30;
	int TrolleyDifference = 48;
	int TrolleyIncrement = TrolleyDifference / 8;
	int UI_TrolleyEnd = UI_TrolleyStart + TrolleyDifference;

	int UI_PlayerIndex = 0;
	int UI_TrolleyIndex = 0;
	
	//Inventory rendering
	for(int i = UI_PlayerStart; i < UI_PlayerEnd; i+= PlayerIncrement)
	{
		RenderUIOnScreen(meshList[GEO_UI], Color(1, 0 , 0), i, 5.f, 0.f, 1.f, 6.f, 6.f, 1.f);
	}
	for(vector<CItem*>::iterator iter = PlayerInvent.Inventory.begin(); iter != PlayerInvent.Inventory.end(); iter++, UI_PlayerIndex++)
	{
		RenderUIOnScreen((meshList[(*iter)->GEO_TYPE]), Color(), UI_PlayerStart + (UI_PlayerIndex * PlayerIncrement), 5.f, 90.f, 1.f, 1.f, 3.f, 3.f);
	}
	//Trolley rendering
	for(int i = UI_TrolleyStart; i < UI_TrolleyEnd; i+= TrolleyIncrement)
	{
		RenderUIOnScreen(meshList[GEO_UI], Color(1, 0 , 0), i, 5.f, 0.f, 1.f, 6.f, 6.f, 1.f);
	}
	if (renderItemOnTrolley == true)
	{
		for(vector<CItem*>::iterator iter = Trolley.Inventory.begin(); iter != Trolley.Inventory.end(); iter++, UI_TrolleyIndex++)
		{
			RenderUIOnScreen((meshList[(*iter)->GEO_TYPE]), Color(), UI_TrolleyStart + (UI_TrolleyIndex * TrolleyIncrement), 5.f, 90.f, 1.f, 1.f, 3.f, 3.f);
		}
	}

	//Rendering Text
	RenderTextOnScreen(meshList[GEO_TEXT], "Shopping Cart:", Color(0.2, 0.87, 0.87), 3.f, 9.5f, 3.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "On hand:", Color(0.2, 0.87, 0.87), 3.f, 2.8f, 3.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "Objective:", Color(0.2, 0.87, 0.87), 3.f, 0.5f, 13.f);
	//Goals
	float y = 14.5f;
	for (int i = 0; i < 8; i++)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], strSL[i], Color(1, 0, 0), 2.5f, 0.5f, y);
		y--;
	} 

	if ((camera.position.x > cTablePos.x - 5
				&& camera.position.x < cTablePos.x - 2
				&& camera.position.z > cTablePos.z - 10
				&& camera.position.z < cTablePos.z - 5)
				|| (camera.position.x > cTablePos.x - 20
				&& camera.position.x < cTablePos.x - 17
				&& camera.position.z > cTablePos.z - 10
				&& camera.position.z < cTablePos.z -5)
				|| (camera.position.x > cTablePos.x - 35
				&& camera.position.x < cTablePos.x - 32
				&& camera.position.z > cTablePos.z - 10
				&& camera.position.z < cTablePos.z - 5 ))
	{
		if(Trolley.EquippedTrolley == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Enter' to check out", Color (0, 1, 0), 2.5f, 7.f, 5.5f);
		}
	}
	if(camera.position.x > Trolley.RotationMinWidth
			&& camera.position.x < Trolley.RotationMaxWidth
			&& camera.position.z > Trolley.RotationMinLength
			&& camera.position.z < Trolley.RotationMaxLength
			&& camera.RotationYAxis > Trolley.TrolleyDirection.y - (RangeOfOne * 3)
			&& camera.RotationYAxis < Trolley.TrolleyDirection.y + (RangeOfOne * 3))
	{
		if(Trolley.EquippedTrolley == false)
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'F' to take Trolley", Color (0, 1, 0), 2.5f, 7.f, 4.5f);
		else
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Y' to let go of Trolley", Color (0, 1, 0), 2.5f, 7.f, 4.5f);
	}
	if (NPCInteraction == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(42, 1, -59);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderText(meshList[GEO_TEXT], "Weed?", Color(0, 1, 0));
		modelStack.PopMatrix();
	}
}

void SP2::RenderScenarioVillain(void)
{
	RenderPlayerArm();
	RenderTextOnScreen(meshList[GEO_TEXT], "Objective:", Color(0.2, 0.87, 0.87), 3.f, 0.5f, 13.f);
	if (objectsDestroyed < 15)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Objects:"+desObj+"/15", Color(1, 0, 0), 2.5f, 0.5f, 14.f);
	}
	if (objectsDestroyed >= 15)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Objects:"+desObj+"/15", Color(0, 1, 0), 2.5f, 0.5f, 14.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Escape from the supermarket", Color(1, 0, 0), 2.5f, 0.5f, 13.f);
	}
}

void SP2::RenderScenarioGuard(void)
{
	RenderPlayerArm();
	RenderTextOnScreen(meshList[GEO_TEXT], "Objective:", Color(0.2, 0.87, 0.87), 3.f, 0.5f, 13.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "Villain 0/1", Color(1, 0, 0), 2.5f, 0.5f, 13.5f);
}

void SP2::RenderVillainAI(CVillainAI *Villain)
{
	modelStack.PushMatrix();

	modelStack.Translate(Villain->GetPosition().x, Villain->GetPosition().y, Villain->GetPosition().z);
	modelStack.Rotate(Villain->GetDirection().y + 180.f, 0.f, 1.f, 0.f);

	//Default walking animation
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_HUMAN_BODY], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.95, 0);
	RenderMesh(meshList[GEO_HUMAN_HEAD], false);
	modelStack.PopMatrix(); // Pop Head

	modelStack.PushMatrix();
	modelStack.Translate(1, 2.3, 0);
	modelStack.Rotate(Villain->Rotation_Left_Hand,1,0,0);
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //Left
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 2.3, 0);
	modelStack.Rotate(Villain->Rotation_Right_Hand, -1, 0, 0);
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //right
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.3, -0.05, 0);
	modelStack.Rotate(Villain->Rotation_Left_Leg, -1, 0,0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //left
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.3, -0.05, 0);
	modelStack.Rotate(Villain->Rotation_Right_Leg, 1, 0, 0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //right
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(Guard.getPosition().x, Guard.getPosition().y, Guard.getPosition().z);
	//RenderMesh(meshList[GEO_HUMAN_MODEL], true);
	//modelStack.PopMatrix();
}

void SP2::RenderGuardAI(void)
{
	modelStack.PushMatrix();
	modelStack.Translate(Guard.getX(), -3.0f, Guard.getZ());
	modelStack.Rotate(Guard.getY2(), 0.f, 1.f, 0.f);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_GUARD_BODY], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.95, 0);
	RenderMesh(meshList[GEO_GUARD_HEAD], false);
	modelStack.PopMatrix(); // Pop Head

	modelStack.PushMatrix();
	modelStack.Translate(1, 2.3, 0);
	modelStack.Rotate(Guard.Rotation_Left_Hand,1,0,0);
	RenderMesh(meshList[GEO_GUARD_ARM], false); //Left
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 2.3, 0);
	modelStack.Rotate(Guard.Rotation_Right_Hand, -1, 0, 0);
	RenderMesh(meshList[GEO_GUARD_ARM], false); //right
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.3, -0.05, 0);
	modelStack.Rotate(Guard.Rotation_Left_Leg, -1, 0,0);
	RenderMesh(meshList[GEO_GUARD_LEG], false); //left
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.3, -0.05, 0);
	modelStack.Rotate(Guard.Rotation_Right_Leg, 1, 0, 0);
	RenderMesh(meshList[GEO_GUARD_LEG], false); //right
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	
	modelStack.PopMatrix();
}

void SP2::RenderShopperAI2(CShopperAI2 *Shopper1)
{
	modelStack.PushMatrix();

	modelStack.Translate(Shopper1->GetPosition().x, Shopper1->GetPosition().y, Shopper1->GetPosition().z);
	modelStack.Rotate(Shopper1->GetDirection().y + 180.f, 0.f, 1.f, 0.f);

	//Default walking animation
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_HUMAN_BODY], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.95, 0);
	RenderMesh(meshList[GEO_HUMAN_HEAD], false);
	modelStack.PopMatrix(); // Pop Head

	modelStack.PushMatrix();
	modelStack.Translate(1, 2.3, 0);
	modelStack.Rotate(-55, 1, 0, 0); //Shopper1->Rotation_Left_Hand
	if (Shopper1->Anime_Take == true)
	{
		modelStack.Rotate(Shopper1->Rotation_Left_Hand, 1, 0, 0);
	}
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //Left
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 2.3, 0);
	modelStack.Rotate(55, -1, 0, 0);//Shopper1->Rotation_Right_Hand
	if (Shopper1->Anime_Take == true)
	{
		modelStack.Rotate(Shopper1->Rotation_Right_Hand, -1, 0, 0);//Shopper1->Rotation_Right_Hand
	}
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //right
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.3, -0.05, 0);
	modelStack.Rotate(Shopper1->Rotation_Left_Leg, -1, 0, 0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //left
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.3, -0.05, 0);
	modelStack.Rotate(Shopper1->Rotation_Right_Leg, 1, 0, 0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //right
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();

	AITrolley.SetPosition(Shopper1->GetPosition());

	int i = 0;

	for (vector<CItem*>::iterator iter = AITrolley.Inventory.begin(); iter != AITrolley.Inventory.end(); ++iter, ++i)
	{
		
		modelStack.PushMatrix();
	
		modelStack.Translate(Shopper1->GetPosition().x, Shopper1->GetPosition().y, Shopper1->GetPosition().z);
		modelStack.Rotate(AITrolley.TrolleyDirection.y + 180.f, 0.f, 1.f, 0.f);
		modelStack.Translate(0, -0.6f, 4);
		modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
		//RenderMesh(meshList[AITrolley.Inventory.at(i)->GEO_TYPE], true);
		RenderTrolleyItems((*iter)->ItemName, (*iter)->ItemPrice, Vector3((*iter)->ItemPosition.x, (*iter)->ItemPosition.y, (*iter)->ItemPosition.z), (*iter)->GEO_TYPE, i);
		modelStack.PopMatrix();
	}

	if (Shopper1->backwardtrolley == true)
	{
		modelStack.PushMatrix();
		//modelStack.Translate(Shopper1->GetPosition().x, Shopper1->GetPosition().y, Shopper1->GetPosition().z);
		modelStack.Translate(AITrolley.TrolleyPosition.x, AITrolley.TrolleyPosition.y, AITrolley.TrolleyPosition.z);
		if (Shopper1->DoNotTurn == false)
		{
			modelStack.Rotate(Shopper1->GetDirection().y + 180.f, 0.f, 1.f, 0.f);
		}
		{

			modelStack.PushMatrix();
			modelStack.Translate(0, -0.6, -3);
			modelStack.Rotate(270, 0, 1, 0);
			RenderMesh(meshList[GEO_TROLLEY], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	if (Shopper1->fowardtrolley == true)
	{
		modelStack.PushMatrix();
		//modelStack.Translate(Shopper1->GetPosition().x, Shopper1->GetPosition().y, Shopper1->GetPosition().z);
		modelStack.Translate(AITrolley.TrolleyPosition.x, AITrolley.TrolleyPosition.y, AITrolley.TrolleyPosition.z);
		if (Shopper1->DoNotTurn == false)
		{
			modelStack.Rotate(Shopper1->GetDirection().y + 180.f, 0.f, 1.f, 0.f);
		}
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, -0.6, 4);
			modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_TROLLEY], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
}

void SP2::RenderShopperAI()
{
	//modelStack.PushMatrix();
	//modelStack.Translate(ShopperAI.getPositionX(), 0, ShopperAI.getPositionZ());
	//modelStack.Rotate(180, 0, 1, 0);
	//modelStack.Rotate(ShopperAI.getShopperDirection(), 0, 1, 0);
	//RenderMesh(meshList[GEO_HUMAN_MODEL], true);
	//modelStack.PopMatrix();

	//WithShopperCart
	if (ShopperAI.RENDERINGAI == false)
	{

		modelStack.PushMatrix();
		modelStack.Translate(ShopperAI.getPositionX(), -4, ShopperAI.getPositionZ());
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(ShopperAI.getShopperDirection(), 0, 1, 0);
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 3.95, 0);
			RenderMesh(meshList[GEO_HUMAN_HEAD], false);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.05, 0);
			RenderMesh(meshList[GEO_HUMAN_BODY], false);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(1.04, 3.3, 0);
			modelStack.Rotate(70, -1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_ARM], false); //Left
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.97, 3.3, 0);
			modelStack.Rotate(70, -1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_ARM], false); //right
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0.4, 1, 0);
			modelStack.Rotate(Rotation_Left_Leg, -1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_LEG], false); //left
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.38, 1, 0);
			modelStack.Rotate(Rotation_Right_Leg, 1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_LEG], false); //right
			modelStack.PopMatrix();
			if (ShopperAI.item_milo == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(0.5, 1, 3);
				modelStack.Rotate(90, 0, 1, 0);
				RenderMesh(meshList[GEO_CAN_MILO], false);
				modelStack.PopMatrix();
			}
			if (ShopperAI.item_sardine == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(-0.5, 0.9, 3);
				modelStack.Rotate(90, 0, 1, 0);
				RenderMesh(meshList[GEO_CAN_SARDINES], false);
				modelStack.PopMatrix();
			}
			if (ShopperAI.item_maggie == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(0.5, 0.9, 4);
				modelStack.Rotate(90, 0, 1, 0);
				RenderMesh(meshList[GEO_PACK_NOODLE], false);
				modelStack.PopMatrix();
			}
			if (ShopperAI.item_MnC == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(-0.6, 1.35, 4);
				modelStack.Rotate(90, 0, 1, 0);
				RenderMesh(meshList[GEO_BOX_CEREAL], false);
				modelStack.PopMatrix();
			}
			if (ShopperAI.item_choco == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(-0.4, 0.7, 5);
				modelStack.Rotate(180, 0, 1, 0);
				RenderMesh(meshList[GEO_BOX_CHOCO], false);
				modelStack.PopMatrix();
			}
			if (ShopperAI.item_iceCream == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(0.4, 1.5, 5);
				modelStack.Rotate(180, 1, 1, 0);
				RenderMesh(meshList[GEO_BOX_ICECREAM], false);
				modelStack.PopMatrix();
			}
			if (ShopperAI.RenderTrolley == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(0, 0.7, 4);
				modelStack.Rotate(90, 0, 1, 0);		
				RenderMesh(meshList[GEO_TROLLEY], false);
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
		}
	}
	//without Shopping Cart
	if (ShopperAI.RENDERINGAI == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(ShopperAI.getPositionX(), -4.1, ShopperAI.getPositionZ());
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(ShopperAI.getShopperDirection(), 0, 1, 0);
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 3.95, 0);
			RenderMesh(meshList[GEO_HUMAN_HEAD], false);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.05, 0);
			RenderMesh(meshList[GEO_HUMAN_BODY], false);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(1.04, 3.3, 0);
			modelStack.Rotate(Rotation_Left_Hand, 1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_ARM], false); //Left
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.97, 3.3, 0);
			modelStack.Rotate(Rotation_Right_Hand, -1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_ARM], false); //right
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0.4, 1, 0);
			modelStack.Rotate(Rotation_Left_Leg, -1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_LEG], false); //left
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.38, 1, 0);
			modelStack.Rotate(Rotation_Right_Leg, 1, 0, 0);
			RenderMesh(meshList[GEO_HUMAN_LEG], false); //right
			modelStack.PopMatrix();
			if (ShopperAI.item1 == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(-1, 0.8, 0.3);
				modelStack.Rotate(90, 1, 0, 0);
				modelStack.Rotate(Rotation_Right_Hand, -1, 0, 0);
				RenderMesh(meshList[GEO_CAN_COKE], false);
				modelStack.PopMatrix();
			}
			if (ShopperAI.item2 == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(1, 0.5, 0);
				modelStack.Rotate(90, 1, 0, 0);
				modelStack.Rotate(Rotation_Right_Hand, -1, 0, 0);
				RenderMesh(meshList[GEO_BOX_CHOC_CEREAL], false);
				modelStack.PopMatrix();
			}
		}
		modelStack.PopMatrix();
	}
}

void SP2::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	mesh->Render();

	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void SP2::RenderSkyBox()
{
	Mtx44 MVP;

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, 0, -0.499);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, 0, 0.499);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(-0.499, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0.499,0, 0);
	modelStack.Rotate(90, 0, -1, 0);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, 0.499, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, -0.5, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, -1, 0, 0);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void SP2::RenderObject()
{
	//Mtx44 MVP;

	//wall
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(1, 1, 1);
	modelStack.Translate(0, 1, -25);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();

	//Coldshelve
	for (int i = 0; i > -75; i -= 15)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, i);
		{
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(40.1, -2.12, 10);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_COLDSHELVE], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	for (int i = 0; i > -75; i -= 15)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, i);
		{
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-42.4, -2.12, 10);
			RenderMesh(meshList[GEO_COLDSHELVE], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 16; i += 4)
	for (int j = 0; j < 8; j+= 4)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, j);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(10, 0, 30);
			RenderMesh(meshList[GEO_TROLLEY], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	//Promoter
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(1, 1, 1);
	modelStack.Translate(25, -1.8, 4);
	RenderMesh(meshList[GEO_STANDER], true);
	modelStack.PopMatrix();

	//Refridge
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(1, 1, 1);
	modelStack.Translate(-3, -2, -25);
	RenderMesh(meshList[GEO_REFRIDGE], true);
	modelStack.PopMatrix();

	for (int i = 0; i > -54; i -= 8.5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, i);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-20, -2.2, -2);
			modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_THIRDSHELF], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	for (int i = 0; i > -54; i -= 8.5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, i);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(18, -2.2, -2);
			modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_THIRDSHELF], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}


	for (int i = 0; i > -32; i -= 15)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-0.02, -2.01, 19.86);
			//modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_CASHIERTABLE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-0.71, 0.9, 18);
			//modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_CASHIER], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	//ENTRANCE chehckbox
	if ((camera.position.x > 31 && camera.position.x < 43) && (camera.position.z > 39 && camera.position.z < 46))
	{
		rotateback = true;
		camera.HasEntered = false;
	}
	else
	{
		rotateback = false;
	}
	if(rotateback == false && camera.position.z < 35)
	{
		camera.HasEntered = true;
	}
	if (rotateback == true && rotationofdoor < 70)
	{
		rotationofdoor++;
	}
	else if (rotateback == false && rotationofdoor > 0)
	{
		rotationofdoor--;
	}
	//Render Entrance
	for (float i = 0; i > -10; i -= 5.5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(43, -1.8, 38);
			modelStack.Rotate(rotationofdoor, 0, -1, 0);
			RenderMesh(meshList[GEO_ENTRY], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	for (float i = 0; i > -10; i -= 5.5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(38, -1.8, 38);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Rotate(rotationofdoor, 0, 1, 0);
			RenderMesh(meshList[GEO_ENTRY], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}


	//LightBulb
	for (int j = -20; j < 40; j += 20)
	{
		for (int i = 30; i > -31; i -= 60)
		{
			modelStack.PushMatrix();
			modelStack.Translate(j, 0, i);
			{
				modelStack.PushMatrix();
				//scale, translate, rotate
				modelStack.Scale(1, 1, 1);
				modelStack.Translate(0, 7.5, 0);
				RenderMesh(meshList[GEO_LIGHTBULB], true);
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
		}
	}

	for (int i = 0; i < 50; i += 6)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);

		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-43, -1.8, 38);
			modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_SENSOR], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	for (int i = 0; i > -18; i -= 2)
	for (int j = 0; j > -4; j -= 2)
	{
		modelStack.PushMatrix();
		modelStack.Translate(j, 0, i);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-2.1, 1.3, -1.85);
			RenderMesh(meshList[GEO_BOX_PIZZA], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	for (int i = 0; i > -14; i -= 1)
	for (int j = 0; j > -4; j -= 2)
	{
		modelStack.PushMatrix();
		modelStack.Translate(j, 0, i);
		{
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-2.05, 1.3, -19.3);
			RenderMesh(meshList[GEO_BOX_ICECREAM], false);
		    modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	for (float i = 0; i > -16; i -= 0.5)
	for (float j = 0; j > -3.5; j -= 1.8)
	{
		modelStack.PushMatrix();
		modelStack.Translate(j, 0, i);
		{
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-1.9, 1., -33.06);
			RenderMesh(meshList[GEO_BOX_CHOCO], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	modelStack.PushMatrix();
	modelStack.Scale(1, 1, 1);
	modelStack.Translate(19,1,29);
	RenderMesh(meshList[GEO_WALLPARTITION], false);
	modelStack.PopMatrix();

	for (int i = 0; i > -32; i -= 15)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(cTablePos.x, cTablePos.y, cTablePos.z);
			RenderMesh(meshList[GEO_CONVEYORTABLE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(0, translateY, translateZ);
			modelStack.Translate(beltPos.x, beltPos.y, beltPos.z);
			RenderMesh(meshList[GEO_CONVEYORBELT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderCashier();
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	//Trolley
	modelStack.PushMatrix();
	modelStack.Translate(Trolley.TrolleyPosition.x, Trolley.TrolleyPosition.y, Trolley.TrolleyPosition.z); //Move trolley with camera
	
	modelStack.Rotate(Trolley.TrolleyDirection.y, 0.f, 1.f, 0.f); //Rotate with camera
	modelStack.Translate(-4.0f,0,0);
	
	int i = 0;
	//Rendering items on trolley
	if (renderItemOnTrolley == true)
	{
		for(vector<CItem*>::iterator iter = Trolley.Inventory.begin(); iter != Trolley.Inventory.end(); ++iter, i++)
		{
			RenderTrolleyItems((*iter)->ItemName, (*iter)->ItemPrice, Vector3((*iter)->ItemPosition.x, (*iter)->ItemPosition.y, (*iter)->ItemPosition.z), (*iter)->GEO_TYPE, i);
		}
	}
	RenderMesh(meshList[GEO_TROLLEY], true);
	modelStack.PopMatrix();

	if (renderItemOnTrolley == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, movingOnBelt);
		for(vector<CItem*>::iterator iter = Trolley.Inventory.begin(); iter != Trolley.Inventory.end(); ++iter, i++)
		{
			if (Trolley.Inventory.at(i)->render == true)
			{
				RenderBeltItems((*iter)->ItemName, (*iter)->ItemPrice, Vector3((*iter)->ItemPosition.x, (*iter)->ItemPosition.y, (*iter)->ItemPosition.z), (*iter)->GEO_TYPE, i);
			}
		}
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(42, 0, -59);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderNPC();
	modelStack.PopMatrix();

	for (int i = 0; i < 60; i += 20)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
	modelStack.PushMatrix();
	modelStack.Scale(1, 1, 1);
	modelStack.Translate(-20, -2, 55);
	RenderMesh(meshList[GEO_BENCH], false);
	modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 40; i += 20)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-10, -1.4, 55);
			modelStack.Rotate(90,0,1,0);
			RenderMesh(meshList[GEO_DUSTBIN], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	for (int i = 0; i < 160; i += 84)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-43, -1.4,68);
			modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_DUSTBIN], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

}

void SP2::RenderShelfItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber)
{
	Mtx44 MVP;
	int offsetY = WorldOffset;
	float Align = 0.15f;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelStack.PushMatrix();
	//Render items as default state
	if(Container.Shelf.at(ItemNumber)->ItemState == CItem::DEFAULT)
	{
		modelStack.Translate(Container.Shelf.at(ItemNumber)->ItemPosition.x, Container.Shelf.at(ItemNumber)->ItemPosition.y + offsetY, Container.Shelf.at(ItemNumber)->ItemPosition.z);
		RenderMesh(meshList[ItemType], false);
		
	}
	//Render items as destroyed state
	else if(Container.Shelf.at(ItemNumber)->ItemState == CItem::DESTROYED)
	{
		modelStack.Translate(Container.Shelf.at(ItemNumber)->ItemPosition.x, Container.Shelf.at(ItemNumber)->ItemPosition.y + offsetY, Container.Shelf.at(ItemNumber)->ItemPosition.z);
		//Translate flattened items downwards
		if(ItemType != SP2::GEO_PACK_KINDER && ItemType != SP2::GEO_PACK_SNICKER)
		{
			modelStack.Translate(0.f, -Align, 0.f);
		}
		else //Translate lesser Y due to obj size
		{
			modelStack.Translate(0.f, -(Align / 6), 0.f);
		}
		modelStack.Scale(1.25f, 0.25f, 1.25f);
		RenderMesh(meshList[ItemType], false);
	}

	//Text info of item
	if(camera.target.x > Container.Shelf.at(ItemNumber)->MinWidth && camera.target.x < Container.Shelf.at(ItemNumber)->MaxWidth
		&& camera.target.y > Container.Shelf.at(ItemNumber)->MinHeight && camera.target.y < Container.Shelf.at(ItemNumber)->MaxHeight
		&& camera.target.z > Container.Shelf.at(ItemNumber)->MinLength && camera.target.z < Container.Shelf.at(ItemNumber)->MaxLength)
	{
		string itemName, itemPrice;
		std::stringstream nameOfItemOnShelf, priceOfItemOnShelf;

		nameOfItemOnShelf << Container.Shelf.at(ItemNumber)->GetName();
		itemName = nameOfItemOnShelf.str();

		priceOfItemOnShelf << std::fixed << std::setprecision(2) << Container.Shelf.at(ItemNumber)->ItemPrice;
		itemPrice = priceOfItemOnShelf.str();

		if(Container.Shelf.at(ItemNumber)->ItemState == CItem::DEFAULT)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Name:"+itemName, Color(0, 1, 0), 2.5f, 7.f, 8.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], "Price: $"+itemPrice, Color(0, 1, 0), 2.5f, 7.f, 7.5f);
			if (PlayerInvent.Inventory.size() < 2)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to take", Color(0, 1, 0), 2.5f, 7.f, 6.5f);
			}

		}
		if (PlayerInvent.Inventory.size() > 0 && Container.Shelf.at(ItemNumber)->ItemState == CItem::TAKEN)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'G' to return", Color(0, 1, 0), 2.5f, 7.f, 5.5f);
		}
	}

	modelStack.PopMatrix();
}

void SP2::RenderTrolleyItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber)
{
	Mtx44 MVP;
	float TrolleyOffsetX = 1.5f;
	float TrolleyOffsetZ = 0.55f;
	float Spacing = 0.8f;
	float NewRow = 4.f;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelStack.PushMatrix();

	//Render items in 2x4
	if(ItemNumber < 4)
	{
		modelStack.Translate(-TrolleyOffsetX + (ItemNumber * Spacing), 0.f, -TrolleyOffsetZ);
	}
	else
	{
		modelStack.Translate(-TrolleyOffsetX + ((ItemNumber - NewRow) * Spacing), 0.f, TrolleyOffsetZ);
	}
	//modelStack.Rotate(Trolley.TrolleyDirection.y, 0.f, 1.f, 0.f);
	//modelStack.Translate(-4.f, 0.f, 0.f);

	RenderMesh(meshList[ItemType], false);
	modelStack.PopMatrix();
}

void SP2::RenderBeltItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber)
{
	float offSetZ = 2.f;
	Mtx44 MVP;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelStack.PushMatrix();

	modelStack.Translate(ItemPosition.x, ItemPosition.y, ItemPosition.z);

	RenderMesh(meshList[ItemType], false);
	modelStack.PopMatrix();
}

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	float temp = 0;
	float widthDivide = 100;
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(temp * 1.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
		temp += (textWidth[text[i]] / 100);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	float temp = 0;
	float widthDivide = 100;
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(temp * 1.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		temp += textWidth[text[i]] / widthDivide;
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void SP2::RenderUIOnScreen(Mesh* mesh, Color color, float TranslateX, float TranslateY, float degrees, float RotateY, float ScaleX, float ScaleY, float ScaleZ)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
	return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(TranslateX, TranslateY, 0);
	modelStack.Rotate(degrees, 0.f, RotateY, 0.f);
	modelStack.Scale(ScaleX, ScaleY, ScaleZ);

	RenderMesh(mesh, false);
	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void SP2::RenderCashier(void)
{
	//Render Cashier
	modelStack.PushMatrix(); //Push body
	modelStack.Translate(cTablePos.x, cTablePos.y, cTablePos.z);
	modelStack.Translate(3, 3, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_HUMAN_BODY], false);
	modelStack.PushMatrix();
	modelStack.Translate(0, 2.95, 0);
	RenderMesh(meshList[GEO_HUMAN_HEAD], false);
	modelStack.PopMatrix(); // Pop Head
	modelStack.PushMatrix();
	modelStack.Translate(1, 2.3, 0);
	modelStack.Rotate(armRotation,1,0,0);
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //Left
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-0.9, 2.3, 0);
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //right
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.3, -0.05, 0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //left
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-0.3, -0.05, 0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //right
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderPlayerArm(void)
{
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x , camera.position.y, camera.position.z);
	modelStack.Rotate(camera.playerArmRotation, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-1.5, -1.5, -1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_HUMAN_ARM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1.5, -1.5, -1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_HUMAN_ARM], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SP2::RenderNPC(void)
{
	modelStack.PushMatrix(); //Push body
	modelStack.Translate(0, 0.5, 0);
	RenderMesh(meshList[GEO_HUMAN_BODY], false);
	modelStack.PushMatrix();
	modelStack.Translate(0, 2.95, 0);
	RenderMesh(meshList[GEO_HUMAN_HEAD], false);
	modelStack.PopMatrix(); // Pop Head
	modelStack.PushMatrix();
	modelStack.Translate(1, 2.3, 0);
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //Left
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-0.9, 2.3, 0);
	RenderMesh(meshList[GEO_HUMAN_ARM], false); //right
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.3, -0.05, 0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //left
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-0.3, -0.05, 0);
	RenderMesh(meshList[GEO_HUMAN_LEG], false); //right
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::Exit()
{
	// Cleanup here
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i] != NULL)
			delete meshList[i];
	}
	engine->drop();
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}