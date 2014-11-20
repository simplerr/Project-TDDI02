#ifndef EDITROSTATE_H
#define EDITORSTATE_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"
#include "Level.h"
#include "Button.h"
#include "Object.h"
#include "Player.h"
#include "Vec2.h"
#include <vector>

class EditorState : public BaseState {
public:
    EditorState();
    ~EditorState();
    
    void init();
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e, bool& exit);
    
    StateId getStateId() { return EDITOR_STATE; }
private:
    Texture* mFlagTexture;
    Texture* mTextPlatformar;
    Texture* mTextBakgrunder;
    
    int camX = SCREEN_WIDTH/2;
    int camY = SCREEN_HEIGHT/2;
    Level* mLevel;
    vector<Button*> buttonList;
    vector<Button*> buttonListUnclickable;
    Vec2 buttonSize{30, 30};
    int menuBarWidth{120};
    Vec2 mousePos;
    Vec2 gridPos;
    Object* currentObject = nullptr;
    unsigned int currentWidth;
    unsigned int currentHeight;
    unsigned int gridSize = 8;
};

#endif


