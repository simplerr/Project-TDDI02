#include "MenuState.h"
#include "Highscores.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

MenuState::MenuState()
{
    mute = false;
    mMenu = nullptr;
    mAlphaOverlay = nullptr;
    
    mHooverLevel = "none";
    mHighscoreButtonT = new ButtonText(Vec2(85, 400), 160, 30, "Best time: ", 0, 0, 0);
	mHighscoreButtonS = new ButtonText(Vec2(85, 430), 160, 30, "Best score: ", 0, 0, 0);
}

MenuState::~MenuState()
{
    for (unsigned int i = 0; i < buttonList.size(); i++)
		delete buttonList.at(i);
    
    delete mMenu;
    delete mAlphaOverlay;
    delete mHighscores;
    delete mHighscoreButtonT;
	delete mHighscoreButtonS;
}

void MenuState::init(string initData)
{
    buttonList = {	
		new ButtonImg(Vec2(80, 200), 200, 200, LEVEL1_BUTTON), // Play 1
		new ButtonImg(Vec2(300, 200), 200, 200, LEVEL2_BUTTON), // Play 2
		new ButtonImg(Vec2(520, 200), 200, 200, LEVEL3_BUTTON), // Play 3
		new ButtonImg(Vec2(740, 200), 200, 200, LEVEL4_BUTTON), // Play 3
		new ButtonImg(Vec2(412, 450), 200, 70, CREDIT_BUTTON), // Credit
		new ButtonImg(Vec2(412, 530), 200, 80, EXIT_BUTTON), // Exit
		new ButtonImg(Vec2(SCREEN_WIDTH-100, SCREEN_HEIGHT-100), 100, 100, TOEDITOR_BUTTON),
		new ButtonImg(Vec2(492, 660), 48, 48, VOLUME_BUTTON),
		new ButtonImg(Vec2(492, 660), 48, 48, MUTE_BUTTON)
		//new ButtonImg(Vec2(492, 660), 48, 48, VOLUME_BUTTON)
    };
    
    mHighscores = new Highscores("highscores.txt");
}

void MenuState::cleanup()
{
	;
}

void MenuState::update(float dt)
{
	;
}

void MenuState::draw(Renderer* renderer)
{
	//set camera to normal pos
	renderer->updateCamera(0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); 
	// draw test bkgd
	if(mMenu != nullptr)
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mMenu);
	else
		mMenu = renderer->loadTexture(MENU_BACKGROUND);

	if(mAlphaOverlay == nullptr)
	    mAlphaOverlay = renderer->loadTexture("../imgs/alpha.png");
	
	// Renderera ut knapparna
	for (unsigned int i = 0; i < buttonList.size()-2; i++) // -2 Cuz the 2 last is for volume and we renderer them later
	{
		buttonList[i]->draw(renderer);
		
		SDL_Rect rect = buttonList[i]->getRect();
		if((i == 1 && getLvlUnlocks() < 1) || (i == 2 && getLvlUnlocks() < 2) || (i == 3 && getLvlUnlocks() < 3))
		    renderer->drawTextureScreen(Vec2(rect.x, rect.y), rect.w, rect.h, mAlphaOverlay);
	}
	if (!mSoundMuted)
		buttonList.at(buttonList.size()-2)->draw(renderer);
    else
		buttonList.at(buttonList.size()-1)->draw(renderer);

	// rita ut highscore för den level man har musen över
	if(mHooverLevel != "none")
	{
		if (mHooverLevel == "level1.txt") {
			mHighscoreButtonT->setPosition(Vec2(80,400));
			mHighscoreButtonS->setPosition(Vec2(80,425));
		}
		if (mHooverLevel == "level2.txt") {
			mHighscoreButtonT->setPosition(Vec2(300,400));
			mHighscoreButtonS->setPosition(Vec2(300,425));
		}
		if (mHooverLevel == "level3.txt") {
			mHighscoreButtonT->setPosition(Vec2(520,400));
			mHighscoreButtonS->setPosition(Vec2(520,425));
		}
		if (mHooverLevel == "level4.txt") {
			mHighscoreButtonT->setPosition(Vec2(740,400));
			mHighscoreButtonS->setPosition(Vec2(740,425));
		}
		
	    ostringstream convertedT, convertedS;
		convertedT << fixed << std::setprecision(1) << left << "Best Time: " << mHighscores->getHighscoreTime(mHooverLevel) << " s";
		convertedS << fixed << std::setprecision(1) << left << "Best Score: " << mHighscores->getHighscoreScore(mHooverLevel);
	    mHighscoreButtonT->draw(renderer, convertedT.str());
		mHighscoreButtonS->draw(renderer, convertedS.str());
	}
}

void MenuState::handleEvent(SDL_Event e, bool& exit, bool& mMuteSound)
{
		mSoundMuted = mMuteSound;
    // för att se vilken karta highscore ska visas för
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    mHooverLevel = "none";
    for (unsigned int i = 0; i < buttonList.size(); i++) {
			
		if (buttonList.at(i)->mouseOver(mousePos)) {

			switch (i) {
			case 0:
				mHooverLevel = FILEPATH_LVL1;	
				break;
			case 1:	   
				mHooverLevel = FILEPATH_LVL2;	
				break;
			case 2:
				mHooverLevel = FILEPATH_LVL3;	
				break;
			case 3:		
				mHooverLevel = FILEPATH_LVL4;	
				break;
			default:
				mHooverLevel = "none";
			}
		}
    }


    if(e.type == SDL_MOUSEBUTTONDOWN) // Kolla musknappnedtryck
    {
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		for (unsigned int i = 0; i < buttonList.size(); i++) {
			
			if (buttonList.at(i)->mouseOver(mousePos)) {

				switch (i) {
				case 0:
				    setNextState(BaseState::PLAY_STATE, FILEPATH_LVL1);	
				    break;
				case 1:
				    if (getLvlUnlocks() > 0)
						setNextState(BaseState::PLAY_STATE, FILEPATH_LVL2);
				    break;
				case 2:
				    if (getLvlUnlocks() > 1)
						setNextState(BaseState::PLAY_STATE, FILEPATH_LVL3);
				    break;
				case 3:
					if (getLvlUnlocks() > 2)
						setNextState(BaseState::PLAY_STATE, FILEPATH_LVL4);
				    break;
				case 4:
				    setNextState(BaseState::CREDIT);
				    break;
				case 5:
				    exit = true;
				    break;
				case 6:
				    setNextState(BaseState::EDITOR_STATE);
				    break;
				case 7:
					mMuteSound = !mMuteSound;
				
					if (!mMuteSound) {
						buttonList.at(buttonList.size()-1) = new ButtonImg(Vec2(492, 660), 48, 48, VOLUME_BUTTON);
					} else {
						buttonList.at(buttonList.size()-1) = new ButtonImg(Vec2(492, 660), 48, 48, MUTE_BUTTON);
					}
					break;
				default:
				    break;
				}

			}

		}
	}
}
