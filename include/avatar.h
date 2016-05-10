#ifndef _AVATAR_H_
#define _AVATAR_H_
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL.h"
#include "events.h"
#include "surface.h"
#include "sensor.h"

typedef struct floatRGB floatRGB;
struct floatRGB
{
   float r;
   float g;
   float b;
};

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

    bool ancient_code;

    SDL_Surface* sdl_pimage;

    SDL_Surface*    Surf_Display;
    SDL_Surface*    Surf_Test;
    SDL_Surface*    Surf_Temp;

    GLuint captured;
    GLuint texture;

 public:

    int teta, phi;

    CSensor sensor;

    bool mouse_left_down;
    bool mouse_right_down;

    CAvatar();
    ~CAvatar();
    int OnExecute(bool ancient_code);

    bool OnInit(bool ancient_code);

    void OnCleanup();
    void OnLoop() {};
    void OnRender();

    void OnMouseWheel(int, int);

    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

    virtual void OnLButtonDown(int mX, int mY);
    virtual void OnLButtonUp(int mX, int mY);
    virtual void OnRButtonDown(int mX, int mY);
    virtual void OnRButtonUp(int mX, int mY);

    void OnEvent(SDL_Event* Event);
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnMouseWheel(bool Up, bool Down);
    void OnResize(int w, int h);
    void OnExpose();
    void OnExit();

    float** AccessFrameColor();
    float* AccessFrameDepth(openni::VideoFrameRef *m_depthFrame);

    void InitSceneConstants();

    void SetPerspectiveProjectionMatrix();
    void SetOrthoProjectionMatrix();

    void DrawDemo();
    void DrawSensor();

};

#endif
