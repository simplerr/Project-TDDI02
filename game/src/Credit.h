#ifndef CREDIT_H
#define CREDIT_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"
#include "Button.h"

class Credit : public BaseState {
public:
    Credit();
    ~Credit();
    
    void init(string initData = "");
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e, bool& exit);
    
	bool getMute() { return mmMute; }

    StateId getStateId() { return CREDIT; }
private:
    Texture* mBackground;
	Button *mBack;
	Vec2 mousePos;
};

#endif


