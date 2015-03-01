#include "Shelf.h"

CShelf::CShelf(void)
{
}


CShelf::~CShelf(void)
{
}

void CShelf::SetShelfPosition(Vector3 &NewPosition)
{
	Position = NewPosition;
}

void CShelf::SetShelfCollision(float Width, float Length)
{
	MinWidth = Position.x - (Width / 2);
	MaxWidth = Position.x + (Width / 2);
	MinLength = Position.z - (Length / 2);
	MaxLength = Position.z + (Length / 2);
}