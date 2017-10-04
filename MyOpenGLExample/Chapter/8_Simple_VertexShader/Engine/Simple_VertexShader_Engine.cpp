//
//  Simple_VertexShader_Engine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "Simple_VertexShader_Engine.hpp"

Simple_VertexShader_Engine::Simple_VertexShader_Engine() {
    
}

void Simple_VertexShader_Engine::onCreate() {
    Simple_VertexShader_GLES::makeProgram();
    
    // Get the uniform locations
    Simple_VertexShader_GLES::mvpLoc = glGetUniformLocation(Simple_VertexShader_GLES::program, "u_mvpMatrix");
    
    // Generate the vertex data
    Simple_VertexShader_GLES::numIndices = Simple_VertexShader_Cube::genCube(1.0, &Simple_VertexShader_GLES::vertices, NULL, NULL, &Simple_VertexShader_GLES::indices);
    
    // Starting rotation angle for the cube
    Simple_VertexShader_GLES::angle = 45.0f;

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void Simple_VertexShader_Engine::onViewWillAppear() {
    
}

void Simple_VertexShader_Engine::onViewWillDisAppear() {
    
}

void Simple_VertexShader_Engine::onDestroy() {
    // Delete program object
    glDeleteProgram(Simple_VertexShader_GLES::program);
    
    if (Simple_VertexShader_GLES::vertices != NULL) {
        free(Simple_VertexShader_GLES::vertices);
    }
    
    if (Simple_VertexShader_GLES::indices != NULL) {
        free(Simple_VertexShader_GLES::indices);
    }
}

void Simple_VertexShader_Engine::onChanged(int width, int height) {
    Simple_VertexShader_Engine::width = width;
    Simple_VertexShader_Engine::height = height;
    
    glViewport(0, 0, width, height);
}

void Simple_VertexShader_Engine::onUpdate(float deltaTime) {
    Simple_VertexShader_Matrix perspective;
    Simple_VertexShader_Matrix modelview;
    float aspect;
    
    // Compute a rotation angle based on time to rotate the cube
    Simple_VertexShader_GLES::angle += (deltaTime * 40.0f);
    
    if (Simple_VertexShader_GLES::angle >= 360.0f)
    {
        Simple_VertexShader_GLES::angle -= 360.0f;
    }
    
    // Compute the window aspect ratio
    aspect = (GLfloat) width / (GLfloat) height;
    
    // Generate a perspective matrix with a 60 degree FOV
    matrixLoadIdentity(&perspective);
    matrixPerspective(&perspective, 60.0f, aspect, 1.0f, 20.0f);
    
    // Generate a model view matrix to rotate/translate the cube
    matrixLoadIdentity(&modelview);
    
    // Translate away from the viewer
    matrixTranslate(&modelview, 0.0, 0.0, -2.0);
    
    // Rotate the cube
    matrixRotate(&modelview, Simple_VertexShader_GLES::angle, 1.0, 0.0, 1.0);
    
    // Compute the final MVP by multiplying the
    // modevleiw and perspective matrices together
    matrixMultiply(&Simple_VertexShader_GLES::mvpMatrix, &modelview, &perspective);
}

void Simple_VertexShader_Engine::onDraw() {
    
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use the program object
    glUseProgram(Simple_VertexShader_GLES::program);
    
    // Load the vertex position
    glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof ( GLfloat ), Simple_VertexShader_GLES::vertices );
    
    glEnableVertexAttribArray ( 0 );
    
    // Set the vertex color to red
    glVertexAttrib4f ( 1, 1.0f, 0.0f, 0.0f, 1.0f );
    
    // Load the MVP matrix
    glUniformMatrix4fv(Simple_VertexShader_GLES::mvpLoc, 1, GL_FALSE, (GLfloat *) &Simple_VertexShader_GLES::mvpMatrix.m[0][0]);
    
    // Draw the cube
    glDrawElements ( GL_TRIANGLES, Simple_VertexShader_GLES::numIndices, GL_UNSIGNED_INT, Simple_VertexShader_GLES::indices );
}

void Simple_VertexShader_Engine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool Simple_VertexShader_Engine::onBackButtonPressed() {
    return true;
}
