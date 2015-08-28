#include "GraphicManager.h"
#include "Engine.h"
#include "Camera.h"
#include "AClock.h"

GraphicsCore GraphicsM;
Gmap Gmaps;

GraphicsCore::GraphicsCore()
{
	Fade_Active = false;
	fps.start();
	update.start();
	Perc = 0.0f;
	ResRatio = 1.0f;
	TxHan.SetVis();
	CTextHandler* buf = &TxHan;


	
}

//void GraphicsCore::Draw(SDL_Rect db, GLuint src, GLRect CropRect, int SheetSize, GLfloat transparency, GLfloat SizeRatio, GLfloat Depth,
//	int height, bool customheight)
void GraphicsCore::Draw(CBaseEntity* ent)
{
	SDL_Rect db, CropRect;
	int height, SheetSize;
	GLfloat SizeRatio, Depth;
	GLuint src;
	bool customheight = false;

	db = ent->GetDrawBox();
	CropRect = ent->Get_Crop_Rect()[ent->Get_Crop()];
	SheetSize = ent->GetSheetSize();
	height = 0;
	SizeRatio = ent->GetSizeRatio();
	Depth = ent->GetDepth();
	src = ent->GetSprite();
	//All of the below is pure magic, do not touch less the evil gremlin hiding amongst the code destroy you, your house and your family.
	//If you have some masochistic need to poke the code with a hot iron, contact the codesmith Inferno.
	//For he (I) was the one who, in a fit of sleep deprivation, shat out this code with such force that it seemingly fixed itself.
	//EDIT 8/2/13: The code has been shrunken down for efficiency and simplicity. Future issues should be easier to debug now. -Inferno.

	const float px_overlap = 2.0f;
	
	//Draw Vertex declarations
	const float dv_w = ((db.x + CropRect.w) - gCam.GetCamera().x) / (ResRatio / SizeRatio);
	const float dv_x = ((db.x) - gCam.GetCamera().x) / (ResRatio / SizeRatio);
	const float dv_y = ((db.y) - gCam.GetCamera().y) / (ResRatio / SizeRatio);
	const float dv_h = ((db.y + CropRect.h) - gCam.GetCamera().y) / (ResRatio / SizeRatio);

	//Sprite Vertex declarations
	const float sp_x = (CropRect.x + px_overlap) / SheetSize;
	const float sp_w = ((CropRect.x + CropRect.w - px_overlap) / SheetSize);
	const float sp_y = (CropRect.y + px_overlap) / SheetSize;
	float sp_h;
	
	if(customheight == true)
	{
		sp_h = ((CropRect.y + CropRect.h - px_overlap) / height);
	}
	else
	{
		sp_h = ((CropRect.y + CropRect.h - px_overlap) / SheetSize);
	}


	ShaderController.SetUniform("TimeFrac", "test", (float)Enviroment->GetTimeSeconds() / SECONDS_24_HOURS);
		ShaderController.BindShader("test");
			glBindTexture(GL_TEXTURE_2D, src);
			glBegin(GL_TRIANGLE_STRIP);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glTexCoord3f(sp_x, sp_y, Depth); glVertex3f(dv_x, dv_y, Depth);
			glTexCoord3f(sp_w, sp_y, Depth); glVertex3f(dv_w, dv_y, Depth);
			glTexCoord3f(sp_x, sp_h, Depth); glVertex3f(dv_x, dv_h, Depth);
			glTexCoord3f(sp_w, sp_h, Depth); glVertex3f(dv_w, dv_h, Depth);
			glEnd();

		ShaderController.UnbindShader("test");
	


}

void GraphicsCore::Maintain_Framerate()
{
	//frame = 1; :(200): This function has been neutered, it will require ball restoration to work.
	//wat -bg
}

GLuint GraphicsCore::Load_Image( string filename)
{

	pngInfo info; //Prepare the PNG info

	GLuint Texture;

	glGenTextures(1, &Texture); // Prepare the Texture to be used as an actual OpenGL Texture.

	Texture = pngBind(filename.c_str(),
						PNG_NOMIPMAP,
						PNG_ALPHA,
						&info,
						GL_CLAMP,
						GL_LINEAR,
						GL_LINEAR); //Bind the png file to the GLuint Texture.

	if(Texture == 0)
	{
		#ifdef _DEBUG
		DevError("Texture not found! Name:%s", filename.c_str()); //If it didn't work, the Texture wasn't found.
		#endif

	}
	return Texture; //Return the finished .png texture.
}

void GraphicsCore::Add_To_Draw_Queue( CBaseEntity* base )
{
	//Add entities to a global Draw list. This will allow for quick Drawing. This can be
	//Used directly or via the simplified definition.
	//DrawQueue.add(base);
	DrawQueue.push(base);
}

void GraphicsCore::Fade_In()
{
	Perc = 0.0f;
	Fade_Active = true;
	Fading = 0;
}

void GraphicsCore::Fade_Out()
{
	Perc = 1.0f;
	Fade_Active = true;
	Fading = 1;
}

void GraphicsCore::Stop_Fade()
{
	glColor3f(1.0,1.0,1.0);
	Fade_Active = false;
	Fading = -1;
}

void GraphicsCore::Handle_Aux()
{
	if(Fade_Active == true)
	{
		if(Fading == 0)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_TEXTURE_2D);
			srand(SDL_GetTicks());
			glBegin(GL_QUADS);
			glColor4f(1, 1, 1, Perc);
			glVertex2f(-0.25f, -0.25f);
			glVertex2f( 0.25f, -0.25f);
			glVertex2f( 0.25f, 0.25f);
			glVertex2f(-0.25f, 0.25f);
			glEnd();


			Perc += 0.05f;
			if(Perc > 1.0f)
			{
				Perc = 1.0f;
				Fading = -1;
					Fade_Active = false;
			}
			SDL_Delay(5);
		}

		if(Fading == 1)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_TEXTURE_2D);
			srand(SDL_GetTicks());
			glBegin(GL_QUADS);
			glColor4f(Perc, Perc, Perc, Perc);
			glVertex2f(-0.25f, -0.25f);
			glVertex2f( 0.25f, -0.25f);
			glVertex2f( 0.25f, 0.25f);
			glVertex2f(-0.25f, 0.25f);
			glEnd();


			Perc -= 0.05f;
			if(Perc < 0.0f)
			{
				Perc = 0.0f;
			}
			SDL_Delay(5);
		}
		if(Fading == 2) // Death
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_TEXTURE_2D);
			srand(SDL_GetTicks());
			glBegin(GL_QUADS);
			glColor3f(2, Perc2, Perc2);
			glVertex2f(-0.25f, -0.25f);
			glVertex2f( 0.25f, -0.25f);
			glVertex2f( 0.25f, 0.25f);
			glVertex2f(-0.25f, 0.25f);
			glEnd();

			Perc2 -= 0.05f;
			if(Perc > 0.0f)
			{
				Perc = 0.0f;
				Fading = -1;
				Fade_Active = false;
			}
			SDL_Delay(5);
		}
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void GraphicsCore::Handle_Queue()
{
	while(!DrawQueue.empty()) //While the DrawQueue isn't empty
	{
		CBaseEntity* ent = DrawQueue.top(); //Save the top entity on the DrawQueue into a local variable for easy access.

		if(ent != NULL && ent->GetSprite() != NULL)
			Draw(ent);

			//Draw(ent->GetDrawBox(), ent->GetSprite(), 
			//buf, ent->GetSheetSize(), ent->GetTransparency(), ent->GetSizeRatio(), ent->GetDepth(),
			//ent->GetDrawBox().h,ent->customheight); //Draw the entity to the screen using all of the given variables from the entity.

		DrawQueue.pop();
	}

	Handle_Aux(); //Fades, overlays and things like that
	SDL_GL_SwapBuffers(); //Swap the buffers (Flip the screen) so OpenGL will display the finished frame

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Sheet GraphicsCore::Get_SpriteSheet( int SheetID )
{
	if(SheetID >= 0 && SheetID <= 19)
	{
		return Precached_Sheets[SheetID];
	}

	#ifdef _DEBUG
	DevError("Unable to find requested sprite sheet. ID may be wrong?");
	#endif
	return Precached_Sheets[20];
}

void GraphicsCore::Precache_Sheets()
{
	//Function called internally during startup, this will save heavily on system resources. Full sprite sheets won't have to be loaded
	//Every time they are needed. Rather, they will assigned a pointer to one of the already precached elements.
	PRECACHE_TEXTURE("Data\\grid.png","grid",512);
	PRECACHE_TEXTURE("Data\\Person.png","Person",1024);
	PRECACHE_TEXTURE("Data\\Menu.png","Menu",512);
	PRECACHE_TEXTURE("Data\\128DEV.png","128Dev",1024);
	PRECACHE_TEXTURE("Data\\Error.png","Error",33);
}

void GraphicsCore::Fade_In_Death()
{
	Perc = 0.0f;
	Perc2 = 1.0f;
	Fade_Active = true;
	Fading = 2;
}

void GraphicsCore::Setup_TxHan()
{
	//TxHan = new CTextHandler();
	//TxHan->SetVis();
	//ENT_INCREMENT(TxHan);
}

void GraphicsCore::SetupFBO()
{
	 glGenFramebuffers(1, &vbo);
}

Sheet LOAD_TEXTURE( std::string txname )
{
	if(Gmaps.find(txname) != Gmaps.end()) 
	{
		return Gmaps[txname];
	} 
	else 
	{
		//DevError("%s does not exist as a precached sheet!", txname);
	}
}
