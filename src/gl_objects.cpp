#include "gl_objects.h"
#include <iostream>

using namespace std;

void DrawFrame(float origin_x, float origin_y, float origin_z, float frame_length)
{
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(origin_x, origin_y, origin_z);
        glVertex3f(origin_x + frame_length, origin_y, origin_z);

        glColor3f(0, 0, 1);
        glVertex3f(origin_x, origin_y, origin_z);
        glVertex3f(origin_x, origin_y + frame_length, origin_z);

        glColor3f(0, 1, 0);
        glVertex3f(origin_x, origin_y, origin_z);
        glVertex3f(origin_x, origin_y, origin_z + frame_length);
    glEnd();
}

void DrawCube(float origin_x, float origin_y, float origin_z, float half_side, GLuint texture)
{

    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        // front
        glColor3f(0, 1, 0);

        glTexCoord2f(1, 0);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z + half_side);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z + half_side);

        // back
        glColor3f(0, 0.5, 0);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(1, 0);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z - half_side);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z - half_side);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z - half_side);

        // left
        glColor3f(0.5, 0, 0);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z - half_side);

        glTexCoord2f(1, 0);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z + half_side);

        // right
        glColor3f(1, 0, 0);

        glTexCoord2f(0,1);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(0,0);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(1,0);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z + half_side);

        glTexCoord2f(1,1);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z - half_side);

        // top
        glColor3f(0, 0, 1);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z + half_side);
        glTexCoord2f(1, 0);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z - half_side);

        // bottom
        glColor3f(0, 0, 0.5);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z + half_side);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z + half_side);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z - half_side);

        glTexCoord2f(1, 0);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z - half_side);

    glEnd();
}


GLuint Load2DTexture(GLsizei width, GLsizei height, int BytesPerPixel, const GLvoid * data)
{
    GLuint texture_ID;
    glGenTextures(1, &texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int color_mode = (BytesPerPixel == 3 ? GL_RGB : GL_RGBA);

    glTexImage2D(GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, data);

    return texture_ID;
}
