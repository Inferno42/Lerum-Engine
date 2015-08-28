#include "Engine.h"
#include "Camera.h"

#ifdef _DEBUG
#include "Wraith.h"
#include "GUIButton.h"
#include "GUIButtonController.h"
#include "Weapon.h"
#include "FPSCounter.h"
#include "ShaderController.h"
#include "AClock.h"
#endif
#include <sys\timeb.h>

Engine GlobEngine;

Engine::Engine()
{
	Active = true;
	//Level = NULL; //Known only to few, it is the NULL Level. Some say, it is a never ending world full of carrots. -Random Hobo I met on my way home
	EntList.reserve(2048);
}

bool Engine::BootGL()
{
	const GLubyte* card = glGetString(GL_VERSION);
	if(!card)
	{
		DevError("Unable to detect OpenGL version, critical error!!!");
		return false;
	}
	else
	{
		DevDrop("OpenGL Version detected:%s",card);
	}



	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,	8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 8);
//	SDL_GLattr(SDL_GL_SWAP_CONTROL,0);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
	{
		DevError("Error initializing GLEW!!! Aborting Startup!!!");
		Sleep(5000);
		exit(0);
	}
	else
	{
		DevDrop("GLEW Successfully initialized.");
	}

	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		DevDrop("GLSL Prepared");
	else
		DevError("GLSL Not prepared");
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel (GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glAlphaFunc ( GL_GREATER, 0.45 ) ;
	glEnable ( GL_ALPHA_TEST ) ;
	glClearColor(0.0,0.0,0.0,1.0);
	glViewport(0, 0, Window->w,Window->h);
	glOrtho(0.0,(GLdouble)Window->w, (GLdouble)Window->h,0.0,0.0,1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	#ifdef _DEBUG
	DevDrop("OpenGL Booted!");
	#endif // _DEBUG

	GraphicsM.SetupFBO();
	
	return true;
}

bool Engine::InitWindow()
{
	Window = SDL_SetVideoMode(800,600,32,SDL_OPENGL | SDL_RESIZABLE); //Initialize the screen, make it able to printed to via OpenGL and make it resizeable.

	if(!Window) //If window does not exist.
	{
		#ifdef _DEBUG
		DevError("Unable to set SDL Video.");
		#endif // _DEBUG
		return false;
	}

	#ifdef _DEBUG
	DevDrop("Window Initialized!");
	#endif // _DEBUG

	SDL_WM_SetCaption("Project Lerum",NULL);
	return true;
}

bool Engine::SetupAudio()
{
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if(Mix_OpenAudio(audio_rate,audio_format,audio_channels,audio_buffers))
	{
		#ifdef _DEBUG
		DevError("Unable to open audio system!!!");
		#endif
		return false;
	}
	#ifdef _DEBUG
	DevDrop("Audio system setup successfully!");
	#endif
	return true;
}

bool Engine::StartUp()
{
	
	
	#ifdef _DEBUG
	DevDrop("Starting Engine.");
	#endif

	if(InitWindow() == false || BootGL() == false) //If unable to initialize window or boot OpenGL
	{
	#ifdef _DEBUG
		DevError("Error starting engine! Shutting down.");
		SDL_Quit();
	#endif // _DEBUG
		return false;
	}

	if(DisableVSync() == false)
	{
		#ifdef _DEBUG
		DevError("Error Disabling VSync, non-critical.");
		#endif
	}
	else
	{
		#ifdef _DEBUG
		DevDrop("VSync Disabled!");
		#endif
	}

	#ifdef _DEBUG
	DevDrop("Engine Started Successfully");
	#endif // _DEBUG

	GraphicsM.Precache_Sheets(); //Precache sheets, they can be called from the GraphicsMananger via pointers.
	#ifdef _DEBUG
	DevDrop("Sprite sheets precached and ready!");
	#endif // _DEBUG

	SetupAudio();

	gCam.Camera.x = 0;
	gCam.Camera.y = 0;
	gCam.Camera.w = GetGameScreen()->w;
	gCam.Camera.h = GetGameScreen()->h;

	SDL_EnableKeyRepeat(40,1); //Enable key repeating. After holding a key down for 40ms it will repeat the key press once.

	SetupLevels(); //This function will be deprecated soon. :(200): 

	Menu->Setup(); //Currently disabled, sets up the Menu initially.

	return true;
}

bool Engine::SetupLevels()
{
	TileMan.Precache_Tiles();
	TileMan.Load_Tiles("test_level");
	return true;
}

void Engine::Add_To_Ent_List( CBaseEntity* ent )
{
	//Add entities to a global ent list. This will allow for quick checking for collision. This can be
	//Used directly or via the simplified definition.
	EntList.push_back(ent);
}

void Engine::Handle_EntList()
{
	vector<CBaseEntity*>::const_iterator i, end(EntList.end());

	int a = 0;
	SDL_Rect* _tmpcam = &gCam.GetCamera(); //Camera won't change during this loop, no need to keep calling it.
	//for(int i = EntList.size() -1; --i;) //Start at the end of the the list and go backwards to 0. 
	for(i = EntList.begin();
		i != EntList.end();
		++i)
	{
		++a;
		CBaseEntity* bb = *i;
		if(!bb->To_Be_Removed()) //Check if EntList[i] exists.
		{
			if(bb->GetExemption() == VIEW_EXEMPT)
			{
				bb->Handle(); //Every entity is casted into a CBaseEntity*, Handle is a virtual function that every entity should have some form of. Even if that means calling an empty function.
			}
			else if(bb->GetExemption() == VIEW_UNEXEMPT)
			{
				if(bb->Check_Collison(_tmpcam) == 0)
				{
					bb->Handle();
				}
			}
		}

		else
		{
			EntList.erase(EntList.begin()+a); //Erase the entity i from the list if it has been scheduled to be removed. This will keep the list much more free.
		}
	}
}

bool Engine::MainLoop()
{	 
	//This block of code is only for debugging purposes, will be removed soon. :(200):
	Player1 = new CPlayer();
	Player1->Spawn();

//	BattleM->Spawn(); //Spawn & Initialize the BattleManager (Currently still being worked on.) :(200):

	Player1->SetPos(0, 600);

	gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2)) * GraphicsM.GetResRatio(), 
		(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2)) * GraphicsM.GetResRatio() );

#ifdef _DEBUG
	
	CWraith *a = new CWraith();
	a->Spawn(); //Spawns and Initializes a single wraith for testing.
	a->SetPos(100,100);

	Text* debug = new Text();
	debug->set("!DEBUG MODE!", 0, 600 - 60, 40, "Data\\IrishUncialfabeta-Bold.ttf");
	GraphicsM.ParseText(debug, "debug");

	CWeapon* Wep = new CWeapon();

	Wep->LoadStats(0);

	Player1->Inventory->AddToInventory(Wep);

	//CMenu* Men = new CMenu();
	//Men->Setup();
	Menu->SetVis();

	GraphicsM.ShaderController.RegisterNewShader("test","Shaders//test.fs",GL_FRAGMENT_SHADER);
	Player1->HasShader = true;
	Player1->shadname = "test";

	AClock* cl = new AClock();
	
	
#endif

	std::stringstream ss;
	
	FPSCounter * fps = new FPSCounter();
	fps->StartCounter();

	while(Active == true)
	{
		GraphicsM.TxHan.Handle();

		fps->Tick();

		//cout << Enviroment->GetTimeSeconds() << "\n";

		Input.HandleInput(); //This is called before in case the window gets a resize.

		HandleRes(); //Resolution Changes

		Handle_EntList(); //Calls the entity handler function

		GraphicsM.Handle_Queue(); //Handle all entities that were added to the drawqueue. Usually the adding is done via the entity when Handle() is called.

		ss << "FPS: " << fps->GetFPS();
		SDL_WM_SetCaption(ss.str().c_str(),NULL);
		ss.str("");

		srand(SDL_GetTicks());
		float r = (float)rand() /(float)RAND_MAX;
		float g = (float)rand() /(float)RAND_MAX;
		float b = (float)rand() /(float)RAND_MAX;
		GraphicsM.TxHan.ChangeColor(-r,-g,-b, "Inventory");
	}
	return true;
}

void Engine::HandleRes()
{
	gCam.Camera.w *= ResTmp;
	gCam.Camera.h *= ResTmp;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,	8);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glAlphaFunc ( GL_GREATER, 0.45 ) ;
	glEnable ( GL_ALPHA_TEST ) ;
	glClearColor(0.0,0.0,0.0,1.0);
	glViewport(0, 0, Window->w,Window->h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

bool Engine::DisableVSync()
{
	//Thanks to dk at DevMaster Aug 09, 2003.
	// http://devmaster.net/posts/5275/turning-vsync-off-in-opengl
	typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
	PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

	int interval = 0;

		const GLubyte *extensions = glGetString( GL_EXTENSIONS );

		if( strstr( (char*)extensions, "WGL_EXT_swap_control" ) == 0 )
			return false; // Error: WGL_EXT_swap_control extension not supported on your computer.\n");
		else
		{
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );

			if( wglSwapIntervalEXT )
				wglSwapIntervalEXT(interval);
		}
		return true;
	
}
