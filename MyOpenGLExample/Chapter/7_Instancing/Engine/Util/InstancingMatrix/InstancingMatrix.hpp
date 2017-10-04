//
//  InstancingMatrix.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 4..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef InstancingMatrix_hpp
#define InstancingMatrix_hpp

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
} Matrix;

void matrixLoadIdentity(Matrix *result);
void matrixPerspective(Matrix *result, float fovy, float aspect, float nearZ, float farZ);
void matrixFrustum(Matrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
void matrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB);
void matrixTranslate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
void matrixRotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

#endif /* InstancingMatrix_hpp */
