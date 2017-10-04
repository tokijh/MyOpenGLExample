//
//  Simple_VertexShader_Matrix.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 4..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef Simple_VertexShader_Matrix_hpp
#define Simple_VertexShader_Matrix_hpp

#include <stdio.h>
#include <string>
#include <math.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

typedef struct
{
    GLfloat m[4][4];
} Simple_VertexShader_Matrix;

void matrixLoadIdentity(Simple_VertexShader_Matrix *result);
void matrixPerspective(Simple_VertexShader_Matrix *result, float fovy, float aspect, float nearZ, float farZ);
void matrixFrustum(Simple_VertexShader_Matrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
void matrixMultiply(Simple_VertexShader_Matrix *result, Simple_VertexShader_Matrix *srcA, Simple_VertexShader_Matrix *srcB);
void matrixTranslate(Simple_VertexShader_Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
void matrixRotate(Simple_VertexShader_Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

#endif /* Simple_VertexShader_Matrix_hpp */
