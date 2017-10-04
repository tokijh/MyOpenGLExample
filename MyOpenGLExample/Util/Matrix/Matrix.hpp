//
//  Matrix.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 4..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#define I(_i, _j) ((_j)+ 4*(_i))

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include <math.h>
#include <string>
#include "Logger.h"

class Matrix {
public:
    Matrix();
    
    static GLfloat sTemp[32];
    
    static void loadIdentity(GLfloat *result);
    static void multiplyMM(GLfloat *result, GLuint resultOffset, const GLfloat *lhs, GLuint lhsOffset, const GLfloat *rhs, GLuint rhsOffset);
    static void multiplyMV(GLfloat *resultVec, GLuint resultVecOffset, GLfloat *lhsMat, GLuint lhsMatOffset, GLfloat *rhsVec, GLuint rhsVecOffset);
    static void transposeM(GLfloat *mTrans, GLuint mTransOffset, const GLfloat *m, GLuint mOffset);
    static bool invertM(GLfloat *mInv, GLuint mInvOffset, const GLfloat *m, GLuint mOffset);
    static void orthoM(GLfloat *m, GLuint mOffset, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
    static void frustumM(GLfloat *m, GLuint offset, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
    static void perspectiveM(GLfloat *m, GLuint offset, GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);
    static GLfloat length(GLfloat x, GLfloat y, GLfloat z);
    static void setIdentityM(GLfloat *sm, GLuint smOffset);
    static void scaleM(GLfloat *sm, GLuint smOffset, const GLfloat *m, GLuint mOffset, GLfloat x, GLfloat y, GLfloat z);
    static void scaleM(GLfloat *m, GLuint mOffset, GLfloat x, GLfloat y, GLfloat z);
    static void translateM(GLfloat *tm, GLuint tmOffset, const GLfloat *m, GLuint mOffset, GLfloat x, GLfloat y, GLfloat z);
    static void translateM(GLfloat *m, GLuint mOffset, GLfloat x, GLfloat y, GLfloat z);
    static void rotateM(GLfloat *rm, GLuint rmOffset, const GLfloat *m, GLuint mOffset, GLfloat a, GLfloat x, GLfloat y, GLfloat z);
    static void rotateM(GLfloat *m, GLuint mOffset, GLfloat a, GLfloat x, GLfloat y, GLfloat z);
    static void setRotateM(GLfloat *rm, GLuint rmOffset, GLfloat a, GLfloat x, GLfloat y, GLfloat z);
    static void setRotateEulerM(GLfloat *rm, GLuint rmOffset, GLfloat x, GLfloat y, GLfloat z);
    static void setLookAtM(GLfloat *rm, GLuint rmOffset, GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ);
    
};

#endif /* Matrix_hpp */
