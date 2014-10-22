#pragma once

class Renderer;

class BaseState
{
public:
    BaseState() {};
    ~BaseState() {};

    virtual void init() = 0;
    virtual void cleanup() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(Renderer* renderer) = 0;
private:
};
