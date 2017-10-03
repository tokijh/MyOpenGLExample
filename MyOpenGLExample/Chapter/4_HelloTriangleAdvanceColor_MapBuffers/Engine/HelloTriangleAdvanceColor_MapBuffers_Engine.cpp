//
//  HelloTriangleAdvanceColor_MapBuffers_Engine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "HelloTriangleAdvanceColor_MapBuffers_Engine.hpp"

#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1

HelloTriangleAdvanceColor_MapBuffers_Engine::HelloTriangleAdvanceColor_MapBuffers_Engine() {
    
}

void HelloTriangleAdvanceColor_MapBuffers_Engine::onCreate() {
    HelloTriangleAdvanceColor_MapBuffers_GLES::makeProgram();
    
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
}

void HelloTriangleAdvanceColor_MapBuffers_Engine::onViewWillAppear() {
    
}

void HelloTriangleAdvanceColor_MapBuffers_Engine::onViewWillDisAppear() {
    
}

void HelloTriangleAdvanceColor_MapBuffers_Engine::onDestroy() {
    glDeleteProgram(HelloTriangleAdvanceColor_MapBuffers_GLES::program);
    glDeleteBuffers(2, vboIds);
}

void HelloTriangleAdvanceColor_MapBuffers_Engine::onChanged(int width, int height) {
    HelloTriangleAdvanceColor_MapBuffers_Engine::width = width;
    HelloTriangleAdvanceColor_MapBuffers_Engine::height = height;
    
    glViewport(0, 0, width, height);
}

void HelloTriangleAdvanceColor_MapBuffers_Engine::onDraw() {
    
    // 3 vertices, with (x,y,z) ,(r, g, b, a) per-vertex
    GLfloat vertices[3 * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE)] =
    {
        0.0f,  0.5f, 0.0f,        // v0
        1.0f,  0.0f, 0.0f, 1.0f,  // c0
        -0.5f, -0.5f, 0.0f,        // v1
        0.0f,  1.0f, 0.0f, 1.0f,  // c1
        0.5f, -0.5f, 0.0f,        // v2
        0.0f,  0.0f, 1.0f, 1.0f,  // c2
    };
    // Index buffer data
    GLushort indices[3] = { 0, 1, 2 };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLuint offset = 0;
    
    GLint numVertices = 3;
    GLint vtxStride = sizeof(GLfloat) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE);
    GLint numIndices = 3;
    
    // vboIds[0] - used to store vertex attribute data
    // vboIds[l] - used to store element indices
    if (vboIds[0] == 0 && vboIds[1] == 0) {
        GLfloat *vtxMappedBuf;
        GLushort *idxMappedBuf;
        
        // Only allocate on the first draw
        glGenBuffers(2, vboIds);
        
        glBindBuffer( GL_ARRAY_BUFFER, vboIds[0] );
        glBufferData( GL_ARRAY_BUFFER, vtxStride * numVertices,
                      NULL, GL_STATIC_DRAW );
        
        vtxMappedBuf = (GLfloat *) glMapBufferRange(GL_ARRAY_BUFFER, 0, vtxStride * numVertices, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        
        if (vtxMappedBuf == NULL)
        {
            LOGE("Error mapping vertex buffer object.");
            return;
        }
        
        // Copy the data into the mapped buffer
        memcpy(vtxMappedBuf, vertices, vtxStride * numVertices);
        
        // Unmap the buffer
        if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE)
        {
            LOGE("Error unmapping array buffer object.");
            return;
        }
        
        // Map the index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numIndices, NULL, GL_STATIC_DRAW);
        idxMappedBuf = (GLushort *) glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLushort) * numIndices, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        
        if (idxMappedBuf == NULL)
        {
            LOGE("Error mapping element array buffer object.");
            return;
        }
        
        // Copy the data into the mapped buffer
        memcpy(idxMappedBuf, indices, sizeof(GLushort) * numIndices);
        
        // Unmap the buffer
        if (glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) == GL_FALSE)
        {
            LOGE("Error unmapping element array buffer object.");
            return;
        }
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    glEnableVertexAttribArray(VERTEX_COLOR_INDX);
    
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, vtxStride, (const void *) offset);
    
    offset += VERTEX_POS_SIZE * sizeof(GLfloat);
    glVertexAttribPointer(VERTEX_COLOR_INDX, VERTEX_COLOR_SIZE, GL_FLOAT, GL_FALSE, vtxStride, (const void *) offset);
    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
    
    glDisableVertexAttribArray(VERTEX_POS_INDX);
    glDisableVertexAttribArray(VERTEX_COLOR_INDX);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void HelloTriangleAdvanceColor_MapBuffers_Engine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool HelloTriangleAdvanceColor_MapBuffers_Engine::onBackButtonPressed() {
    return true;
}
