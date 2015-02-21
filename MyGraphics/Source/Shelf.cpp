#include "Shelf.h"

CShelf::CShelf(void)
{
	MaxShelfSize = 76;
}


CShelf::~CShelf(void)
{
}

void CShelf::SetShelfPosition(Vector3 &Position)
{
	ShelfPosition.x = Position.x;
	ShelfPosition.y = Position.y;
	ShelfPosition.z = Position.z;
}