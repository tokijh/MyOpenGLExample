//
//  HelloTriangleColorGLES.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef HelloTriangleColorGLES_hpp
#define HelloTriangleColorGLES_hpp

#include <string>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "DataManager.hpp"

using namespace std;

class HelloTriangleColorGLES {
private:
    static string VERTEX_SHADER_NAME;
    static string FRAGMENT_SHADER_NAME;
public:
    static GLuint program;
    
    static void makeProgram();
    static GLuint loadShader(GLenum shaderType, const char *pSource);
};

#endif /* HelloTriangleColorGLES_hpp */
