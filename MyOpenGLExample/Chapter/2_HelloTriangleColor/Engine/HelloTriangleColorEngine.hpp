//
//  HelloTriangleColorEngine.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef HelloTriangleColorEngine_hpp
#define HelloTriangleColorEngine_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "HelloTriangleColorGLES.hpp"

class HelloTriangleColorEngine {
private:
    int width, height;
public:
    HelloTriangleColorEngine();
    void onCreate();
    void onViewWillAppear();
    void onViewWillDisAppear();
    void onChanged(int width, int height);
    void onDraw();
    bool onBackButtonPressed();
    void onTouch(int eventsCount, int **touchInfo);
    void onDestroy();
};

#endif /* HelloTriangleColorEngine_hpp */
