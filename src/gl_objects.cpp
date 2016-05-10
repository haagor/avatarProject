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


    glColor4f(1,1,1,0);
    glBegin(GL_QUADS);
        // front
        glTexCoord2f(1, 0);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z + half_side);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z + half_side);

        // back

        glTexCoord2f(1, 1);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(1, 0);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z - half_side);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z - half_side);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z - half_side);

        // left

        glTexCoord2f(0, 0);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z - half_side);

        glTexCoord2f(1, 0);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y - half_side, origin_z + half_side);

        // right

        glTexCoord2f(0,1);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(0,0);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(1,0);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z + half_side);

        glTexCoord2f(1,1);
        glVertex3f(origin_x + half_side, origin_y - half_side, origin_z - half_side);

        // top

        glTexCoord2f(0, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z + half_side);

        glTexCoord2f(0, 0);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z + half_side);
        glTexCoord2f(1, 0);
        glVertex3f(origin_x + half_side, origin_y + half_side, origin_z - half_side);

        glTexCoord2f(1, 1);
        glVertex3f(origin_x - half_side, origin_y + half_side, origin_z - half_side);

        // bottom

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

void FillWindowWithTexture(GLuint texture_ID){
}

void DrawCanoniqueCube(/*GLuint texture*/)
{
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glColor4f(1,1,1,0);
    glBegin(GL_QUADS);

    // Front
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);

    // Left
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);

    // Right
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);

    // Back
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);

    // Top
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    // Bottom
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);

    glEnd();
}

void DrawArm(int teta, int phi)
{
    // Bras
    glScalef(2, 1, 1);
    glTranslatef(1.5, 0, 0);
    DrawCanoniqueCube();

    // Avant bras
    glPushMatrix();
        glTranslatef(2, 0, 0);
        glRotatef(teta, 0, 0, 1);
        DrawCanoniqueCube();

        // Main
        glPushMatrix();
            glTranslatef(1.5, 0, -0.5);
            glRotatef(phi, 1, 0, 0);
            glScalef(0.5, 1.5, 1);
            DrawCanoniqueCube();
        glPopMatrix();
    glPopMatrix();

}
