//
//  InstancingEngine.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef InstancingEngine_hpp
#define InstancingEngine_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "InstancingGLES.hpp"
#include "InstancingMatrix.hpp"
#include "InstancingCube.hpp"

#ifdef _WIN32
#define srandom srand
#define random rand
#endif

#define NUM_INSTANCES   100
#define POSITION_LOC    0
#define COLOR_LOC       1
#define MVP_LOC         2

class InstancingEngine {
private:
    int width, height;
    
    // VBOs
    GLuint positionVBO;
    GLuint colorVBO;
    GLuint mvpVBO;
    GLuint indicesIBO;
    
    // Number of indices
    int numIndices;
    
    // Rotation angle
    GLfloat angle[NUM_INSTANCES];
    
public:
    InstancingEngine();
    void onCreate();
    void onViewWillAppear();
    void onViewWillDisAppear();
    void onChanged(int width, int height);
    void onUpdate(float deltaTime);
    void onDraw();
    bool onBackButtonPressed();
    void onTouch(int eventsCount, int **touchInfo);
    void onDestroy();
};

#endif /* InstancingEngine_hpp */
