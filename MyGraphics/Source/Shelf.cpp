/******************************************************************************/
/*!
\file	Shelf.cpp
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Shelf to store items
*/
/******************************************************************************/
#include "Shelf.h"
/******************************************************************************/
/*!
\brief
Default Constructor

\exception None
\return None
*/
/******************************************************************************/
CShelf::CShelf(void)
{
}
/******************************************************************************/
/*!
\brief
Default Destructor
*/
/******************************************************************************/
CShelf::~CShelf(void)
{
}
/******************************************************************************/
/*!
\brief
Sets position of shelf

\param NewPosition - position to update
*/
/******************************************************************************/
void CShelf::SetShelfPosition(Vector3 &NewPosition)
{
	Position = NewPosition;
}
/******************************************************************************/
/*!
\brief
Sets collision of shelf

\param width - width of collision
\param height - height of collision
*/
/******************************************************************************/
void CShelf::SetShelfCollision(float Width, float Length)
{
	MinWidth = Position.x - (Width / 2);
	MaxWidth = Position.x + (Width / 2);
	MinLength = Position.z - (Length / 2);
	MaxLength = Position.z + (Length / 2);
}