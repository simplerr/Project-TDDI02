#include "EditorState.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>

#include "Platform.h"
#include "Background.h"
#include "constants.h"
#include "Decoration.h"
#include "Enemy.h"
#include "Powerup.h"
#include "LavaPlatform.h"
#include "Finish.h"

EditorState::EditorState()
{
    mTextPlatformar = nullptr;
    mTextBakgrunder = nullptr;
    mFlagTexture = nullptr;
	showMousePos = nullptr;
	setEnemyFlag = false;
}

EditorState::~EditorState()
{
    for (unsigned int i{}; i < buttonList.size(); ++i)
    {
		delete buttonList[i];
    }
	for (unsigned int j{}; j < buttonListUnclickable.size(); ++j)
    {
		delete buttonListUnclickable[j];
    }
    delete mLevel;
    delete mTextPlatformar;
    delete mTextBakgrunder;
	delete mFlagTexture;
	delete showMousePos;
    //delete mFlagTexture;
    if ( currentObject != nullptr )
		delete currentObject;
}

void EditorState::init(string initData)
{
	//ALLA KNAPPAR PÅ VÄNSTER SIDA
	int col1 = SCREEN_WIDTH-(buttonSize.x*3)-20;
	int col2 = SCREEN_WIDTH-(buttonSize.x*2)-15;
	int col3 = SCREEN_WIDTH-buttonSize.x-10;
	int row = buttonSize.y; // mSCREEN_HEIGHT+buttonSize.y;
	//###### CREATURES ######
	buttonList = {
		new ButtonImg(Vec2(col1, 30+row*0), buttonSize.x, buttonSize.y, FILEPATH_PLAYER),
		new ButtonImg(Vec2(col2, 30+row*0), buttonSize.x, buttonSize.y, FILEPATH_ENEMY1),
		new ButtonImg(Vec2(col3, 30+row*0), buttonSize.x, buttonSize.y, FILEPATH_POWERUP1),
		new ButtonImg(Vec2(col1, 35+row*1), buttonSize.x, buttonSize.y, FILEPATH_FINISH),
		//###### PLATFORMS ######
		new ButtonImg(Vec2(col1, 10+row*4), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_1),
		new ButtonImg(Vec2(col2, 10+row*4), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_2),
		new ButtonImg(Vec2(col3, 10+row*4), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_3),
		new ButtonImg(Vec2(col1, 15+row*5), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_4),
		new ButtonImg(Vec2(col2, 15+row*5), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_5), 
		new ButtonImg(Vec2(col3, 15+row*5), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_6),
		
		new ButtonImg(Vec2(col1, 20+row*6), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_7),
		new ButtonImg(Vec2(col2, 20+row*6), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_8),
		new ButtonImg(Vec2(col3, 20+row*6), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_9),
		new ButtonImg(Vec2(col1, 25+row*7), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_10),
		new ButtonImg(Vec2(col2, 25+row*7), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_11),
		new ButtonImg(Vec2(col3, 25+row*7), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_12),
		new ButtonImg(Vec2(col1, 30+row*8), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_13),
		new ButtonImg(Vec2(col2, 30+row*8), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_14),
		new ButtonImg(Vec2(col3, 30+row*8), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_15),
		new ButtonImg(Vec2(col1, 35+row*9), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_16),
		new ButtonImg(Vec2(col2, 35+row*9), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_17),
		new ButtonImg(Vec2(col3, 35+row*9), buttonSize.x, buttonSize.y, FILEPATH_PLATFORM_18),
		//###### PLATFORMS ######
		//###### BACKGROUNDS ######
		new ButtonImg(Vec2(col1, 10+row*12), buttonSize.x, buttonSize.y, FILEPATH_BACKGROUND_1),
		new ButtonImg(Vec2(col2, 10+row*12), buttonSize.x, buttonSize.y, FILEPATH_BACKGROUND_2),
		new ButtonImg(Vec2(col3, 10+row*12), buttonSize.x, buttonSize.y, FILEPATH_BACKGROUND_3),
		//###### BACKGROUNDS ######
		//###### DECORATIONS ######
		new ButtonImg(Vec2(col1, 10+row*15), buttonSize.x, buttonSize.y, FILEPATH_DECORATION_1),
		new ButtonImg(Vec2(col2, 10+row*15), buttonSize.x, buttonSize.y, FILEPATH_DECORATION_2),
		new ButtonImg(Vec2(col3, 10+row*15), buttonSize.x, buttonSize.y, FILEPATH_DECORATION_3),
		new ButtonImg(Vec2(col1, 10+row*16), buttonSize.x, buttonSize.y, FILEPATH_DECORATION_4),
		//###### DECORATIONS ######
		// //###### OTHERS ######
		new ButtonImg(Vec2(SCREEN_WIDTH-110, SCREEN_HEIGHT-60), 100, 50, FILEPATH_SAVE),
		new ButtonText(Vec2(SCREEN_WIDTH-(25*4)-16, SCREEN_HEIGHT-70-buttonSize.y), 25, 25, FILEPATH_LEVEL_1,0,0,0),
		new ButtonText(Vec2(SCREEN_WIDTH-(25*3)-12, SCREEN_HEIGHT-70-buttonSize.y), 25, 25, FILEPATH_LEVEL_2,0,0,0),
		new ButtonText(Vec2(SCREEN_WIDTH-(25*2)-8, SCREEN_HEIGHT-70-buttonSize.y), 25, 25, FILEPATH_LEVEL_3,0,0,0),
		new ButtonText(Vec2(SCREEN_WIDTH-(25*1)-4, SCREEN_HEIGHT-70-buttonSize.y), 25, 25, FILEPATH_LEVEL_4,0,0,0)
	};
	buttonListUnclickable = { //VIKTIGT ATT DET SOM SKALL VARA LÄNGST BAK ÄR FÖRST OSV.
		new ButtonImg(Vec2(0,0), SCREEN_WIDTH, SCREEN_HEIGHT, FILEPATH_GRID),
		new ButtonImg(Vec2(SCREEN_WIDTH-menuBarWidth, 0), 120, SCREEN_HEIGHT, FILEPATH_MENU_BACKGROUND),
		new ButtonText(Vec2(SCREEN_WIDTH-(buttonSize.x*3)-10, buttonSize.x*4-5), 80, 13, TEXT_MENU_1, 0,0,0),
		new ButtonText(Vec2(SCREEN_WIDTH-(buttonSize.x*3)-10, buttonSize.x*12-5), 80, 13, TEXT_MENU_2, 0,0,0),
		new ButtonText(Vec2(SCREEN_WIDTH-(buttonSize.x*3)-10, buttonSize.x-15), 80, 13, TEXT_MENU_3, 0,0,0),
		new ButtonText(Vec2(SCREEN_WIDTH-(buttonSize.x*3)-10, row*15), 80, 13, TEXT_MENU_4, 0,0,0)
	};
	
	showMousePos = new ButtonText(Vec2(SCREEN_WIDTH-(buttonSize.x*3)-10, row*19), 80, 13, "x: EE y: EE", 0,0,0);
	
	mLevel = new Level();
	mLevel->setCurrentLevel(FILEPATH_LVL1);
	mLevel->loadLevel(mLevel->getCurrentLevel(), 2);	
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
    if (currentObject != nullptr && currentObject->getId() == Object::BACKGROUND)
	currentObject->draw(renderer, gridPos);

	//Ritar ut alla object (platformar osv....)
	mLevel->draw(renderer, true); //Rita ut alla skapade objekt

		std::cout << "HÄR\n"; 
	//Ritar ut markerat objekt om det inte är en bakgrund
	if (currentObject != nullptr && currentObject->getId() != Object::BACKGROUND && setEnemyFlag == false)
	    currentObject->draw(renderer, gridPos);

	// Rita ut slutpositionen för fienders patrullering
	if (setEnemyFlag == true)
	{
	    if(mFlagTexture == nullptr)
	    	mFlagTexture = renderer->loadTexture("../imgs/flag.png");
	    
	    renderer->drawTexture(gridPos, 48, 48, mFlagTexture);
	}
	
	//Ritar ut alla oklickbara knappar
	for (unsigned int c{0}; c < buttonListUnclickable.size(); ++c)
	{
		buttonListUnclickable[c]->setHighlightOn();
		buttonListUnclickable[c]->draw(renderer);
	}
	
	//Ritar ut alla knappar
	for (unsigned int p{0}; p < buttonList.size(); ++p)
	{
		buttonList[p]->setHighlightOn();
		buttonList[p]->draw(renderer);
	}

	//ritar ut positionen för vart musen befinnder sig...
	ostringstream converted;
	converted << "x: "<< mousePos.x+renderer->getCameraAdjustment().x << " y: " << mousePos.y+renderer->getCameraAdjustment().y;
	showMousePos->draw(renderer, converted.str());
		
	
}

void EditorState::handleEvent(SDL_Event e, bool& exit, bool& mMuteSound)
{
	if ( currentObject != nullptr )
	{
		// Placera objekt
		if(e.type == SDL_MOUSEBUTTONDOWN && mousePos.x < SCREEN_WIDTH-menuBarWidth ) // 120 == bredd på sidmenyn
		{
			currentObject->setPosition(gridPos);
			mLevel->addObject( currentObject->clone() );

			cout << "id: " << currentObject->getId() << endl;

			if (currentObject->getId() == Object::ENEMY)
			{
				setEnemyFlag = true;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP && mousePos.x < SCREEN_WIDTH-menuBarWidth )
		{
			
			if ( setEnemyFlag == true )
			{
			mLevel->pop();
			mLevel->addObject(new Enemy(currentObject->getPosition(), currentObject->getWidth(), currentObject->getHeight(), currentObject->getFilename(), gridPos.x));
			setEnemyFlag = false;
			}
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
				switch(i) {
				case 0: currentObject = new Player(mousePos, 48, 48, FILEPATH_PLAYER); break;
				case 1: currentObject = new Enemy(mousePos, 48, 48, FILEPATH_ENEMY1, mousePos.x); break;
				case 2: currentObject = new Powerup(mousePos, 40, 40, FILEPATH_POWERUP1); break;				   
				case 3: currentObject = new Finish(mousePos, 40, 40, FILEPATH_FINISH); break;
				case 4:	currentObject = new Platform( mousePos, 200, 104, FILEPATH_PLATFORM_1 ); break;
				case 5: currentObject = new LavaPlatform( mousePos, 200, 104, FILEPATH_PLATFORM_2 ); break;
				case 6: currentObject = new Platform( mousePos, 200, 104, FILEPATH_PLATFORM_3 ); break;
				case 7: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_4 ); break;
				case 8: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_5 ); break;
				case 9: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_6 ); break;
				case 10: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_7 ); break;
				case 11: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_8 ); break;
				case 12: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_9 ); break;
				case 13: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_10 ); break;
				case 14: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_11 ); break;
				case 15: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_12 ); break;
				case 16: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_13 ); break;
				case 17: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_14 ); break;
				case 18: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_15 ); break;
				case 19: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_16 ); break;
				case 20: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_17 ); break;
				case 21: currentObject = new Platform( mousePos, 104, 80, FILEPATH_PLATFORM_18 ); break;
				case 22: currentObject = new Background( mousePos, 560, 560, FILEPATH_BACKGROUND_1 ); break;
				case 23: currentObject = new Background( mousePos, 560, 560, FILEPATH_BACKGROUND_2 ); break;
				case 24: currentObject = new Background( mousePos, 560, 560, FILEPATH_BACKGROUND_3 ); break;
				case 25: currentObject = new Decoration( mousePos, 104, 48, FILEPATH_DECORATION_1 ); break;
				case 26: currentObject = new Decoration( mousePos, 104, 48, FILEPATH_DECORATION_2 ); break;
				case 27: currentObject = new Decoration( mousePos, 104, 48, FILEPATH_DECORATION_3 ); break;
				case 28: currentObject = new Decoration( mousePos, 400, 184, FILEPATH_DECORATION_4 ); break;
				case 29:

				    if ( mLevel->saveLevel(mLevel->getCurrentLevel()) )
						cout << "Succeeded to save file!\n";
					else
						cout << "Failed to save file!\n";
					break;
				case 30:
						mLevel->setCurrentLevel(FILEPATH_LVL1);
						mLevel->clearList();
						mLevel->loadLevel(mLevel->getCurrentLevel(), 2);
						cout << "level: " << mLevel->getCurrentLevel() << endl;
					break;
				case 31:
						mLevel->setCurrentLevel(FILEPATH_LVL2);
						mLevel->clearList();
						mLevel->loadLevel(mLevel->getCurrentLevel(), 2);
						cout << "level: " << mLevel->getCurrentLevel() << endl;
					break;
				case 32:
						mLevel->setCurrentLevel(FILEPATH_LVL3);
						mLevel->clearList();
						mLevel->loadLevel(mLevel->getCurrentLevel(), 2);
						cout << "level: " << mLevel->getCurrentLevel() << endl;
					break;
				case 33:
						mLevel->setCurrentLevel(FILEPATH_LVL4);
						mLevel->clearList();
						mLevel->loadLevel(mLevel->getCurrentLevel(), 2);
						cout << "level: " << mLevel->getCurrentLevel() << endl;
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
	
	// Ta bort allt och börja om
	if(e.key.keysym.sym == SDLK_F12 && e.type == SDL_KEYUP)
    {
		mLevel->clearList();
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
