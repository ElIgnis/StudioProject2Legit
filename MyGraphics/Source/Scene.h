/******************************************************************************/
/*!
\file	Scene.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Overall scene handler
*/
/******************************************************************************/
#ifndef SCENE_H
#define SCENE_H
/******************************************************************************/
/*!
		Class Mtx44:
\brief	Handler for all scenes
*/
/******************************************************************************/
class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif