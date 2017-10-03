//
//  HelloTriangleAdvanceColorEngine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "HelloTriangleAdvanceColorEngine.hpp"

#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1

HelloTriangleAdvanceColorEngine::HelloTriangleAdvanceColorEngine() {
    
}

void HelloTriangleAdvanceColorEngine::onCreate() {
    HelloTriangleAdvanceColorGLES::makeProgram();
    
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
}

void HelloTriangleAdvanceColorEngine::onViewWillAppear() {
    
}

void HelloTriangleAdvanceColorEngine::onViewWillDisAppear() {
    
}

void HelloTriangleAdvanceColorEngine::onDestroy() {
    glDeleteProgram(HelloTriangleAdvanceColorGLES::program);
    glDeleteBuffers(3, vboIds);
}

void HelloTriangleAdvanceColorEngine::onChanged(int width, int height) {
    HelloTriangleAdvanceColorEngine::width = width;
    HelloTriangleAdvanceColorEngine::height = height;
    
    glViewport(0, 0, width, height);
}

void HelloTriangleAdvanceColorEngine::onDraw() {
    
    GLfloat vertexPos[3 * VERTEX_POS_SIZE] =
    {
        0.0f,  0.5f, 0.0f,        // v0
        -0.5f, -0.5f, 0.0f,        // v1
        0.5f, -0.5f, 0.0f         // v2
    };
    GLfloat color[4 * VERTEX_COLOR_SIZE] =
    {
        1.0f, 0.0f, 0.0f, 1.0f,   // c0
        0.0f, 1.0f, 0.0f, 1.0f,   // c1
        0.0f, 0.0f, 1.0f, 1.0f    // c2
    };
    GLint vtxStrides[2] =
    {
        VERTEX_POS_SIZE * sizeof ( GLfloat ),
        VERTEX_COLOR_SIZE * sizeof ( GLfloat )
    };
    
    // Index buffer data
    GLushort indices[3] = { 0, 1, 2 };
    GLfloat *vtxBuf[2] = { vertexPos, color };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // vboIds[0] - used to store vertex position
    // vboIds[1] - used to store vertex color
    // vboIds[2] - used to store element indices
    if (vboIds[0] == 0 && vboIds[1] == 0 && vboIds[2] == 0 )
    {
        // Only allocate on the first draw
        glGenBuffers(3, vboIds);
        
        glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, vtxStrides[0] * 3,
                      vtxBuf[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
        glBufferData(GL_ARRAY_BUFFER, vtxStrides[1] * 3,
                      vtxBuf[1], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      sizeof ( GLushort ) * 3,
                      indices, GL_STATIC_DRAW);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE,
                           GL_FLOAT, GL_FALSE, vtxStrides[0], 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glEnableVertexAttribArray(VERTEX_COLOR_INDX);
    glVertexAttribPointer(VERTEX_COLOR_INDX,
                           VERTEX_COLOR_SIZE,
                           GL_FLOAT, GL_FALSE, vtxStrides[1], 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[2]);
    
    glDrawElements(GL_TRIANGLES, 3,
                    GL_UNSIGNED_SHORT, 0);
    
    glDisableVertexAttribArray(VERTEX_POS_INDX);
    glDisableVertexAttribArray(VERTEX_COLOR_INDX);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void HelloTriangleAdvanceColorEngine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool HelloTriangleAdvanceColorEngine::onBackButtonPressed() {
    return true;
}
