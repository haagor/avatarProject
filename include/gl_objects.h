#ifndef _GL_OBJECTS_H_
#define _GL_OBJECTS_H_

#include <GL/gl.h>

void DrawFrame(float origin_x, float origin_y, float origin_z, float frame_length);
void DrawCube(float origin_x, float origin_y, float origin_z, float half_side, GLuint texture);
void DrawCanoniqueCube();
void DrawArm();
GLuint Load2DTexture(GLsizei width, GLsizei height, int BytesPerPixel, const GLvoid * data);

#endif
