//
//  HelloTriangleAdvanceColor_VertexBufferObjects_Engine.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef HelloTriangleAdvanceColor_VertexBufferObjects_Engine_hpp
#define HelloTriangleAdvanceColor_VertexBufferObjects_Engine_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
#include "HelloTriangleAdvanceColor_VertexBufferObjects_GLES.hpp"

class HelloTriangleAdvanceColor_VertexBufferObjects_Engine {
private:
    int width, height;
    
    // VertexBufferObject Ids
    GLuint vboIds[2] = {};
    
    // x-offset uniform location
    GLuint offsetLoc;
    
    void DrawPrimitiveWithoutVBOs(GLfloat *vertices, GLint vtxStride, GLint numIndices, GLushort *indices);
    void DrawPrimitiveWithVBOs(GLint numVertices, GLfloat *vtxBuf,GLint vtxStride, GLint numIndices, GLushort *indices);
public:
    HelloTriangleAdvanceColor_VertexBufferObjects_Engine();
    void onCreate();
    void onViewWillAppear();
    void onViewWillDisAppear();
    void onChanged(int width, int height);
    void onDraw();
    bool onBackButtonPressed();
    void onTouch(int eventsCount, int **touchInfo);
    void onDestroy();
};

#endif /* HelloTriangleAdvanceColor_VertexBufferObjects_Engine_hpp */
