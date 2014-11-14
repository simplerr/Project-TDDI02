#include "EditorState.h"

#include <SDL2/SDL.h>
#include <iostream>
#include "Platform.h"
#include "Background.h"


EditorState::EditorState(Renderer* renderer)
	: mRenderer(renderer)
{
	mSCREEN_WIDTH = renderer->getScreenWidth();
	mSCREEN_HEIGHT = renderer->getScreenHeight();
	init();
}

EditorState::~EditorState()
{
	for (unsigned int i{}; i < buttonList.size(); ++i)
	{
		delete buttonList[i];
	}
	delete mLevel;
	delete mListBgd;
    delete mRenderer;
	if ( currentObject != nullptr )
		delete currentObject;
}

void EditorState::init()
{
	//ALLA KNAPPAR PÅ VÄNSTER SIDA
	
	int col1 = mSCREEN_WIDTH-(buttonSize.x*3)-20;
	int col2 = mSCREEN_WIDTH-(buttonSize.x*2)-15;
	int col3 = mSCREEN_WIDTH-buttonSize.x-10;
	int row = buttonSize.y; // mSCREEN_HEIGHT+buttonSize.y;
	
	//###### CREATURES ######
	buttonList = {
		new Button(Vec2(col1, 10+row*0), buttonSize.x, buttonSize.y, "../imgs/player.jpg"),
	
		//###### PLATFORMS ######
		new Button(Vec2(col1, 10+row*3), buttonSize.x, buttonSize.y, "../imgs/platforms/platform.jpg"),
		new Button(Vec2(col2, 10+row*3), buttonSize.x, buttonSize.y, "../imgs/platforms/lava.png"),
		new Button(Vec2(col3, 10+row*3), buttonSize.x, buttonSize.y, "../imgs/platforms/block.png"),
		
		new Button(Vec2(col1, 15+row*4), buttonSize.x, buttonSize.y, "../imgs/downloads/Walkways/Walkway3.png"),
		new Button(Vec2(col2, 15+row*4), buttonSize.x, buttonSize.y, "../imgs/downloads/Walkways/Walkway2.png"), 
		new Button(Vec2(col3, 15+row*4), buttonSize.x, buttonSize.y, "../imgs/downloads/Walkways/Walkway1.png"),
		//###### PLATFORMS ######
		
		//###### BACKGROUNDS ######
		new Button(Vec2(col1, 10+row*8), buttonSize.x, buttonSize.y, "../imgs/backgrounds/skygrad.jpg"),
		new Button(Vec2(col2, 10+row*8), buttonSize.x, buttonSize.y, "../imgs/downloads/Other/FarBackground.png"),
		new Button(Vec2(col3, 10+row*8), buttonSize.x, buttonSize.y, "../imgs/downloads/Other/Grass.png"),
		//###### BACKGROUNDS ######
	
		// //###### OTHERS ######
		new Button(Vec2(mSCREEN_WIDTH-110, mSCREEN_HEIGHT-60), 100, 50, "../imgs/SAVE.png")
	}; 
	mLevel = new Level();
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
		gridPos.x = (mousePos.x / (mSCREEN_WIDTH/(mSCREEN_WIDTH/gridSize)))*(mSCREEN_WIDTH/(mSCREEN_WIDTH/gridSize));
		gridPos.y = (mousePos.y / (mSCREEN_HEIGHT/(mSCREEN_HEIGHT/gridSize)))*(mSCREEN_HEIGHT/(mSCREEN_HEIGHT/gridSize));
	}
}

void EditorState::draw(Renderer* renderer)
{
	if (currentObject != nullptr && currentObject->getId() == 4)
		currentObject->draw(renderer, gridPos);
		
	//Ritar ut alla object (platformar osv....)
	mLevel->draw(renderer); //Rita ut alla skapade objekt
	
	if (currentObject != nullptr && currentObject->getId() != 4)
		currentObject->draw(renderer, gridPos);
	
	//Bakgrund grid
	if(mGridBgd != nullptr)
		renderer->drawTexture(Vec2(0, 0), mSCREEN_WIDTH, mSCREEN_HEIGHT, mGridBgd);
    else
		mGridBgd = renderer->loadTexture("../imgs/backgrounds/grid8px.png");
		
		
	//Bakgrund sidan
	if(mListBgd != nullptr)
		renderer->drawTexture(Vec2(mSCREEN_WIDTH-menuBarWidth, 0), 120, mSCREEN_HEIGHT, mListBgd);
    else
		mListBgd = renderer->loadTexture("../imgs/backgrounds/darkblue.png");
	
	//Ritar ut alla knappar
	for (unsigned int i{}; i < buttonList.size(); ++i)
	{
		buttonList[i]->draw(renderer);
	}
	
	if(mTextPlatformar != nullptr)
		renderer->drawTexture(Vec2(mSCREEN_WIDTH-(buttonSize.x*3)-10, buttonSize.x*3-5), 80, 13, mTextPlatformar);
    else
		mTextPlatformar = renderer->loadTexture("..Platformar..", 0, 0, 0);
		
	if(mTextBakgrunder != nullptr)
		renderer->drawTexture(Vec2(mSCREEN_WIDTH-(buttonSize.x*3)-10, buttonSize.x*8-5), 80, 13, mTextBakgrunder);
    else
		mTextBakgrunder = renderer->loadTexture("..Bakgrunder..", 0, 0, 0);
		
	
}

void EditorState::handleEvent(SDL_Event e, bool& exit)
{
	//Om vi har ett objekt på musen
	if( currentObject != nullptr )
	{
		// Placera objekt
		if(e.type == SDL_MOUSEBUTTONDOWN && mousePos.x < mSCREEN_WIDTH-menuBarWidth ) // 120 == bredd på sidmenyn
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
	if ( e.type == SDL_MOUSEBUTTONDOWN )
	{
		//kolla om knapp är markerad
		for (unsigned int i{}; i < buttonList.size(); ++i)
		{
			if( buttonList[i]->mouseOver(mousePos)) //om innanför en knapp
			{
				delete currentObject; //Om man väljer någon annan efter man har valt
				currentObject = nullptr;
				switch(i)
				{
					case 0: currentObject = new Player(mousePos, 48, 48, "../imgs/player.jpg"); break;
					case 1:	currentObject = new Platform( mousePos, 200, 104, "../imgs/platforms/platform.jpg" ); break;
					case 2: currentObject = new Platform( mousePos, 200, 104, "../imgs/platforms/lava.png" ); break;
					case 3: currentObject = new Platform( mousePos, 200, 104, "../imgs/platforms/block.png" ); break;
					case 4: currentObject = new Platform( mousePos, 104, 104, "../imgs/downloads/Walkways/Walkway3.png" ); break;
					case 5: currentObject = new Platform( mousePos, 104, 104, "../imgs/downloads/Walkways/Walkway2.png" ); break;
					case 6: currentObject = new Platform( mousePos, 104, 104, "../imgs/downloads/Walkways/Walkway1.png" ); break;
					case 7: currentObject = new Background( mousePos, 200, 200, "../imgs/backgrounds/skygrad.jpg" ); break;
					case 8: currentObject = new Background( mousePos, 200, 200, "../imgs/downloads/Other/FarBackground.png" ); break;
					case 9: currentObject = new Background( mousePos, 200, 200, "../imgs/downloads/Other/Grass.png" ); break;
					case 10:
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
			
			
		//Om vi inte har något objekt markerat
		if ( currentObject == nullptr )
		{
			//kolla i objektlista ifall ett skapat objekt är markerat
			currentObject = mLevel->findObjectByPos(mousePos);
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
    
}
