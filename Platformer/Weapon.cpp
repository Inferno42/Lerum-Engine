#include "Weapon.h"
#include "tinyxml2.h"

#define TIXML_USE_STL

void CWeapon::Handle_Item_Effect()
{

}

void CWeapon::LoadStats(int id)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("items.xml");

	tinyxml2::XMLNode *root = doc.FirstChild(); //<items>
	tinyxml2::XMLNode *item = root->FirstChild(); //<item>
	while(true)
	{
		string cat = item->ToElement()->Attribute("category");
		if(cat == "WEAPON")
		{
			int w_id = atoi(item->FirstChild()->ToElement()->GetText());
			if(w_id == id) //We found the weapon.
			{
				tinyxml2::XMLNode *masterbit = item->FirstChild();
				masterbit = masterbit->NextSibling(); //Skip ID check.
				while(true)
				{
					
					const char* bitname = masterbit->ToElement()->Name();

					if(strcmp(bitname,"itemname") == 0)
					{
						this->itemstats.name = masterbit->ToElement()->GetText();
					}
					else if(strcmp(bitname,"weightcategory") == 0)
					{
						stats.weight_cat = masterbit->ToElement()->GetText();
					}
					else if(strcmp(bitname,"basedamage") == 0)
					{
						stats.BaseDamage = atoi(masterbit->ToElement()->GetText());
					}
					else if(strcmp(bitname,"bonuses") == 0)
					{
						tinyxml2::XMLNode* bbit = masterbit->FirstChild();
						while(true)
						{
							const char* name = bbit->ToElement()->Name();
							if(strcmp(name,"int") == 0)
							{
								bonuses.Int = atoi(bbit->ToElement()->GetText());
							}
							else if(strcmp(name,"strength") == 0)
							{
								bonuses.Str = atoi(bbit->ToElement()->GetText());
							}

							if(bbit == masterbit->LastChild())
							{
								break;
							}
							else
							{
								bbit = bbit->NextSibling();
							}
						}
					}
					else
					{
						masterbit = masterbit->NextSibling(); //Skip, unidentified value
					}


					if(masterbit == item->LastChild()) //basedamage will always come last (Unless bonuses found)
					{
						break;
					}
					else
					{
						masterbit = masterbit->NextSibling();
					}
				}

				break;
			}
			else
			{
				//DevError("Non-matching ID");
				item = item->NextSibling();
			}
		}
		else
		{
			//DevError("Incorrect Cat");
			item = item->NextSibling();
		}

		if(!item->NextSibling())
		{
			//DevError("End of file, item not found.");
			break;
		}
	}


}