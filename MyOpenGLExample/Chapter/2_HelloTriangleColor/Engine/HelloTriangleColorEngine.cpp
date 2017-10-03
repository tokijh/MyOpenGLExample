//
//  HelloTriangleColorEngine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "HelloTriangleColorEngine.hpp"

HelloTriangleColorEngine::HelloTriangleColorEngine() {
    
}

void HelloTriangleColorEngine::onCreate() {
    HelloTriangleColorGLES::makeProgram();
    
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
}

void HelloTriangleColorEngine::onViewWillAppear() {
    
}

void HelloTriangleColorEngine::onViewWillDisAppear() {
    
}

void HelloTriangleColorEngine::onDestroy() {
    
}

void HelloTriangleColorEngine::onChanged(int width, int height) {
    HelloTriangleColorEngine::width = width;
    HelloTriangleColorEngine::height = height;
    
    glViewport(0, 0, width, height);
}

void HelloTriangleColorEngine::onDraw() {
    
    GLfloat color[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    
    GLfloat vertexPos[] = {
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertexPos);
    glEnableVertexAttribArray(0);
    glVertexAttrib4fv(1, color);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void HelloTriangleColorEngine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool HelloTriangleColorEngine::onBackButtonPressed() {
    return true;
}
