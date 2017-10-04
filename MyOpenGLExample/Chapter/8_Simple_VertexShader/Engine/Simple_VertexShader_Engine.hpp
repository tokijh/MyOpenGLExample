//
//  Simple_VertexShader_Engine.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef Simple_VertexShader_Engine_hpp
#define Simple_VertexShader_Engine_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "Simple_VertexShader_GLES.hpp"
#include "Simple_VertexShader_Matrix.hpp"
#include "Simple_VertexShader_Cube.hpp"

#ifdef _WIN32
#define srandom srand
#define random rand
#endif

class Simple_VertexShader_Engine {
private:
    int width, height;
    
public:
    Simple_VertexShader_Engine();
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

#endif /* Simple_VertexShader_Engine_hpp */
