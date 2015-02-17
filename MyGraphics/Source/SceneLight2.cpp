#include "SceneLight2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Vertex.h"

SceneLight2::SceneLight2()
{
}

SceneLight2::~SceneLight2()
{
}

void SceneLight2::Init()
{
	// Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable back face culling
	glEnable(GL_CULL_FACE);
	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	//Load vertex and fragment shaders
	//m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	//m_programID = LoadShaders( "Shader//Shading.vertexshader", "Shader//Shading.fragmentshader" );
	m_programID = LoadShaders( "Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader" );
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));
	
	//Initialize all meshes to NULL
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
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

	lights[0].type = Light::LIGHT_SPOT;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_POINT;
	lights[1].position.Set(20, 20, 0);
	lights[1].color.Set(1, 0, 0);
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

	//Sphere 1
	meshList[GEO_SPHERE0] = MeshBuilder::GenerateSphere("sphere",Color(0.0f, 0.0f, 0.0f), 18, 36, 1.f);
	meshList[GEO_SPHERE0]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE0]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE0]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE0]->material.kShininess = 8.f;

	//Sphere 2
	meshList[GEO_SPHERE1] = MeshBuilder::GenerateSphere("sphere1",Color(1.f, 0.f, 0.f), 18, 36, 1.f);
	meshList[GEO_SPHERE1]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE1]->material.kDiffuse.Set(0.1f, 0.9f, 0.9f);
	meshList[GEO_SPHERE1]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE1]->material.kShininess = 8.f;

	//Sphere 3
	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("sphere2",Color(1.f, 1.f, 0.f), 18, 36, 1.f);
	meshList[GEO_SPHERE2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE2]->material.kShininess = 8.f;

	//Sphere 4
	meshList[GEO_SPHERE3] = MeshBuilder::GenerateSphere("sphere3",Color(1.f, 1.f, 1.f), 18, 36, 1.f);
	meshList[GEO_SPHERE3]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE3]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE3]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE3]->material.kShininess = 8.f;

	//Sphere 5
	meshList[GEO_SPHERE4] = MeshBuilder::GenerateSphere("sphere4",Color(0.f, 1.f, 0.f), 18, 36, 1.f);
	meshList[GEO_SPHERE4]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE4]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE4]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE4]->material.kShininess = 8.f;

	//Sphere 6
	meshList[GEO_SPHERE5] = MeshBuilder::GenerateSphere("sphere5",Color(0.f, 1.f, 1.f), 18, 36, 1.f);
	meshList[GEO_SPHERE5]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE5]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE5]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE5]->material.kShininess = 8.f;

	//Sphere 7
	meshList[GEO_SPHERE6] = MeshBuilder::GenerateSphere("sphere6",Color(1.f, 0.f, 1.f), 18, 36, 1.f);
	meshList[GEO_SPHERE6]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE6]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE6]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE6]->material.kShininess = 8.f;

	//Sphere 8
	meshList[GEO_SPHERE7] = MeshBuilder::GenerateSphere("sphere7",Color(0.f, 0.f, 1.f), 18, 36, 1.f);
	meshList[GEO_SPHERE7]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE7]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE7]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE7]->material.kShininess = 8.f;

	//Sphere 9
	meshList[GEO_SPHERE8] = MeshBuilder::GenerateSphere("sphere8",Color(1, 0, 0), 18, 36, 1.f);
	meshList[GEO_SPHERE8]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE8]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SPHERE8]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE8]->material.kShininess = 8.f;

	//Light ball
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 10, 1);
	meshList[GEO_LIGHTBALL2] = MeshBuilder::GenerateSphere("lightball2", Color(1, 1, 1), 10, 10, 1);

	//Floor
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1), 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kShininess = 8.f;
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
bool toggleLight = false;

void SceneLight2::Update(double dt)
{
	float LSPEED = 10.f;
	
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if(Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(LSPEED * dt);

	if(Application::IsKeyPressed('T'))
		lights[1].position.z -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('G'))
		lights[1].position.z += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('F'))
		lights[1].position.x -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('H'))
		lights[1].position.x += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('Y'))
		lights[1].position.y -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('U'))
		lights[1].position.y += (float)(LSPEED * dt);
	
	if(Application::IsKeyPressed('5'))
	{
		toggleLight = true;
	}
	if(Application::IsKeyPressed('6'))
	{
		toggleLight = false;
	}

	if(Application::IsKeyPressed('Z'))
	{
		//to do: switch light type to POINT and pass the information to shader
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	if(Application::IsKeyPressed('X'))
	{
		//to do: switch light type to DIRECTIONAL and pass the information to shader
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	if(Application::IsKeyPressed('C'))
	{
		//to do: switch light type to SPOT and pass the information to shader
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}

	if(Application::IsKeyPressed('7'))
	{
		//to do: switch light type to POINT and pass the information to shader
		lights[1].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}
	if(Application::IsKeyPressed('8'))
	{
		//to do: switch light type to DIRECTIONAL and pass the information to shader
		lights[1].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}
	if(Application::IsKeyPressed('9'))
	{
		//to do: switch light type to SPOT and pass the information to shader
		lights[1].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}

	rotateAngle += (float)(10 * dt);

	camera.Update(dt);
}

void SceneLight2::Render()
{
	//bool toggleLight = false;

	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

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

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(lights[1].position.x, lights[1].position.y, lights[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL2], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-20.f, 0.f, -20.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	float a = 0.1f;
	for(float i = 0; i < 3; i++)
	{
		for(float j = 0; j < 3; j++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(i * 2, 0, j * 2);
			if(i == 0 && j == 0)
			{
				RenderMesh(meshList[GEO_SPHERE0], toggleLight);
			}
			else if( i == 0 && j == 1)
			{
				RenderMesh(meshList[GEO_SPHERE1], toggleLight);
			}
			else if( i == 0 && j == 2)
			{
				RenderMesh(meshList[GEO_SPHERE2], toggleLight);
			}
			else if( i == 1 && j == 0)
			{
				RenderMesh(meshList[GEO_SPHERE3], toggleLight);
			}
			else if( i == 1 && j == 1)
			{
				RenderMesh(meshList[GEO_SPHERE4], toggleLight);
			}
			else if( i == 1 && j == 2)
			{
				RenderMesh(meshList[GEO_SPHERE5], toggleLight);
			}
			else if( i == 2 && j == 0)
			{
				RenderMesh(meshList[GEO_SPHERE6], toggleLight);
			}
			else if( i == 2 && j == 1)
			{
				RenderMesh(meshList[GEO_SPHERE7], toggleLight);
			}
			else if( i == 2 && j == 2)
			{
				RenderMesh(meshList[GEO_SPHERE8], toggleLight);
			}
			modelStack.PopMatrix();
		}
	}
	
	modelStack.PopMatrix();
	//RenderMesh(meshList[GEO_CYLINDER], toggleLight);

	//modelStack.PushMatrix();

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(0.f, -20.f, 0.f);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	RenderMesh(meshList[GEO_QUAD], toggleLight);
	modelStack.PopMatrix();
}

void SceneLight2::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
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
}


void SceneLight2::Exit()
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
