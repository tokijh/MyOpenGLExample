//
//  HelloTriangleAdvanceColor_VertexArrayObjects_Engine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "HelloTriangleAdvanceColor_VertexArrayObjects_Engine.hpp"

#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1

#define VERTEX_STRIDE         ( sizeof(GLfloat) *     \
( VERTEX_POS_SIZE +    \
VERTEX_COLOR_SIZE ) )

HelloTriangleAdvanceColor_VertexArrayObjects_Engine::HelloTriangleAdvanceColor_VertexArrayObjects_Engine() {
    
}

void HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onCreate() {
    HelloTriangleAdvanceColor_VertexArrayObjects_GLES::makeProgram();
    
    GLfloat vertices[3 * ( VERTEX_POS_SIZE + VERTEX_COLOR_SIZE )] = {
        0.0f,  0.5f, 0.0f,        // v0
        1.0f,  0.0f, 0.0f, 1.0f,  // c0
        -0.5f, -0.5f, 0.0f,        // v1
        0.0f,  1.0f, 0.0f, 1.0f,  // c1
        0.5f, -0.5f, 0.0f,        // v2
        0.0f,  0.0f, 1.0f, 1.0f,  // c2
    };
    // Index buffer data
    GLushort indices[3] = { 0, 1, 2 };
    
    glGenBuffers(2, vboIds);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Generate VAO Id
    glGenVertexArrays(1, &vaoId);
    
    // Bind the VAO and then setup the vertex
    // attributes
    glBindVertexArray(vaoId);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0] );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    glEnableVertexAttribArray(VERTEX_COLOR_INDX);
    
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (const void *) 0);
    
    glVertexAttribPointer(VERTEX_COLOR_INDX, VERTEX_COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (const void *) (VERTEX_POS_SIZE * sizeof(GLfloat)));
    
    // Reset to the default VAO
    glBindVertexArray(0);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onViewWillAppear() {
    
}

void HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onViewWillDisAppear() {
    
}

void HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onDestroy() {
    glDeleteProgram(HelloTriangleAdvanceColor_VertexArrayObjects_GLES::program);
    glDeleteBuffers(2, vboIds);
    glDeleteVertexArrays(1, &vaoId);
}

void HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onChanged(int width, int height) {
    HelloTriangleAdvanceColor_VertexArrayObjects_Engine::width = width;
    HelloTriangleAdvanceColor_VertexArrayObjects_Engine::height = height;
    
    glViewport(0, 0, width, height);
}

void HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onDraw() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Bind the VAO
    glBindVertexArray(vaoId);
    
    // Draw with the VAO settings
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (const void *) 0);
    
    // Return to the default VAO
    glBindVertexArray(0);
}

void HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool HelloTriangleAdvanceColor_VertexArrayObjects_Engine::onBackButtonPressed() {
    return true;
}
