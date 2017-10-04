//
//  InstancingEngine.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "InstancingEngine.hpp"

InstancingEngine::InstancingEngine() {
    
}

void InstancingEngine::onCreate() {
    InstancingGLES::makeProgram();
    
    GLfloat *positions;
    GLuint *indices;
    
    // Generate the vertex data
    numIndices = InstancingCube::genCube(0.1f, &positions, NULL, NULL, &indices);
    
    // Index buffer object
    glGenBuffers(1, &indicesIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    free(indices);
    
    // Position VBO for cube model
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat) * 3, positions, GL_STATIC_DRAW);
    free(positions);
    
    // Random color for each instance
    {
        GLubyte colors[NUM_INSTANCES][4];
        int instance;
        
        srandom(0);
        
        for (instance = 0; instance < NUM_INSTANCES; instance++)
        {
            colors[instance][0] = random() % 255;
            colors[instance][1] = random() % 255;
            colors[instance][2] = random() % 255;
            colors[instance][3] = 0;
        }
        
        glGenBuffers(1, &colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferData(GL_ARRAY_BUFFER, NUM_INSTANCES * 4, colors, GL_STATIC_DRAW);
    }
    
    // Allocate storage to store MVP per instance
    {
        int instance;
        
        // Random angle for each instance, compute the MVP later
        for (instance = 0; instance < NUM_INSTANCES; instance++)
        {
            angle[instance] = (float) (random() % 32768) / 32767.0f * 360.0f;
        }
        
        glGenBuffers(1, &mvpVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mvpVBO);
        glBufferData(GL_ARRAY_BUFFER, NUM_INSTANCES * sizeof(Matrix), NULL, GL_DYNAMIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void InstancingEngine::onViewWillAppear() {
    
}

void InstancingEngine::onViewWillDisAppear() {
    
}

void InstancingEngine::onDestroy() {
    // Delete program object
    glDeleteProgram(InstancingGLES::program);
    
    glDeleteBuffers(1, &positionVBO);
    glDeleteBuffers(1, &colorVBO);
    glDeleteBuffers(1, &mvpVBO);
    glDeleteBuffers(1, &indicesIBO);
}

void InstancingEngine::onChanged(int width, int height) {
    InstancingEngine::width = width;
    InstancingEngine::height = height;
    
    glViewport(0, 0, width, height);
}

void InstancingEngine::onUpdate(float deltaTime) {

    Matrix *matrixBuf;
    Matrix perspective;
    float aspect;
    int instance = 0;
    int numRows;
    int numColumns;


    // Compute the window aspect ratio
    aspect = (GLfloat) width / (GLfloat) height;

    // Generate a perspective matrix with a 60 degree FOV
    matrixLoadIdentity(&perspective);
    matrixPerspective(&perspective, 60.0f, aspect, 1.0f, 20.0f);

    glBindBuffer(GL_ARRAY_BUFFER, mvpVBO);
    matrixBuf = (Matrix *) glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(Matrix) * NUM_INSTANCES, GL_MAP_WRITE_BIT);

    // Compute a per-instance MVP that translates and rotates each instance differnetly
    numRows = (int) sqrtf(NUM_INSTANCES);
    numColumns = numRows;

    for (instance = 0; instance < NUM_INSTANCES; instance++)
    {
        Matrix modelview;
        float translateX = ((float) (instance % numRows) / (float) numRows) * 2.0f - 1.0f;
        float translateY = ((float) (instance / numColumns) / (float) numColumns) * 2.0f - 1.0f;

        // Generate a model view matrix to rotate/translate the cube
        matrixLoadIdentity(&modelview);

        // Per-instance translation
        matrixTranslate(&modelview, translateX, translateY, -2.0f);

        // Compute a rotation angle based on time to rotate the cube
        angle[instance] += (deltaTime * 40.0f);

        if (angle[instance] >= 360.0f)
        {
            angle[instance] -= 360.0f;
        }

        // Rotate the cube
        matrixRotate(&modelview, angle[instance], 1.0, 0.0, 1.0);

        // Compute the final MVP by multiplying the
        // modevleiw and perspective matrices together
        matrixMultiply(&matrixBuf[instance], &modelview, &perspective);
    }

    glUnmapBuffer ( GL_ARRAY_BUFFER );
}

void InstancingEngine::onDraw() {
    
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use the program object
    glUseProgram (InstancingGLES::program );
    
    // Load the vertex position
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *) NULL);
    glEnableVertexAttribArray(POSITION_LOC);
    
    // Load the instance color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glVertexAttribPointer(COLOR_LOC, 4, GL_UNSIGNED_BYTE, GL_TRUE, 4 * sizeof(GLubyte), (const void *) NULL);
    glEnableVertexAttribArray(COLOR_LOC);
    glVertexAttribDivisor(COLOR_LOC, 1); // One color per instance
    
    
    // Load the instance MVP buffer
    glBindBuffer(GL_ARRAY_BUFFER, mvpVBO);
    
    // Load each matrix row of the MVP.  Each row gets an increasing attribute location.
    glVertexAttribPointer(MVP_LOC + 0, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix), (const void *) NULL);
    glVertexAttribPointer(MVP_LOC + 1, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix), (const void *) (sizeof(GLfloat) * 4 ));
    glVertexAttribPointer(MVP_LOC + 2, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix), (const void *) (sizeof (GLfloat) * 8));
    glVertexAttribPointer(MVP_LOC + 3, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix), (const void *) (sizeof(GLfloat) * 12));
    glEnableVertexAttribArray(MVP_LOC + 0);
    glEnableVertexAttribArray(MVP_LOC + 1);
    glEnableVertexAttribArray(MVP_LOC + 2);
    glEnableVertexAttribArray(MVP_LOC + 3);
    
    // One MVP per instance
    glVertexAttribDivisor(MVP_LOC + 0, 1);
    glVertexAttribDivisor(MVP_LOC + 1, 1);
    glVertexAttribDivisor(MVP_LOC + 2, 1);
    glVertexAttribDivisor(MVP_LOC + 3, 1);
    
    // Bind the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesIBO);
    
    // Draw the cubes
    glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (const void *) NULL, NUM_INSTANCES);
}

void InstancingEngine::onTouch(int eventsCount, int **touchInfo) {
    for (int i = 0; i < eventsCount; i++) {
        delete []touchInfo[i];
    }
    delete []touchInfo;
}

bool InstancingEngine::onBackButtonPressed() {
    return true;
}
