//
//  HelloTriangleAdvanceColor_VertexBufferObjects_Engine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "HelloTriangleAdvanceColor_VertexBufferObjects_Engine.hpp"

#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1

HelloTriangleAdvanceColor_VertexBufferObjects_Engine::HelloTriangleAdvanceColor_VertexBufferObjects_Engine() {
    
}

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onCreate() {
    HelloTriangleAdvanceColor_VertexBufferObjects_GLES::makeProgram();
    
    offsetLoc = glGetUniformLocation(HelloTriangleAdvanceColor_VertexBufferObjects_GLES::program, "u_offset");
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onViewWillAppear() {
    
}

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onViewWillDisAppear() {
    
}

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onDestroy() {
    glDeleteProgram(HelloTriangleAdvanceColor_VertexBufferObjects_GLES::program);
    glDeleteBuffers(2, vboIds);
}

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onChanged(int width, int height) {
    HelloTriangleAdvanceColor_VertexBufferObjects_Engine::width = width;
    HelloTriangleAdvanceColor_VertexBufferObjects_Engine::height = height;
    
    glViewport(0, 0, width, height);
}

//
// vertices   - pointer to a buffer that contains vertex
//              attribute data
// vtxStride  - stride of attribute data / vertex in bytes
// numIndices - number of indices that make up primitive
//              drawn as triangles
// indices    - pointer to element index buffer.
//
void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::DrawPrimitiveWithoutVBOs(GLfloat *vertices, GLint vtxStride, GLint numIndices, GLushort *indices)
{
    GLfloat *vtxBuf = vertices;
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    glEnableVertexAttribArray(VERTEX_COLOR_INDX);
    
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, vtxStride, vtxBuf);
    vtxBuf += VERTEX_POS_SIZE;
    
    glVertexAttribPointer(VERTEX_COLOR_INDX, VERTEX_COLOR_SIZE, GL_FLOAT, GL_FALSE, vtxStride, vtxBuf);
    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, indices);
    
    glDisableVertexAttribArray(VERTEX_POS_INDX);
    glDisableVertexAttribArray(VERTEX_COLOR_INDX);
}

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::DrawPrimitiveWithVBOs(GLint numVertices, GLfloat *vtxBuf,GLint vtxStride, GLint numIndices, GLushort *indices)
{
    GLuint offset = 0;
    
    // vboIds[0] - used to store vertex attribute data
    // vboIds[l] - used to store element indices
    if (vboIds[0] == 0 && vboIds[1] == 0)
    {
        // Only allocate on the first draw
        glGenBuffers(2, vboIds);
        
        glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, vtxStride * numVertices, vtxBuf, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numIndices, indices, GL_STATIC_DRAW);
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

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onDraw() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 3 vertices, with (x,y,z) ,(r, g, b, a) per-vertex
    GLfloat vertices[3 * ( VERTEX_POS_SIZE + VERTEX_COLOR_SIZE )] =
    {
        -0.5f,  0.5f, 0.0f,        // v0
        1.0f,  0.0f, 0.0f, 1.0f,  // c0
        -1.0f, -0.5f, 0.0f,        // v1
        0.0f,  1.0f, 0.0f, 1.0f,  // c1
        0.0f, -0.5f, 0.0f,        // v2
        0.0f,  0.0f, 1.0f, 1.0f,  // c2
    };
    // Index buffer data
    GLushort indices[3] = { 0, 1, 2 };
    
    glUniform1f(offsetLoc, 0.0f);

    DrawPrimitiveWithoutVBOs(vertices, sizeof(GLfloat) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE), 3, indices);
    
    // Offset the vertex positions so both can be seen
    glUniform1f(offsetLoc, 1.0f);
    
    DrawPrimitiveWithVBOs(3, vertices, sizeof(GLfloat) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE), 3, indices);
}

void HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool HelloTriangleAdvanceColor_VertexBufferObjects_Engine::onBackButtonPressed() {
    return true;
}
