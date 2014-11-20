#include "EditorState.h"

#include <SDL2/SDL.h>
#include <iostream>
#include "Platform.h"
#include "Background.h"
#include "constants.h"
#include "Decoration.h"

EditorState::EditorState()
{
	init();
	mListBgd = nullptr;
    mGridBgd = nullptr;
    mTextPlatformar = nullptr;
    mTextBakgrunder = nullptr;
}

EditorState::~EditorState()
{
	for (unsigned int i{}; i < buttonList.size(); ++i)
	{
		delete buttonList[i];
	}
	delete mLevel;
	delete mListBgd;
	if ( currentObject != nullptr )
		delete currentObject;
}

void EditorState::init()
{
	//ALLA KNAPPAR PÅ VÄNSTER SIDA
	
	int col1 = SCREEN_WIDTH-(buttonSize.x*3)-20;
	int col2 = SCREEN_WIDTH-(buttonSize.x*2)-15;
	int col3 = SCREEN_WIDTH-buttonSize.x-10;
	int row = buttonSize.y; // mSCREEN_HEIGHT+buttonSize.y;
	//###### CREATURES ######
	buttonList = {
		new Button(Vec2(col1, 10+row*0), buttonSize.x, buttonSize.y, FILEPATH_PLAYER),
		new Button(Vec2(col2, 10+row*0), buttonSize.x, buttonSize.y, FILEPATH_ENEMY1),
		//###### PLATFORMS ######
		new Button(Vec2(col1, 10+row*3), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_1),
		new Button(Vec2(col2, 10+row*3), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_2),
		new Button(Vec2(col3, 10+row*3), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_3),
		new Button(Vec2(col1, 15+row*4), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_4),
		new Button(Vec2(col2, 15+row*4), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_5), 
		new Button(Vec2(col3, 15+row*4), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_6),
		//###### PLATFORMS ######
		//###### BACKGROUNDS ######
		new Button(Vec2(col1, 10+row*8), buttonSize.x, buttonSize.y, FILEPATH_BACKGROUND_1),
		new Button(Vec2(col2, 10+row*8), buttonSize.x, buttonSize.y, FILEPATH_BACKGROUND_2),
		new Button(Vec2(col3, 10+row*8), buttonSize.x, buttonSize.y, "../imgs/downloads/Other/Grass.png"),
		//###### BACKGROUNDS ######
		// //###### OTHERS ######
		new Button(Vec2(SCREEN_WIDTH-110, SCREEN_HEIGHT-60), 100, 50, "../imgs/SAVE.png")
	};
	buttonListUnclickable = {
		new Button(Vec2(0,0), SCREEN_WIDTH, SCREEN_HEIGHT, "../imgs/backgrounds/grid8px.png"),
		new Button(Vec2(SCREEN_WIDTH-menuBarWidth, 0), 120, SCREEN_HEIGHT, "../imgs/backgrounds/darkblue.png"),
		new TextItem(Vec2(SCREEN_WIDTH-(buttonSize.x*3)-10, buttonSize.x*3-5), 80, 13, "..Platformar..", 0,0,0),
		new TextItem(Vec2(SCREEN_WIDTH-(buttonSize.x*3)-10, buttonSize.x*8-5), 80, 13, "..Bakgrunder..", 0,0,0)
	};
	mLevel = new Level();
	mLevel->loadLevel("Maptest2.txt");
}

void EditorState::cleanup()
{
	;
}

void EditorState::update(float dt)
{
	//Get mouse position
	SDL_GetMouseState( &mousePos.x, &mousePos.y ); //Get mouse position
	if  (mousePos.x != 0 && mousePos.y != 0 )
	{
		gridPos.x = ((mousePos.x+(mLevel->getCam().x-SCREEN_WIDTH/2)) / (SCREEN_WIDTH/(SCREEN_WIDTH/gridSize)))*(SCREEN_WIDTH/(SCREEN_WIDTH/gridSize));
		gridPos.y = ((mousePos.y+(mLevel->getCam().y-SCREEN_HEIGHT/2)) / (SCREEN_HEIGHT/(SCREEN_HEIGHT/gridSize)))*(SCREEN_HEIGHT/(SCREEN_HEIGHT/gridSize));
	}
}

void EditorState::draw(Renderer* renderer)
{
	
	//renderer->updateCamera(mPlayer->getPosition().x, mPlayer->getPosition().y, mPlayer->getWidth(), mPlayer->getHeight(), 9000, 9000);
	//Ritar ut markerat objekt om det är en bakgrund (Vi vill ha det längs bak)
	if (currentObject != nullptr && currentObject->getId() == 5)
		currentObject->draw(renderer, gridPos);

	//Ritar ut alla object (platformar osv....)
	mLevel->draw(renderer); //Rita ut alla skapade objekt

	//Ritar ut markerat objekt om det inte är en bakgrund
	if (currentObject != nullptr && currentObject->getId() != 5)
		currentObject->draw(renderer, gridPos);
	
	//Ritar ut alla oklickbara knappar
	for (unsigned int c{0}; c < buttonListUnclickable.size(); ++c)
	{
		buttonListUnclickable[c]->draw(renderer);
	}
	
	//Ritar ut alla knappar
	for (unsigned int p{0}; p < buttonList.size(); ++p)
	{
		buttonList[p]->draw(renderer);
	}
		
	
}

void EditorState::handleEvent(SDL_Event e, bool& exit)
{
	//Om vi har ett objekt på musen
	if( currentObject != nullptr )
	{
		// Placera objekt
		if(e.type == SDL_MOUSEBUTTONDOWN && mousePos.x < SCREEN_WIDTH-menuBarWidth ) // 120 == bredd på sidmenyn
		{
			currentObject->setPosition(gridPos);
			mLevel->addObject( currentObject->clone() );
			mLevel->insertion_sort();
		}
		
		//Ta bort markerat objekt
		if( e.key.keysym.sym == SDLK_LSHIFT && e.type == SDL_KEYDOWN )
		{
			delete currentObject;
			currentObject = nullptr;
		}
		
		//Filp current objekt
		if( e.key.keysym.sym == SDLK_f && e.type == SDL_KEYDOWN )
		{
			currentObject->setSize(Vec2(currentObject->getHeight(), currentObject->getWidth() ));
			currentHeight = currentObject->getHeight();
			currentWidth = currentObject->getWidth();
		}
		
		// Förstora eller förminska markerat objekt
		if(e.key.keysym.sym == SDLK_w && e.type == SDL_KEYDOWN )
			currentHeight -= gridSize;
		else if(e.key.keysym.sym == SDLK_s && e.type == SDL_KEYDOWN)
			currentHeight += gridSize;
		else if(e.key.keysym.sym == SDLK_d && e.type == SDL_KEYDOWN)
			currentWidth += gridSize;
		else if(e.key.keysym.sym == SDLK_a && e.type == SDL_KEYDOWN)
			currentWidth -= gridSize;

		if (currentWidth <= 0)
			currentWidth = gridSize;
		else if (currentHeight <= 0)
			currentHeight = gridSize;
		
		if ( currentObject != nullptr )
			currentObject->setSize(Vec2(currentWidth, currentHeight));
	}

	// Ta upp Object
	if ( e.type == SDL_MOUSEBUTTONDOWN  )
	{
		//kolla om knapp är markerad
		for (unsigned int i{}; i < buttonList.size(); ++i)
		{
			if( buttonList[i]->mouseOver(mousePos)) //om innanför en knapp
			{
				if(currentObject != nullptr)
				{
						delete currentObject; //Om man väljer någon annan efter man har valt
						currentObject = nullptr;
				}
				switch(i)
				{
					case 0: currentObject = new Player(mousePos, 48, 48, FILEPATH_PLAYER); break;
					case 1: currentObject = new Enemy(mousePos, 48, 48, FILEPATH_ENEMY1, 200); break;
					case 2:	currentObject = new Platform( mousePos, 200, 104, FILEPATH_PLATFORM_1 ); break;
					case 3: currentObject = new Platform( mousePos, 200, 104, FILEPATH_PLATFORM_2 ); break;
					case 4: currentObject = new Platform( mousePos, 200, 104, FILEPATH_PLATFORM_3 ); break;
					case 5: currentObject = new Platform( mousePos, 104, 104, FILEPATH_PLATFORM_4 ); break;
					case 6: currentObject = new Platform( mousePos, 104, 104, FILEPATH_PLATFORM_5 ); break;
					case 7: currentObject = new Platform( mousePos, 104, 104, FILEPATH_PLATFORM_6 ); break;
					case 8: currentObject = new Background( mousePos, 200, 200, FILEPATH_BACKGROUND_1 ); break;
					case 9: currentObject = new Background( mousePos, 200, 200, FILEPATH_BACKGROUND_2 ); break;
					case 10: currentObject = new Decoration( mousePos, 200, 200, "../imgs/downloads/Other/Grass.png" ); break;
					case 11:
						if ( mLevel->saveLevel("Maptest2.txt") )
							cout << "Succeeded to save file!\n";
						else
							cout << "Failed to save file!\n";
					break;
					default: currentObject = nullptr;
				}
				if (currentObject != nullptr)
				{
					currentHeight = currentObject->getHeight();
					currentWidth = currentObject->getWidth();
				}
				break; //Eftersom att vi hittat en knapp går vi ur loopen
			} // END IF
		} // END LOOP
			
			
		//Om vi inte har något objekt markerat och klickar på grid
		if ( currentObject == nullptr && mousePos.x < SCREEN_WIDTH-menuBarWidth )
		{
			//kolla i objektlista ifall ett skapat objekt är markerat
			Vec2 levelMousePos(mousePos.x+(mLevel->getCam().x-SCREEN_WIDTH/2),mousePos.y+(mLevel->getCam().y-SCREEN_HEIGHT/2));
			currentObject = mLevel->findObjectByPos(levelMousePos);
			if( currentObject != nullptr )
			{
				currentHeight = currentObject->getHeight();
				currentWidth = currentObject->getWidth();	
			}
		}
		
	}

	// Ta bort senast tillagda Objectet // SDLK_DELETE SDLK_BACKSPACE
	if(e.key.keysym.sym == SDLK_z && e.type == SDL_KEYDOWN)
    {
		if ( !mLevel->isListEmpty() )
			mLevel->pop();
    }
	
	// Ta bort allt och börja om
	if(e.key.keysym.sym == SDLK_F12 && e.type == SDL_KEYUP)
    {
		delete mLevel;
		mLevel = new Level();
		currentObject = nullptr;
    }
	
	// GÅ tillbaka till menyn
	if(e.key.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYUP)
    {
		setNextState(BaseState::MENU_STATE);
    }
	
	if(e.key.keysym.sym == SDLK_RIGHT && e.type == SDL_KEYDOWN)
    {
		mLevel->setCam(32,0);
    }
	if(e.key.keysym.sym == SDLK_LEFT && e.type == SDL_KEYDOWN)
    {
		mLevel->setCam(-32,0);
    }
	if(e.key.keysym.sym == SDLK_UP && e.type == SDL_KEYDOWN)
    {
		mLevel->setCam(0,-32);
    }
	if(e.key.keysym.sym == SDLK_DOWN && e.type == SDL_KEYDOWN)
    {
		mLevel->setCam(0,32);
    } 
}
