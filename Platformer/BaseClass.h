#pragma once
#ifndef BASECLASS_H
#define BASECLASS_H
#include "Definitions.h"

enum Types{
	TYPE_OTHER,
	TYPE_ENEMY,
	TYPE_PHYSICS,
	TYPE_WORLD,

	TYPE_SOLID,
	TYPE_NONSOLID,

	TYPE_PLAYER,
	TYPE_ITEM
};

enum Exemption{
	VIEW_EXEMPT,
	VIEW_UNEXEMPT
};

// This class will be the base of all entities. Be them stationary(Environmental things) or non-stationary(Player or similar 
// entities). Please be very careful when tampering with this class as it can effect inheriting classes. -Inferno
class CBaseEntity
{
	public:
	
	CBaseEntity(int X, int Y);
	CBaseEntity();
	~CBaseEntity();
	void Spawn(int X, int Y);
	virtual void Handle();
	bool Check_Collison(SDL_Rect* CollidingRect);
	void Remove_Entity(); // Ticks the To_Be_Removed boolean, will be removed on next engine pass.

public:
	//Pre-defined and declared
	bool To_Be_Removed() {return dead;} 

	void SetDrawBox(SDL_Rect newrect) {DrawBox = newrect;}
	SDL_Rect GetDrawBox() {return DrawBox;}

	void SetBoundBox(SDL_Rect newrect) {BoundBox = newrect;}
	SDL_Rect GetBoundBox() {return BoundBox;}

	GLuint GetSprite() {return Sprite;}
	void SetSprite(GLuint newsprite) {Sprite = newsprite;}

	void Set_Crop(int crop) {CurrentCrop = crop;}
	int Get_Crop() {return CurrentCrop;}

	SDL_Rect* Get_Crop_Rect() {return Crops;}

	void SetIndex(int i) {index = i;}
	int GetIndex() {return index;}

	void SetSheetSize(int size) {SheetSize = size;}
	int GetSheetSize() {return SheetSize;}

	void SetType(int type) {EntType = type;}
	int GetType() {return EntType;}

	void SetPos(int X, int Y) { DrawBox.x = X; DrawBox.y = Y; DrawBox.w = Crops[CurrentCrop].w; DrawBox.h = Crops[CurrentCrop].h; }
	int GetX() {return DrawBox.x;}
	int GetY() {return DrawBox.y;}

	void SetSolidity(int _Solidity) {Solidity = _Solidity;}
	int GetSolidity() {return Solidity;}

	GLfloat GetTransparency() {return transparency;}
	void SetTransparency(GLfloat Trans) {transparency = Trans;}

	void SetDepth(GLfloat ndepth) {Depth = ndepth;}
	GLfloat GetDepth() {return Depth;}

	void SetSizeRatio(float nsize) {SizeRatio = nsize;}
	float GetSizeRatio() {return SizeRatio;}

	void SetExemption(int e) {Exemp = e;}//If entity should be handled while off-screen. (NPCs!!!)
	int GetExemption() {return Exemp;}

	//This may need to be changed in the future. 20 is a rough number for dev testing. 
	//At this moment in time (pre-alpha) we don't expect an entity to use more than 20 sprites.
	//Once we enter alpha, this will most likely be bumped up to around 50+.
	SDL_Rect Crops[20]; 

	bool customheight;

	bool HasShader;

	const char* shadname;

	protected:

	// Permanent I.D. (PID) Used for thinks like dialog tracking and cutscene tracking.
	// CAUTION, a PID is not required for entities such as tiles, enemies, etc.
	// But if it IS used for ANYTHING please make sure that it is UNIQUE.
	// If a duplication is found, it may very well throw a wrench into the system
	// if its either of the duplicates are called.
	// EX: Call dialog for PID 31. Two entites have PID 31. It will attempt to call both entites to play at the same time.
	// While this may be a desired effect, take care that it is not done otherwise.
	int PID; 

	int Exemp;

	bool dead;
	
	SDL_Rect DrawBox;
	GLuint Sprite;

	SDL_Rect BoundBox;

	int CurrentCrop; //Which crop (sprite) is to be loaded for this pass.
	int index; //pre-stored index for the engine loop. NOTE: This may need to be fixed so that it will be renewed every pass in case of entity removal. -Inferno
	
	int SheetSize;
	int EntType;
	int Solidity;
	GLfloat Depth;
	GLfloat transparency;
	float SizeRatio;

};

#define BASE CBaseEntity


#endif // BASECLASS_H
