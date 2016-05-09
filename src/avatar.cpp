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
    mouse_left_down = false;
    mouse_right_down = false;
}

CAvatar::~CAvatar() {}

void CAvatar::InitSceneConstants()
{

    world_rx = 0;
    world_ry = 0;

    camera_min_tz = world_origin_z + CAMERA_Z_OFFSET + 200;
    camera_tx = world_origin_x;
    camera_ty = world_origin_y;
    camera_tz = camera_min_tz;
}

void CAvatar::SetPerspectiveProjectionMatrix()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera_fovy, camera_aspect_ratio, camera_min_z, camera_max_z);
}

int CAvatar::OnExecute(bool ancient_code)
{
    if(OnInit(ancient_code) == false)
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

bool CAvatar::OnInit(bool ancient_code)
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
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat colorBronzeDiff[] = {1.0, 1.0, 0.0, 0.0};
    GLfloat colorBronzeSpec[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_emission[] = {0.1, 0.1, 0.1, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, window_width, window_height);

    camera_aspect_ratio = ((float)window_width) / ((float)window_height);
    camera_min_z = 0.1;
    camera_max_z = 10;
    camera_fovy = 60;

    SetPerspectiveProjectionMatrix();

    if((Surf_Temp = SDL_LoadBMP("")) == NULL) {
        //Error
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Test = CSurface::OnLoad("/home/user/Documents/SI4/S2/RA/Shared_Avatar/avatarProject/images/Uncolored_Glass.bmp")) == NULL) {
        return false;
    }

    // Typical Texture Generation Using Data From The Bitmap
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    texture = Load2DTexture(Surf_Test->w, Surf_Test->h, 4, Surf_Test->pixels);

    //sensor.OnInit(ancient_code);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, window_width, window_height);

    camera_aspect_ratio = ((float)window_width) / ((float)window_height);
    camera_min_z = 0.1;
    camera_max_z = 10;
    camera_fovy = 60;

    SetPerspectiveProjectionMatrix();

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
    if(ancient_code == 1)
    {
        DrawDemo();
    } else
    {
        DrawSensor();
    }
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

    case(SDLK_c):
        sensor.active_stream = color_stream;
        InitSceneConstants();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        SetOrthoProjectionMatrix();
        sensor.OnInit(true);
        DrawSensor();
        break;

    case(SDLK_p):
        sensor.active_stream = depth_stream1;
        InitSceneConstants();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        SetPerspectiveProjectionMatrix();
        sensor.OnInit(false);
        break;
    }
}

void CAvatar::OnMouseWheel(int bouton,int dir) {
    std::cout << bouton << " " << dir <<std::endl;
}

void CAvatar::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle){
    if (mouse_left_down){
        if (relX <0)
            camera_tx += CAMERA_TRANSLATION_STEP;
        else if(relX >0)
            camera_tx -= CAMERA_TRANSLATION_STEP;
        needs_rendering = true;

        if (relY <0)
            camera_ty -= CAMERA_TRANSLATION_STEP;
        else if(relY >0)
            camera_ty += CAMERA_TRANSLATION_STEP;
        needs_rendering = true;

    }

    if (mouse_right_down){
        if (relX <0)
            world_ry -= SCENE_ROTATION_STEP;
        else if(relX >0)
            world_ry += SCENE_ROTATION_STEP;
        needs_rendering = true;

        if (relY <0)
            world_rx -= SCENE_ROTATION_STEP;
        else if(relY >0)
            world_rx += SCENE_ROTATION_STEP;
        needs_rendering = true;
    }
}

void CAvatar::OnLButtonDown(int mX, int mY) {
    mouse_left_down = true;
}

void CAvatar::OnLButtonUp(int mX, int mY) {
    mouse_left_down = false;
}
void CAvatar::OnRButtonDown(int mX, int mY){
    mouse_right_down = true;
}
void CAvatar::OnRButtonUp(int mX, int mY){
    mouse_right_down = false;
}

void CAvatar::OnResize(int w, int h)
{
    window_width = w;
    window_height = h;

    SDL_FreeSurface(sdl_pimage);
    sdl_pimage = SDL_SetVideoMode(window_width, window_height, SDL_DEPTH, SDL_VIDEO_MODE_OPTIONS);

    glViewport(0, 0, window_width, window_height);

    camera_aspect_ratio = ((float)window_width) / ((float)window_height);
    SetPerspectiveProjectionMatrix();

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

void CAvatar::DrawDemo() {
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

    //DrawFrame(world_origin_x, world_origin_y, world_origin_z, RDR_FRAME_LENGTH);
    //DrawCube(world_origin_x, world_origin_y, world_origin_z, RDR_CUBE_HALF_SIDE, texture);
    //DrawCanoniqueCube();
    DrawArm();
    SDL_GL_SwapBuffers();

}

float *CAvatar::AccessFrameDepth(openni::VideoFrameRef *m_depthFrame)
{
    sensor.m_depthStream.readFrame(m_depthFrame);
    if (! m_depthFrame->isValid())
        return NULL;
    openni::DepthPixel* pImage = (openni::DepthPixel*) m_depthFrame->getData();

    int taille= sizeof(pImage)/sizeof(openni::DepthPixel);
    float *pImageFloat= new float[taille];

    for(int i=0; i<taille; i++ ){
        pImageFloat[i] = (float) pImage[i]/255.0;
    }

    return pImageFloat;
}

void CAvatar::DrawSensor()
{
    /*    //const floatRGB* pImageColorFloat;
    float **pImageColorFloat;
    const float* pImageDepthFloat;
    openni::VideoFrameRef m_depthFrame;


    if (sensor.active_stream == color_stream) {
        pImageColorFloat = AccessFrameColor();
        captured= Load2DTexture(window_width, window_height, GL_RGBA, pImageColorFloat);

        glClearColor(0,0,0,0);
        glViewport(0,0,window_width,window_height);

        SetPerspectiveProjectionMatrix();

        glEnable(GL_TEXTURE_2D);
        DrawCube(world_origin_x,world_origin_y,world_origin_z,RDR_CUBE_HALF_SIDE,captured);
        //FillWindowWithTexture(captured);
        //glDeleteTextures(1,(GLuint *)captured);
    }
    else if (sensor.active_stream == depth_stream1){
        // on croit qu'on va essayer de mettre les textures de profondeur...
        pImageDepthFloat = AccessFrameDepth(&m_depthFrame);


        int width = m_depthFrame.getWidth();
        int height = m_depthFrame.getHeight();

        float pWorldX, pWorldY, pWorldZ;


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_DEPTH_TEST);
        glPointSize(2);
        glBegin(GL_POINTS);

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                for (int z=0; z<sizeof(pImageDepthFloat)/sizeof(openni::DepthPixel); z++)
                {
                    if ((x%2 == 0) && (y%2 == 0) && (*pImageDepthFloat != 0) && (*pImageDepthFloat < 2000))
                    {
                        //convertDepthToWorld(const VideoStream& depthStream, float depthX, float depthY, float depthZ, float* pWorldX, float* pWorldY, float* pWorldZ)
                        openni::CoordinateConverter::convertDepthToWorld(sensor.m_depthStream,
                                                                         (float)x, (float)y, pImageDepthFloat[z], &pWorldX, &pWorldY, &pWorldZ);
                        glColor3f(0.2, 0.4, 0.6);
                        glVertex3f(pWorldX / 1000.0, pWorldY / 1000.0, pWorldZ / 500.0);
                    }
                }
        glEnd();
        // vider les buffers
        SDL_GL_SwapBuffers();
    }*/
}

float **CAvatar::AccessFrameColor()
{
    const openni::RGB888Pixel* pImageColor;
    openni::VideoFrameRef m_colorFrame;

    sensor.m_colorStream.readFrame(&m_colorFrame);
    if (! m_colorFrame.isValid())
        return NULL;
    pImageColor = (openni::RGB888Pixel *)m_colorFrame.getData();
    int taille = m_colorFrame.getDataSize() / 3;
    float **pImageColorFloat;

    pImageColorFloat = (float **) malloc(sizeof(floatRGB)*taille);
    for(int i=0; i<taille; i++ ){
        pImageColorFloat[i] = ( float * ) malloc( 3 * sizeof(float) ) ;
        pImageColorFloat[i][0]= pImageColor[i].r/255.0;
        pImageColorFloat[i][1]= pImageColor[i].g/255.0;
        pImageColorFloat[i][2]= pImageColor[i].b/255.0;
    }

    return pImageColorFloat;
}

/*
 *
 * Warning: USB events thread - failed to set priority. This might cause loss of data...
    Device.setProperty(5) failed
 *
 * */

void CAvatar::SetOrthoProjectionMatrix()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -10, 10);
}
