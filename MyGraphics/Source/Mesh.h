/******************************************************************************/
/*!
\file	Mesh.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Mesh data storage for generated shapes
*/
/******************************************************************************/
#ifndef MESH_H
#define MESH_H

#include <string>
#include "Material.h"
/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	//! An enum.
	/*! Enum for uniform type */
	enum DRAW_MODE
	{
		DRAW_TRIANGLES,			/*!< DRAW_TRIANGLES */
		DRAW_TRIANGLE_STRIP,	/*!< DRAW_TRIANGLE_STRIP */
		DRAW_LINES,				/*!< DRAW_LINES */
		DRAW_MODE_LAST,			/*!< DRAW_MODE_LAST */
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();
	void Render(unsigned offset, unsigned count);
	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	unsigned textureID;
	Material material;
};

#endif