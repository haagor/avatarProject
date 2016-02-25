#ifndef _EVENT_H_
#define _EVENT_H_
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
};

#endif
