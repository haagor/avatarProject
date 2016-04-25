#include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#include "../include/events.h"

CEvent::CEvent() {}

CEvent::~CEvent() {}

void CEvent::OnEvent(SDL_Event* Event) {
    switch(Event->type) {

        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }


        case SDL_QUIT: {
            OnExit();
            break;
        }

        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }

        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }

        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }

    case SDL_MOUSEMOTION: {
                OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
                break;
            }

    case SDL_MOUSEBUTTONDOWN: {
                switch(Event->button.button) {
                    case SDL_BUTTON_LEFT: {
                        OnLButtonDown(Event->button.x,Event->button.y);
                        break;
                    }
                    case SDL_BUTTON_RIGHT: {
                        OnRButtonDown(Event->button.x,Event->button.y);
                        break;
                    }
                    case SDL_BUTTON_MIDDLE: {
                        OnMButtonDown(Event->button.x,Event->button.y);
                        break;
                    }
                }
                break;
            }

            case SDL_MOUSEBUTTONUP:    {
                switch(Event->button.button) {
                    case SDL_BUTTON_LEFT: {
                        OnLButtonUp(Event->button.x,Event->button.y);
                        break;
                    }
                    case SDL_BUTTON_RIGHT: {
                        OnRButtonUp(Event->button.x,Event->button.y);
                        break;
                    }
                    case SDL_BUTTON_MIDDLE: {
                        OnMButtonUp(Event->button.x,Event->button.y);
                        break;
                    }
                }
                break;
            }

        default: {
            break;
        }
    }
}

void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    //Pure virtual, do nothing
}

void CEvent::OnLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}
