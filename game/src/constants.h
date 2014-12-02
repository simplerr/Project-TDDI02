#pragma once

#include <string>
#include "Vec2.h"

static const int SCREEN_WIDTH = 1024;
static const int SCREEN_HEIGHT = 768;
static const char WINDOW_NAME[] = "Rockblock II";
static const char PATH_FONT[] = "../fonts/GROBOLD.ttf";
static const std::string MENU_BKGD = "../imgs/menu_bkgd.png";


static const std::string VOLUME_BUTTON = "../imgs/buttons/volume.png";
static const std::string MUTE_BUTTON = "../imgs/buttons/mute.png";


//###### MAIN MENU //#####
static const std::string MENU_BACKGROUND = "../imgs/backgrounds/mainmenu.jpg";
static const std::string LEVEL1_BUTTON = "../imgs/buttons/menu/level1.png";
static const std::string LEVEL2_BUTTON = "../imgs/buttons/menu/level2.png";
static const std::string LEVEL3_BUTTON = "../imgs/buttons/menu/level3.png";
static const std::string LEVEL4_BUTTON = "../imgs/buttons/menu/level4.png";
static const std::string CREDIT_BUTTON = "../imgs/buttons/menu/creditbutton.png";
static const std::string EXIT_BUTTON = "../imgs/buttons/menu/exitbutton.png";
static const std::string TOEDITOR_BUTTON = "../imgs/buttons/menu/toEditor.png";


//###### PLAY //#####
 // Animation för player
static const Vec2 PLAYER_CLIP_LEFT[] {
  {36,0,37,55}, // STANDING
  {120,0,37,55}, //Jumping
  {343,118,44,55}, //RUNNING
  {298,118,44,55}, //RUNNING
  {248,118,44,55}, //RUNNING
  {197,118,44,55}, //RUNNING
  {145,118,44,55}, //RUNNING
  {93,118,44,55}, //RUNNING
  {44,118,44,55}, //RUNNING
  {0,118,44,55} //RUNNING
};
 // Animation för player
static const Vec2 PLAYER_CLIP_RIGHT[] {
  {0,0,37,55}, // STANDING
  {75,0,37,55}, //Jumping
  {0,60,44,55}, //RUNNING
  {50,60,44,55}, //RUNNING
  {93,60,44,55}, //RUNNING
  {141,60,44,55}, //RUNNING
  {191,60,44,55}, //RUNNING
  {243,60,44,55}, //RUNNING
  {290,60,44,55}, //RUNNING
  {344,60,44,55} //RUNNING
};
static const Vec2 ENEMY_CLIPS[] {
  {0,0,390,454},
  {390,0,390,454},
  {780,0,390,454},
  {1170,0,390,454}, 
};
static const std::string DEAD_SCREEN = "../imgs/backgrounds/yourdead.png";
static const std::string ENEMY_DEAD = "../imgs/textures/bloodsplatter.png";
static const std::string PAUSE_BACKGROUND = "../imgs/backgrounds/pause.png";
static const std::string CONTINUE_BUTTON = "../imgs/buttons/pause/continue.png";
static const std::string TOMENU_BUTTON = "../imgs/buttons/pause/quit.png";

//###### CREDITS //##### 
static const std::string CREDIT_BACKGROUND = "../imgs/backgrounds/credit.jpg";
static const std::string BACKTOMENU_BUTTON = "../imgs/buttons/credit/creditback.png";

//###### EDITOR #######
static const std::string FILEPATH_GRID = "../imgs/backgrounds/grid8px.png";
static const std::string FILEPATH_PLAYER = "../imgs/textures/creatures/student.png";
static const std::string FILEPATH_ENEMY1 = "../imgs/textures/creatures/enemy.png";
static const std::string FILEPATH_FINISH = "../imgs/textures/finish.png";
static const std::string FILEPATH_POWERUP1 = "../imgs/textures/powerups/powerup.png";
static const std::string FILEPATH_PLATFORM_1 = "../imgs/textures/platforms/platform.jpg";
static const std::string FILEPATH_PLATFORM_2 = "../imgs/textures/platforms/lava.png";
static const std::string FILEPATH_PLATFORM_3 = "../imgs/textures/platforms/block.png";
static const std::string FILEPATH_PLATFORM_4 = "../imgs/textures/platforms/Walkway3.png";
static const std::string FILEPATH_PLATFORM_5 = "../imgs/textures/platforms/Walkway2.png";
static const std::string FILEPATH_PLATFORM_6 = "../imgs/textures/platforms/Walkway1.png";
static const std::string FILEPATH_PLATFORM_7 = "../imgs/textures/platforms/Wall1.png";
static const std::string FILEPATH_PLATFORM_8 = "../imgs/textures/platforms/Wall2.png";
static const std::string FILEPATH_PLATFORM_9 = "../imgs/textures/platforms/Wall3.png";
static const std::string FILEPATH_PLATFORM_10 = "../imgs/textures/platforms/Wall4.png";
static const std::string FILEPATH_PLATFORM_11 = "../imgs/textures/platforms/Wall5.png";
static const std::string FILEPATH_PLATFORM_12 = "../imgs/textures/platforms/Wall6.png";
static const std::string FILEPATH_PLATFORM_13 = "../imgs/textures/platforms/Wall7.png";
static const std::string FILEPATH_PLATFORM_14 = "../imgs/textures/platforms/Wall8.png";
static const std::string FILEPATH_PLATFORM_15 = "../imgs/textures/platforms/Totem1.png";
static const std::string FILEPATH_PLATFORM_16 = "../imgs/textures/platforms/Totem2.png";
static const std::string FILEPATH_PLATFORM_17 = "../imgs/textures/platforms/Totem3.png";
static const std::string FILEPATH_PLATFORM_18 = "../imgs/textures/platforms/Totem4.png";
static const std::string FILEPATH_PLATFORM_19 = "../imgs/textures/platforms/lava.jpg";
static const std::string FILEPATH_BACKGROUND_1 = "../imgs/textures/backgrounds/skygrad.jpg";
static const std::string FILEPATH_BACKGROUND_2 = "../imgs/textures/backgrounds/FarBackground.png";
static const std::string FILEPATH_BACKGROUND_3 = "../imgs/textures/backgrounds/NearBackground.png";
static const std::string FILEPATH_DECORATION_1 = "../imgs/textures/decorations/Grass.png";
static const std::string FILEPATH_DECORATION_2 = "../imgs/textures/decorations/CatEyes.png";
static const std::string FILEPATH_DECORATION_3 = "../imgs/textures/decorations/Roots.png";
static const std::string TEXT_MENU_1 = "..Platforms..";
static const std::string TEXT_MENU_2 = "..Backgrounds..";
static const std::string TEXT_MENU_3 = "..Creatures..";
static const std::string TEXT_MENU_4 = "..Decoration..";
static const std::string FILEPATH_MENU_BACKGROUND = "../imgs/backgrounds/darkblue.png";
static const std::string FILEPATH_SAVE = "../imgs/buttons/editor/SAVE.png";
static const std::string FILEPATH_LEVEL_1 = "1";
static const std::string FILEPATH_LEVEL_2 = "2";
static const std::string FILEPATH_LEVEL_3 = "3";
static const std::string FILEPATH_LEVEL_4 = "4";


//###### MAPS #####
static const std::string FILEPATH_LVL1 = "level1.txt";
static const std::string FILEPATH_LVL2 = "level2.txt";
static const std::string FILEPATH_LVL3 = "level3.txt";
static const std::string FILEPATH_LVL4 = "level4.txt";

static int lvlUnlocks = 0;
