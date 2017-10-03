//
//  HelloTriangleAdvanceColorGLES.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef HelloTriangleAdvanceColorGLES_hpp
#define HelloTriangleAdvanceColorGLES_hpp

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

class HelloTriangleAdvanceColorGLES {
private:
    static string VERTEX_SHADER_NAME;
    static string FRAGMENT_SHADER_NAME;
public:
    static GLuint program;
    
    static void makeProgram();
    static GLuint loadShader(GLenum shaderType, const char *pSource);
};

#endif /* HelloTriangleAdvanceColorGLES_hpp */
