//
//  HelloTriangleAdvanceColor_MapBuffers_Engine.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef HelloTriangleAdvanceColor_MapBuffers_Engine_hpp
#define HelloTriangleAdvanceColor_MapBuffers_Engine_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "HelloTriangleAdvanceColor_MapBuffers_GLES.hpp"

class HelloTriangleAdvanceColor_MapBuffers_Engine {
private:
    int width, height;
    
    GLuint vboIds[2] = {};
public:
    HelloTriangleAdvanceColor_MapBuffers_Engine();
    void onCreate();
    void onViewWillAppear();
    void onViewWillDisAppear();
    void onChanged(int width, int height);
    void onDraw();
    bool onBackButtonPressed();
    void onTouch(int eventsCount, int **touchInfo);
    void onDestroy();
};

#endif /* HelloTriangleAdvanceColor_MapBuffers_Engine_hpp */
