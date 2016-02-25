#include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#include "events.h"

CEvent::CEvent() {}

CEvent::~CEvent() {}

void CEvent::OnEvent(SDL_Event* Event) {
    switch(Event->type) {

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

        default: {
            break;
        }
    }
}
