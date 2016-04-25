#ifndef _CEVENT_H_
    #define _CEVENT_H_
#include <SDL.h>

class CEvent
{
public:
    CEvent();
    virtual ~CEvent();

    virtual void OnEvent(SDL_Event * Event);
    virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){}
    virtual void OnResize(int w, int h){}
    virtual void OnExpose(){}
    virtual void OnExit() {}
    virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
    virtual void OnLButtonDown(int mX, int mY);
    virtual void OnLButtonUp(int mX, int mY);
    virtual void OnRButtonDown(int mX, int mY);
    virtual void OnRButtonUp(int mX, int mY);
    virtual void OnMButtonDown(int mX, int mY);
    virtual void OnMButtonUp(int mX, int mY);

};

#endif
