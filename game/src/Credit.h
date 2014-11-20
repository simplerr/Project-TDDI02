#ifndef CREDIT_H
#define CREDIT_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"

class Credit : public BaseState {
public:
    Credit();
    ~Credit();
    
    void init();
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e, bool& exit);
    
    StateId getStateId() { return EDITOR_STATE; }
private:
    Texture* mBackground;
	Texture* mExit;
};

#endif


