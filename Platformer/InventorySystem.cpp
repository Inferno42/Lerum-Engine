#include "InventorySystem.h"

CInventory::CInventory()
{

}

void CInventory::AddToInventory(CItem* item)
{
	srand(GetTickCount64());
	int powa = (pow(2.0,31-1));
	int uID = rand() % powa - 0;
	I[uID] = item;
};