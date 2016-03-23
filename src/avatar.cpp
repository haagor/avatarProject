#include "../include/avatar.h"
#include "../include/gl_objects.h"
#include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#include <iostream>

#define SDL_VIDEO_MODE_OPTIONS (SDL_RESIZABLE| SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)
#define SDL_DEPTH 32

#define SCENE_ROTATION_STEP 5
    #define CAMERA_Z_OFFSET 2
    #define CAMERA_TRANSLATION_STEP 0.1

    #define RDR_FRAME_LENGTH 1
    #define RDR_CUBE_HALF_SIDE 0.5

using namespace std;

CAvatar::CAvatar() {
    Surf_Test = NULL;
    Surf_Display = NULL;
    should_be_running = true;
    needs_rendering = true;
    window_width = 250;
    window_height = 250;
    window_title = "";
    InitSceneConstants();
}

CAvatar::~CAvatar() {}

void CAvatar::InitSceneConstants()
{
    world_rx = 0;
    world_ry = 0;

    camera_min_tz = world_origin_z + CAMERA_Z_OFFSET;
    camera_tx = world_origin_x;
    camera_ty = world_origin_y;
    camera_tz = camera_min_tz;
}

void CAvatar::InitProjectionMatrix()
{
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(camera_fovy, camera_aspect_ratio, camera_min_z, camera_max_z);
}

int CAvatar::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }

    SDL_Event event;
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    should_be_running = true;

    while(should_be_running) {
        while(SDL_PollEvent(&event)) {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
    OnCleanup();

    return 0;
}

bool CAvatar::OnInit()
{

    char sdl_wdw_pos[] = "SDL_VIDEO_WINDOW_POS";
    char sdl_wdw_ctr[] = "SDL_VIDEO_CENTERED=1";
    putenv(sdl_wdw_pos);
    putenv(sdl_wdw_ctr);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    window_width = 640;
    window_height = 480;
    window_title = "Avatar Main Window";

    SDL_WM_SetCaption(window_title, 0);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,    8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,    16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,    32);

//    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
//    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
//    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
//    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,    1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,    2);

    sdl_pimage = SDL_SetVideoMode(window_width, window_height, SDL_DEPTH, SDL_VIDEO_MODE_OPTIONS);
    if(sdl_pimage == NULL)
        return false;

    glEnable(GL_TEXTURE_2D);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glViewport(0, 0, window_width, window_height);

        camera_aspect_ratio = ((float)window_width) / ((float)window_height);
        camera_min_z = 0.1;
        camera_max_z = 10;
        camera_fovy = 60;

        InitProjectionMatrix();

        if((Surf_Temp = SDL_LoadBMP("")) == NULL) {
            //Error
        }

        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            return false;
        }

        /*if((Surf_Display = SDL_SetVideoMode(window_width, window_height, SDL_DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
            return false;
        }*/

        if((Surf_Test = CSurface::OnLoad("/home/user/Documents/SI4/S2/RA/Shared_Avatar/avatarProject/images/pattern.bmp")) == NULL) {
            return false;
        }

        // Typical Texture Generation Using Data From The Bitmap
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        texture = Load2DTexture(Surf_Test->w,Surf_Test->h,GL_RGB,Surf_Test->pixels);

    return true;
}

void CAvatar::OnCleanup()
{
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

void CAvatar::OnRender()
{
    if (! needs_rendering)
        return;
    needs_rendering = false;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    GLfloat scaling[] = {1, 0,   0, 0,
                         0, 1.5, 0, 0,
                         0, 0,   1, 0,
                         0, 0,   0, 1};

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-camera_tx, -camera_ty, -camera_tz);
    glRotatef(world_rx, 1, 0, 0);
    glRotatef(world_ry, 0, 1, 0);
    glMultMatrixf(scaling);

    DrawFrame(world_origin_x, world_origin_y, world_origin_z, RDR_FRAME_LENGTH);
    DrawCube(world_origin_x, world_origin_y, world_origin_z, RDR_CUBE_HALF_SIDE, texture);
    /*CSurface::OnDraw(Surf_Display, Surf_Test, 0, 0);
    CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
    SDL_Flip(Surf_Display);*/

    // On affiche Surf_Test

    SDL_GL_SwapBuffers();
}

void CAvatar::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void CAvatar::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {

        /* Quitter l'application */
        case SDLK_ESCAPE:
            OnExit();
            break;

        /* Recentrer la camera */
        case SDLK_SPACE:
            InitSceneConstants();
            needs_rendering = true;
            break;

        /*Deplacer le cube vers la gauche */
        case SDLK_LEFT:
            if(mod & KMOD_SHIFT)
            {
                world_ry -= SCENE_ROTATION_STEP;
                if(world_ry < 0)
                    world_ry += 360;
            }
            else
                camera_tx -= CAMERA_TRANSLATION_STEP;
            needs_rendering = true;
            break;

        /* Deplacer le cube vers la droite */
        case SDLK_RIGHT:
            if(mod & KMOD_SHIFT)
            {
                world_ry += SCENE_ROTATION_STEP;
                if(world_ry < 0)
                    world_ry += 360;
            }
            else
                camera_tx += CAMERA_TRANSLATION_STEP;
            needs_rendering = true;
            break;

        /* Deplacer le cube vers le bas */
        case SDLK_DOWN:
            if(mod & KMOD_SHIFT)
            {
                world_rx -= SCENE_ROTATION_STEP;
                if(world_rx < 0)
                    world_rx += 360;
            }
            else
                camera_ty -= CAMERA_TRANSLATION_STEP;
            needs_rendering = true;
            break;

        /* Deplacer le cube vers le haut */
        case SDLK_UP:
            if(mod & KMOD_SHIFT)
            {
                world_rx += SCENE_ROTATION_STEP;
                if(world_rx < 0)
                    world_rx += 360;
            }
            else
                camera_ty += CAMERA_TRANSLATION_STEP;
            needs_rendering = true;
            break;

        /* Zoom + */
        case SDLK_q:
            camera_tz -= CAMERA_TRANSLATION_STEP;
            if(camera_tz < camera_min_tz)
                camera_tz = camera_min_tz;
            needs_rendering = true;
            break;

        /* Zoom - */
        case SDLK_a:
            camera_tz += CAMERA_TRANSLATION_STEP;
            needs_rendering = true;
            break;
    }
}

void CAvatar::OnResize(int w, int h)
{
    window_width = w;
    window_height = h;

    SDL_FreeSurface(sdl_pimage);
    sdl_pimage = SDL_SetVideoMode(window_width, window_height, SDL_DEPTH, SDL_VIDEO_MODE_OPTIONS);

    glViewport(0, 0, window_width, window_height);

    camera_aspect_ratio = ((float)window_width) / ((float)window_height);
    InitProjectionMatrix();

    needs_rendering = true;
}

void CAvatar::OnExpose()
{
    // A completer
}

void CAvatar::OnExit()
{
    should_be_running = false;
}
