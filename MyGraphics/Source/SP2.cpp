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
	UIIndex = 0;
	Distance = 0;
	MaxDistance = 3.5;
	WorldOffset = 3.6f;

	std::string data = " ";

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
		}
		inShelfItem.close();
	}

	//Cashier details


	//AI details

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
	camera.Init(Vector3(0, 0, 0.1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//cl check
	double plX = camera.position.x;
	double plZ = camera.position.z;

	//Initialize all meshes to NULL
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

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

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID,"numLights");
	glUseProgram(m_programID);
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	 
	//UI
	//Screen
	startScreen = true;
	chooseModeScreen = false;
	highScoreScreen = false;
	gameStart = false;
	pauseScreen = false;
	endScreen = false;

	modeCustomer = false;
	modeGuard = true;
	modeVillain = false;

	missionComplete = false;
	missionFailed = false;

	elapsedTime = 0;
	countDown = 180;

	if (modeCustomer == true)
	{
		startingAmount = 150;
	}
	else
	{
		startingAmount = 0;
	}

	if (modeVillain == true)
	{
		isCaught = false;
		objectsDestroyed = 0;
	}
	if (modeGuard == true)
	{
		villainEscaped = false;
		villainCaught = false;
	}

	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(8.5f, 0.f, 260.f);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 0;
	lights[0].kC = 1.0f;
	lights[0].kL = 0.0001f;
	lights[0].kQ = 0.00001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].position.Set(-40.f, 50.f, 550.f);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 1.f, 0.f);

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
	meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("WALL", "OBJ//Wall2.obj");
	meshList[GEO_WALL]->textureID = LoadTGA("Image//Wall2.tga");
	meshList[GEO_WALL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WALL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_WALL]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WALL]->material.kShininess = 5.f;

	//ColdShelves
	meshList[GEO_COLDSHELVE] = MeshBuilder::GenerateOBJ("ColdShelve", "OBJ//ColdShelves.obj");
	meshList[GEO_COLDSHELVE]->textureID = LoadTGA("Image//ColdShelve.tga");
	meshList[GEO_COLDSHELVE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COLDSHELVE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_COLDSHELVE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_COLDSHELVE]->material.kShininess = 5.f;

	//Doorman
	meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("Doorman", "OBJ//doorman.obj");
	meshList[GEO_DOORMAN]->textureID = LoadTGA("Image//doorman.tga");
	meshList[GEO_DOORMAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DOORMAN]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_DOORMAN]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DOORMAN]->material.kShininess = 5.f;

	//Trolley
	meshList[GEO_TROLLEY] = MeshBuilder::GenerateOBJ("Trolley", "OBJ//Trolley.obj");
	meshList[GEO_TROLLEY]->textureID = LoadTGA("Image//Trolley.tga");
	meshList[GEO_TROLLEY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TROLLEY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_TROLLEY]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_TROLLEY]->material.kShininess = 5.f;

	//Stander
	meshList[GEO_STANDER] = MeshBuilder::GenerateOBJ("Stander", "OBJ//Stander.obj");
	meshList[GEO_STANDER]->textureID = LoadTGA("Image//Stander.tga");
	meshList[GEO_STANDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_STANDER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_STANDER]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_STANDER]->material.kShininess = 5.f;

	//Refridge
	meshList[GEO_REFRIDGE] = MeshBuilder::GenerateOBJ("Refridge", "OBJ//Refridge.obj");
	meshList[GEO_REFRIDGE]->textureID = LoadTGA("Image//Refridge.tga");
	meshList[GEO_REFRIDGE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REFRIDGE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_REFRIDGE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REFRIDGE]->material.kShininess = 5.f;

	//Shelf
	meshList[GEO_THIRDSHELF] = MeshBuilder::GenerateOBJ("ThirdShelf", "OBJ//thirdShelf.obj");
	meshList[GEO_THIRDSHELF]->textureID = LoadTGA("Image//thirdShelf.tga");
	meshList[GEO_THIRDSHELF]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_THIRDSHELF]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_THIRDSHELF]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_THIRDSHELF]->material.kShininess = 5.f;

	//CashierTable
	meshList[GEO_CASHIERTABLE] = MeshBuilder::GenerateOBJ("SideShelf", "OBJ//CashierTable.obj");
	meshList[GEO_CASHIERTABLE]->textureID = LoadTGA("Image//Table.tga");
	meshList[GEO_CASHIERTABLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CASHIERTABLE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CASHIERTABLE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CASHIERTABLE]->material.kShininess = 5.f;

	//CashierRegister
	meshList[GEO_CASHIER] = MeshBuilder::GenerateOBJ("Cashier", "OBJ//Cashiers.obj");
	meshList[GEO_CASHIER]->textureID = LoadTGA("Image//Cashiers.tga");
	meshList[GEO_CASHIER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CASHIER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CASHIER]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CASHIER]->material.kShininess = 5.f;

	//Shelf Items
	//Coke
	meshList[GEO_CAN_COKE] = MeshBuilder::GenerateOBJ("Can_Coke", "OBJ//Can_Coke0.obj");
	meshList[GEO_CAN_COKE]->textureID = LoadTGA("Image//Can_Coke_Tex.tga");
	meshList[GEO_CAN_COKE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_COKE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_COKE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CAN_COKE]->material.kShininess = 5.f;

	//Mountain Dew
	meshList[GEO_CAN_MTNDEW] = MeshBuilder::GenerateOBJ("Can_MtnDew", "OBJ//Can_MtnDew.obj");
	meshList[GEO_CAN_MTNDEW]->textureID = LoadTGA("Image//Can_MtnDew_Tex.tga");
	meshList[GEO_CAN_MTNDEW]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_MTNDEW]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_MTNDEW]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CAN_MTNDEW]->material.kShininess = 5.f;

	//Kinder Bueno
	meshList[GEO_PACK_KINDER] = MeshBuilder::GenerateOBJ("Packet_KinderBueno", "OBJ//Packet_KinderBueno.obj");
	meshList[GEO_PACK_KINDER]->textureID = LoadTGA("Image//Packet_KinderBueno_Tex.tga");
	meshList[GEO_PACK_KINDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_KINDER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_KINDER]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PACK_KINDER]->material.kShininess = 5.f;

	//Snicker
	meshList[GEO_PACK_SNICKER] = MeshBuilder::GenerateOBJ("Packet_Snickers", "OBJ//Packet_Snickers.obj");
	meshList[GEO_PACK_SNICKER]->textureID = LoadTGA("Image//Packet_Snickers_Tex.tga");
	meshList[GEO_PACK_SNICKER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_SNICKER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_SNICKER]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PACK_SNICKER]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_ICECREAM] = MeshBuilder::GenerateOBJ("Box_IceCream", "OBJ//Box_IceCream.obj");
	meshList[GEO_BOX_ICECREAM]->textureID = LoadTGA("Image//Box_IceCream_Tex.tga");
	meshList[GEO_BOX_ICECREAM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_ICECREAM]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_ICECREAM]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BOX_ICECREAM]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_PIZZA] = MeshBuilder::GenerateOBJ("Box_Pizza", "OBJ//Box_Pizza.obj");
	meshList[GEO_BOX_PIZZA]->textureID = LoadTGA("Image//Box_Pizza_Tex.tga");
	meshList[GEO_BOX_PIZZA]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_PIZZA]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_PIZZA]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BOX_PIZZA]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_CHOC_CEREAL] = MeshBuilder::GenerateOBJ("Box_Chocolate_Cereal", "OBJ//Box_Chocolate_Cereal.obj");
	meshList[GEO_BOX_CHOC_CEREAL]->textureID = LoadTGA("Image//Box_ChocolateC_Tex.tga");
	meshList[GEO_BOX_CHOC_CEREAL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_CHOC_CEREAL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_CHOC_CEREAL]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BOX_CHOC_CEREAL]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_BOX_CEREAL] = MeshBuilder::GenerateOBJ("Box_Cereal", "OBJ//Box_Cereal.obj");
	meshList[GEO_BOX_CEREAL]->textureID = LoadTGA("Image//Box_Cereal_Tex.tga");
	meshList[GEO_BOX_CEREAL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_CEREAL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_CEREAL]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BOX_CEREAL]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_CAN_BEANS] = MeshBuilder::GenerateOBJ("Can_Beans", "OBJ//Can_Beans.obj");
	meshList[GEO_CAN_BEANS]->textureID = LoadTGA("Image//Can_Beans_Tex.tga");
	meshList[GEO_CAN_BEANS]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_BEANS]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_BEANS]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CAN_BEANS]->material.kShininess = 5.f;

	//Ice Cream
	meshList[GEO_CAN_SARDINES] = MeshBuilder::GenerateOBJ("Can_Sardines", "OBJ//Can_Sardines.obj");
	meshList[GEO_CAN_SARDINES]->textureID = LoadTGA("Image//Can_Sardines_Tex.tga");
	meshList[GEO_CAN_SARDINES]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_SARDINES]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_SARDINES]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CAN_SARDINES]->material.kShininess = 5.f;

	//Entry
	meshList[GEO_ENTRY] = MeshBuilder::GenerateOBJ("Cashier", "OBJ//Entry.obj");
	meshList[GEO_ENTRY]->textureID = LoadTGA("Image//Entry.tga");
	meshList[GEO_ENTRY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENTRY]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_ENTRY]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_ENTRY]->material.kShininess = 5.f;

	//Rootbeer
	meshList[GEO_CAN_ROOTBEER] = MeshBuilder::GenerateOBJ("Can_Rootbeer", "OBJ//Can_Rootbeer.obj");
	meshList[GEO_CAN_ROOTBEER]->textureID = LoadTGA("Image//Can_Rootbeer_Tex.tga");
	meshList[GEO_CAN_ROOTBEER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_ROOTBEER]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_ROOTBEER]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CAN_ROOTBEER]->material.kShininess = 5.f;

	//Milo
	meshList[GEO_CAN_MILO] = MeshBuilder::GenerateOBJ("Can_Milo", "OBJ//Can_Milo.obj");
	meshList[GEO_CAN_MILO]->textureID = LoadTGA("Image//Can_Milo_Tex.tga");
	meshList[GEO_CAN_MILO]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CAN_MILO]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAN_MILO]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_CAN_MILO]->material.kShininess = 5.f;

	//Noodle
	meshList[GEO_PACK_NOODLE] = MeshBuilder::GenerateOBJ("Pack_Noodle", "OBJ//Packet_Noodle.obj");
	meshList[GEO_PACK_NOODLE]->textureID = LoadTGA("Image//Packet_Noodle_Tex.tga");
	meshList[GEO_PACK_NOODLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_NOODLE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_NOODLE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PACK_NOODLE]->material.kShininess = 5.f;

	//Toblerone
	meshList[GEO_PACK_TOBLERONE] = MeshBuilder::GenerateOBJ("Pack_Toblerone", "OBJ//Packet_Toblerone.obj");
	meshList[GEO_PACK_TOBLERONE]->textureID = LoadTGA("Image//Packet_Toblerone_Tex.tga");
	meshList[GEO_PACK_TOBLERONE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PACK_TOBLERONE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_PACK_TOBLERONE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_PACK_TOBLERONE]->material.kShininess = 5.f;

	//Chocolate
	meshList[GEO_BOX_CHOCO] = MeshBuilder::GenerateOBJ("Box_Choco", "OBJ//Box_Choco.obj");
	meshList[GEO_BOX_CHOCO]->textureID = LoadTGA("Image//Box_Choco_Tex.tga");
	meshList[GEO_BOX_CHOCO]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOX_CHOCO]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOX_CHOCO]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_BOX_CHOCO]->material.kShininess = 5.f;

	//Text
	meshList[GEO_UI] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f);
	meshList[GEO_UI]->textureID = LoadTGA("Image//UI.tga");

	//LightBulb
	meshList[GEO_LIGHTBULB] = MeshBuilder::GenerateOBJ("LightBulb", "OBJ//Lightbulb.obj");
	meshList[GEO_LIGHTBULB]->textureID = LoadTGA("Image//Lightbulb.tga");
	meshList[GEO_LIGHTBULB]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LIGHTBULB]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_LIGHTBULB]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_LIGHTBULB]->material.kShininess = 5.f;

	//Sensor
	meshList[GEO_SENSOR] = MeshBuilder::GenerateOBJ("Sensor", "OBJ//Sensor.obj");
	meshList[GEO_SENSOR]->textureID = LoadTGA("Image//Sensor.tga");
	meshList[GEO_SENSOR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SENSOR]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_SENSOR]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SENSOR]->material.kShininess = 5.f;

	//Wall Partition
	meshList[GEO_WALLPARTITION] = MeshBuilder::GenerateOBJ("Sensor", "OBJ//Partition.obj");
	meshList[GEO_WALLPARTITION]->textureID = LoadTGA("Image//Partition.tga");
	meshList[GEO_WALLPARTITION]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WALLPARTITION]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_WALLPARTITION]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WALLPARTITION]->material.kShininess = 5.f;

}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void SP2::Update(double dt)
{
	if (startScreen == true)
	{
		if (Application::IsKeyPressed('1'))
		{
			chooseModeScreen = true;
			startScreen = false;
		}

		if (Application::IsKeyPressed('2'))
		{
			highScoreScreen = true;
			startScreen = false;
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
			chooseModeScreen = false;
			gameStart = true;
		}
		else if (Application::IsKeyPressed('2')) //Play as Security Guard
		{
			startScreen = false;
			modeGuard = true;
			chooseModeScreen = false;
			gameStart = true;
		}
		else if (Application::IsKeyPressed('3')) //Play as Villain
		{
			startScreen = false;
			modeVillain = true;
			chooseModeScreen = false;
			gameStart = true;
		}
	}

	//High score
	else if (highScoreScreen == true)
	{
		if (Application::IsKeyPressed('1'))
		{
			startScreen = true;
			highScoreScreen = false;
		}
	}

	//Pause Screen
	else if (pauseScreen == true)
	{

	}

	//Game start
	else if (gameStart == true)
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

		//Pos checker
		std::stringstream s_plX;
		std::stringstream s_plZ;

		s_plX << camera.position.x;
		s_plZ << camera.position.z;

		plXCoord = s_plX.str();
		plZCoord = s_plZ.str();

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
			if(Application::IsKeyPressed('Q'))
			{
				startScreen = false;
				gameStart = false;
				endScreen = true;
			}
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
						//Distance is updated
						Distance = (camera.position.x - Container.Shelf.at(i)->ItemPosition.x) 
							+ (camera.position.y - Container.Shelf.at(i)->ItemPosition.y)
							+ (camera.position.z - Container.Shelf.at(i)->ItemPosition.z);

						//Only able to take items when within range and items that are on the shelf
						if(Distance <= MaxDistance && Container.Shelf.at(i)->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
						{
							if(PlayerInvent.AddToInvent(Container.Shelf.at(i),i))
							{
								Container.Shelf.at(i)->ItemState[CItem::NUM_STATE] = CItem::TAKEN;
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
						if(Distance <= MaxDistance && Container.Shelf.at(i)->ItemState[CItem::NUM_STATE] == CItem::TAKEN)
						{
							PlayerInvent.RemoveFromInvent(Container.Shelf.at(i),i);
							Container.Shelf.at(i)->ItemState[CItem::NUM_STATE] = CItem::DEFAULT;
						}
					}
				}
			}
			//Checkout items
			if(Application::IsKeyPressed(VK_RETURN))
			{
				//Checkout

			}
		}

		//Playing as Security Guard
		else if (modeGuard == true)
		{
			//if (score > 0 && playerposition == villain position && keypress)
			{
				missionComplete = true;
			}
			//else if (score <= 0)
			{
				missionFailed = true;
			}
		}

		//Playing as Villain
		else if (modeVillain == true)
		{
			//if (playerposition == item position && keypress)
			{
				objectsDestroyed++;
			}

			//if(objectsDestroyed == target && isCaught == false)
			{
				missionComplete = true;
			}
		}
	}

	//Game end
	else if (endScreen == true)
	{
		if (Application::IsKeyPressed('1'))
		{
			startScreen = true;
			endScreen = false;
		}
		//Mission pass/fail for customer
		if (amountSpent < startingAmount)
		{
			remaindingAmount = startingAmount - amountSpent;
			missionComplete = true;
		}
		else
		{
			amountOvershot = amountSpent - startingAmount;
			missionFailed = true;
		}

		//Calculate score 
		if (missionComplete == true || missionFailed == true)
		{
			player.setTimeTaken(elapsedTime);
			if (modeCustomer == true)
			{
				if (missionComplete == true)
				{
					player.setShopperScoreSucceed(dt, remaindingAmount);
				}
				else
				{
					player.setShopperScoreFailed(dt, amountOvershot);
				}
			}

			else if (modeGuard == true)
			{
				if (missionComplete == true)
				{
					player.setGuardScoreSucceed(dt);
				}

				if(missionFailed = true)
				{
					player.setGuardScoreSucceed(180);
				}
			}

			else if (modeVillain == true)
			{
				if (missionComplete == true)
				{
					player.setVillainScoreSucceed(dt);
				}
				else
				{
					player.setVillainScoreFailed(objectsDestroyed);
				}
			}
		}
	}
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
		RenderTextOnScreen(meshList[GEO_TEXT], "Customer: ", Color (1, 0, 0), 4.f, 8.f, 7.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Security Guard: ", Color (1, 0, 0), 4.f, 8.f, 6.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Villain: ", Color (1, 0, 0), 4.f, 8.f, 5.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Main Menu ", Color (1, 1, 1), 4.f, 7.5f, 4.f);
	}
	if (pauseScreen== true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderTextOnScreen(meshList[GEO_TEXT], "Back to Game", Color (1, 1, 1), 4.f, 8.f, 6.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Back to main menu", Color (1, 1, 1), 4.f, 7.5f, 5.f);
	}

	//End Game Screen
	if (endScreen == true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (modeCustomer == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Score:", Color (1, 1, 1), 5.f, 7.5f, 8.f);
		}
		else if (modeGuard == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Score:", Color (1, 1, 1), 5.f, 7.5f, 8.f);
		}
		else if (modeVillain == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Score:", Color (1, 1, 1), 5.f, 7.5f, 8.f);
		}

		RenderTextOnScreen(meshList[GEO_TEXT], "Return to Main Menu", Color (1, 1, 1), 4.f, 7.5f, 3.f);
		//if (player.getShopperHighScore() < player.getShopperScoreFailed() || player.getShopperHighScore() < player.getShopperScoreSucceed() || player.getVillainHighScore() < player.getVillainScoreFailed() || player.getVillainHighScore() < player.getVillainScoreSucceed() || player.getGuardHighScore() < player.getGuardScoreSucceed()) 
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "NEW HIGHSCORE! ", Color (1, 1, 1), 6.f, 4.5f, 8.f);
		}
	}

	if (gameStart == true && endScreen == false)
	{
		float textSize = 3.f;
		//clear depth and color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Temp variables
		Mtx44 MVP;

		viewStack.LoadIdentity();
		viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
		modelStack.LoadIdentity();

		//Ceiling light
		if(lights[0].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
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

		//Exterior light
		if(lights[1].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
			Mtx44 rotation;
			rotation.SetToRotation(-45.f, 1.f, 0.f, 0.f);
			Vector3 lightDirection_cameraspace = viewStack.Top() * rotation * lightDir;
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

		modelStack.PushMatrix();
		modelStack.Translate(-20.f, 0.f, -20.f);
		modelStack.Scale(10.f, 10.f, 10.f);
		float a = 0.1f;
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -WorldOffset, 0);
		RenderSkyBox();
		RenderObject();
		for(int i = 0; i < ItemLine; i++)
		{
			RenderShelfItems(Container.Shelf.at(i)->ItemName, Container.Shelf.at(i)->ItemPrice, Vector3(Container.Shelf.at(i)->ItemPosition.x, Container.Shelf.at(i)->ItemPosition.y, Container.Shelf.at(i)->ItemPosition.z), Container.Shelf.at(i)->GEO_TYPE, i);
		}
		modelStack.PopMatrix();

		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);



		//Text display for FPS
		RenderTextOnScreen(meshList[GEO_TEXT], "FPS:"+fpsText, Color(1, 0, 0), textSize, 22.5f, 19.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "X:"+plXCoord, Color(0, 1, 0), 5.f, 0.5f, 1.5f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Z:"+plZCoord, Color(0, 1, 0), 5.f, 0.5f, 2.5f);
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
			RenderTextOnScreen(meshList[GEO_TEXT], "Shopping List:", Color(1, 1, 1), 3.f, 0.5f, 13.f);

			//UI Rendering
			RenderUIOnScreen(meshList[GEO_UI], Color(1, 0 , 0), 50.f, 40.25f, 0.f, 1.f, 80.f, 80.f, 1.f);
			for(vector<CItem*>::iterator iter = PlayerInvent.Inventory.begin(); iter != PlayerInvent.Inventory.end(); iter++)
			{
				RenderUIOnScreen((meshList[(*iter)->GEO_TYPE]), Color(), 16.f + (UIIndex * 6.15f), 4.f, 90.f, 1.f, 1.f, 3.f, 3.f);
				UIIndex++;
			}
			UIIndex = 0;
		}
		else if (modeVillain == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Destroyed:", Color(1, 1, 1), 3.f, 0.5f, 13.f);
		}
		else if (modeGuard == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Caught:", Color(1, 1, 1), 3.f, 0.5f, 13.f);
		}
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
	modelStack.Translate(0, 0, -0.5);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, 0, 0.5);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(-0.5, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0.5,0, 0);
	modelStack.Rotate(90, 0, -1, 0);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, 0.5, 0);
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
	Mtx44 MVP;

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

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(1, 1, 1);
	modelStack.Translate(35, -1.8, 0);
	RenderMesh(meshList[GEO_DOORMAN], true);
	modelStack.PopMatrix();

	for (int i = 0; i < 24; i += 4)
	for (int j = 0; j < 8; j+= 4)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, j);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(10, -1.8, 25);
			modelStack.Rotate(180, 0, 1, 0);
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


	for (int i = 0; i > -40; i -= 17)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i, 0, 0);
		{
			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(0, -2.20, 20);
			//modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_CASHIERTABLE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			//scale, translate, rotate
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(-1, 0.9, 18);
			//modelStack.Rotate(90, 0, 1, 0);
			RenderMesh(meshList[GEO_CASHIER], false);
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
			modelStack.Translate(43, -1.8, 38);
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
			RenderMesh(meshList[GEO_ENTRY], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	//LightBulb
	for (int j = -20; j < 40; j += 20)
	{
		for (int i = 0; i > -40; i -= 20)
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
}

void SP2::RenderShelfItems(string ItemName, double ItemPrice, Vector3 &ItemPosition, int ItemType, int ItemNumber)
{
	Mtx44 MVP;
	int offsetY = WorldOffset;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelStack.PushMatrix();
	//Render items as default state
	if(Container.Shelf.at(ItemNumber)->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
	{
		modelStack.Translate(Container.Shelf.at(ItemNumber)->ItemPosition.x, Container.Shelf.at(ItemNumber)->ItemPosition.y + offsetY, Container.Shelf.at(ItemNumber)->ItemPosition.z);
		RenderMesh(meshList[ItemType], false);
		
	}
	//Render items as destroyed state
	else if(Container.Shelf.at(ItemNumber)->ItemState[CItem::NUM_STATE] == CItem::DESTROYED)
	{
		modelStack.Translate(Container.Shelf.at(ItemNumber)->ItemPosition.x, Container.Shelf.at(ItemNumber)->ItemPosition.y + offsetY, Container.Shelf.at(ItemNumber)->ItemPosition.z);
		modelStack.Scale(1.5f, 0.25f, 1.5f);
		RenderMesh(meshList[ItemType], false);
	}

	//Text info of item
	if(camera.target.x > Container.Shelf.at(ItemNumber)->MinWidth && camera.target.x < Container.Shelf.at(ItemNumber)->MaxWidth
		&& camera.target.y > Container.Shelf.at(ItemNumber)->MinHeight && camera.target.y < Container.Shelf.at(ItemNumber)->MaxHeight
		&& camera.target.z > Container.Shelf.at(ItemNumber)->MinLength && camera.target.z < Container.Shelf.at(ItemNumber)->MaxLength)
	{
		if(Container.Shelf.at(ItemNumber)->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
		RenderTextOnScreen(meshList[GEO_TEXT], "HERE", Color(0, 1, 0), 5.f, 5.5f, 3.5f);
	}

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

void SP2::Exit()
{
	// Cleanup here
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i] != NULL)
			delete meshList[i];
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}