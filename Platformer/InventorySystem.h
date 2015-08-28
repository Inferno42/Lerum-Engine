#pragma once
#ifndef IS_H
#define IS_H
#include "Item.h"
typedef std::map<int, CItem*> InvMap;

class CInventory
{
	public:
		CInventory();

		void AddToInventory(CItem* item);
		InvMap I;
	private:
		
};

#endif //IS_H