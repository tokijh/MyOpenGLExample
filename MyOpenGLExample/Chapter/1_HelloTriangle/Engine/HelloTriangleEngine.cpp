//
//  HelloTriangleEngine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "HelloTriangleEngine.hpp"

HelloTriangleEngine::HelloTriangleEngine() {
    
}

void HelloTriangleEngine::onCreate() {
    HelloTriangleGLES::makeProgram();
    
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
}

void HelloTriangleEngine::onViewWillAppear() {
    
}

void HelloTriangleEngine::onViewWillDisAppear() {
    
}

void HelloTriangleEngine::onDestroy() {
    
}

void HelloTriangleEngine::onChanged(int width, int height) {
    HelloTriangleEngine::width = width;
    HelloTriangleEngine::height = height;
    
    glViewport(0, 0, width, height);
}

void HelloTriangleEngine::onDraw() {
    GLfloat vVertices[] = {
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void HelloTriangleEngine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool HelloTriangleEngine::onBackButtonPressed() {
    return true;
}
