//
//  Simple_VertexShader_GLES.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef Simple_VertexShader_GLES_hpp
#define Simple_VertexShader_GLES_hpp

#include <string>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "DataManager.hpp"
#include "Simple_VertexShader_Matrix.hpp"

using namespace std;

class Simple_VertexShader_GLES {
private:
    static string VERTEX_SHADER_NAME;
    static string FRAGMENT_SHADER_NAME;
public:
    static GLuint program;
    
    // Uniform locations
    static GLint mvpLoc;
    
    // Vertex daata
    static GLfloat *vertices;
    static GLuint *indices;
    static int numIndices;
    
    // Rotation angle
    static GLfloat angle;
    
    // MVP matrix
    static Simple_VertexShader_Matrix mvpMatrix;
    
    static void makeProgram();
    static GLuint loadShader(GLenum shaderType, const char *pSource);
};

#endif /* Simple_VertexShader_GLES_hpp */
