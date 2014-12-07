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

static const int POWERUP_TIME = 5;
 // Animation för player
static const Vec2 PLAYER_CLIP_LEFT[] {
  {2,47,24,37}, // STANDING
  {62,157,24,40}, //Jumping
  {162,148,32,49}, //Falling
  {66,453,31,40}, //Throwing
  {102,453,31,40}, //Throwing
  {0,86,34,36}, //RUNNING
  {34,86,34,36}, //RUNNING
  {68,86,34,36}, //RUNNING
  {102,86,34,36}, //RUNNING
  {136,86,34,36}, //RUNNING
  {170,86,34,36} //RUNNING
};
static const int PLAYER_STAND_START = 0;
static const int PLAYER_STAND_END = 0;
static const int PLAYER_JUMP_START = 1;
static const int PLAYER_JUMP_END = 1;
static const int PLAYER_FALL_START = 2;
static const int PLAYER_FALL_END = 2;
static const int PLAYER_SHOOT_START = 3;
static const int PLAYER_SHOOT_END = 4;
static const int PLAYER_RUN_START = 5;
static const int PLAYER_RUN_END = 10;
static const int PLAYER_CLIP_DELAY = 2; // 1 = NORMALT TEMPO

//static const Vec2 PLAYER_CLIP_LEFT[] {
//  {36,0,37,55}, // STANDING
//  {120,0,37,55}, //Jumping
//  {343,118,44,55}, //RUNNING
//  {298,118,44,55}, //RUNNING
//  {248,118,44,55}, //RUNNING
//  {197,118,44,55}, //RUNNING
//  {145,118,44,55}, //RUNNING
//  {93,118,44,55}, //RUNNING
//  {44,118,44,55}, //RUNNING
//  {0,118,44,55} //RUNNING
//};
static const Vec2 ENEMY_CLIPS[] {
  {0,0,390,454},
  {390,0,390,454},
  {780,0,390,454},
  {1170,0,390,454}
};

static const std::string PROJECTILE_FILEPATH = "../imgs/textures/projectile1.png";
static const int PROJECTILE_WIDTH = 60;
static const int PROJECTILE_HEIGHT = 30;
static const int PROJECTILE_LENGTH = 350;
static const int PROJECTILE_NUM_CLIPS = 13;
static const int PLAYER_PROJECTILE_SPEED = 12;
static const int ENEMY_PROJECTILE_SPEED = 4;
static const int ENEMY_SHOOT_CHANCE = 400; // ca. 1 på ENEMY_SHOOT_CHANCE per framerate
static const bool PROJECTILES_COLLISION_EACHOTHER = true;
static const Vec2 PROJECTILE_CLIPS[] {
  {0,0,30,15},
  {30,0,30,15},
  {60,0,30,15},
  {0,15,30,15},
  {30,15,30,15},
  {60,15,30,15},
  {0,30,30,15},
  {30,30,30,15},
  {60,30,30,15},
  {0,45,30,15},
  {30,45,30,15},
  {60,45,30,15},
  {0,60,30,15},
  {30,60,30,15},
  {60,60,30,15}
};
static const std::string EXPLOSION_FILEPATH = "../imgs/textures/explosion.png";
static const int EXPLOSION_DIAMETER = 40;
static const int EXPLOSION_NUM_CLIPS = 45;
static const Vec2 EXPLOSION_CLIPS[] {
  {0,0,100,100},
  {100,0,100,100},
  {200,0,100,100},
  {300,0,100,100},
  {400,0,100,100},
  {500,0,100,100},
  {600,0,100,100},
  {700,0,100,100},
  {800,0,100,100},
  
    {0,100,100,100},
  {100,100,100,100},
  {200,100,100,100},
  {300,100,100,100},
  {400,100,100,100},
  {500,100,100,100},
  {600,100,100,100},
  {700,100,100,100},
  {800,100,100,100},
  
    {0,200,100,100},
  {100,200,100,100},
  {200,200,100,100},
  {300,200,100,100},
  {400,200,100,100},
  {500,200,100,100},
  {600,200,100,100},
  {700,200,100,100},
  {800,200,100,100},
  
    {0,300,100,100},
  {100,300,100,100},
  {200,300,100,100},
  {300,300,100,100},
  {400,300,100,100},
  {500,300,100,100},
  {600,300,100,100},
  {700,300,100,100},
  {800,300,100,100},
  
  {0,400,100,100},
  {100,400,100,100},
  {200,400,100,100},
  {300,400,100,100},
  {400,400,100,100},
  {500,400,100,100},
  {600,400,100,100},
  {700,400,100,100},
  {800,400,100,100}
};

static const int BLOODSPLATTER_NUM_CLIPS = 16;

static const Vec2 BLOODSPLATTER_CLIPS[] {
    {0,0,256,256},
  {256,0,256,256},
  {512,0,256,256},
  {768,0,256,256},
    {0,256,256,256},
  {256,256,256,256},
  {512,256,256,256},
  {768,256,256,256},
    {0,512,256,256},
  {256,512,256,256},
  {512,512,256,256},
  {768,512,256,256},
    {0,768,256,256},
  {256,768,256,256},
  {512,768,256,256},
  {768,768,256,256}
};


static const std::string DEAD_SCREEN = "../imgs/backgrounds/yourdead.png";
static const std::string BLOODSPLATTER = "../imgs/textures/bloodsplatter2.png";
static const std::string PAUSE_BACKGROUND = "../imgs/backgrounds/pause.png";
static const std::string CONTINUE_BUTTON = "../imgs/buttons/pause/continue.png";
static const std::string TOMENU_BUTTON = "../imgs/buttons/pause/quit.png";

//###### CREDITS //##### 
static const std::string CREDIT_BACKGROUND = "../imgs/backgrounds/credit.jpg";
static const std::string BACKTOMENU_BUTTON = "../imgs/buttons/credit/creditback.png";

//###### EDITOR #######
static const std::string FILEPATH_GRID = "../imgs/backgrounds/grid8px.png";
//static const std::string FILEPATH_PLAYER = "../imgs/textures/creatures/student.png";
static const std::string FILEPATH_PLAYER = "../imgs/textures/creatures/megha_knuckles.png"; 
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
static const std::string FILEPATH_DECORATION_4 = "../imgs/textures/decorations/cloud.png";
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
