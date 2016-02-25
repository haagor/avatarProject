#ifndef _AVATAR_H_
#define _AVATAR_H_
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL.h"
#include "events.h"

class CAvatar : public CEvent
{
private:
    bool should_be_running;
    bool needs_rendering;

    int window_width;
    int window_height;
    const char* window_title;

    float world_origin_x;
    float world_origin_y;
    float world_origin_z;
    float world_rx;
    float world_ry;

    float camera_min_z;
    float camera_min_tz;
    float camera_max_z;

    float camera_tx;
    float camera_ty;
    float camera_tz;

    float camera_fovy;
    float camera_aspect_ratio;

    SDL_Surface* sdl_pimage;

 public:
    CAvatar();
    ~CAvatar();
    int OnExecute();

    bool OnInit();

    void OnCleanup();
    void OnLoop() {};
    void OnRender();

    void OnEvent(SDL_Event* Event);
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnResize(int w, int h);
    void OnExpose();
    void OnExit();

    void InitSceneConstants();
    void InitProjectionMatrix();

};

#endif
