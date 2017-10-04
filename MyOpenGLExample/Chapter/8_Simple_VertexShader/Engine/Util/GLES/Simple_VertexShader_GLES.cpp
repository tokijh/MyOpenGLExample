//
//  Simple_VertexShader_GLES.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "Simple_VertexShader_GLES.hpp"

string Simple_VertexShader_GLES::VERTEX_SHADER_NAME = "Simple_VertexShader.vs";
string Simple_VertexShader_GLES::FRAGMENT_SHADER_NAME = "Simple_VertexShader.fs";

GLuint Simple_VertexShader_GLES::program = 0;

// Uniform locations
GLint Simple_VertexShader_GLES::mvpLoc;

// Vertex daata
GLfloat * Simple_VertexShader_GLES::vertices;
GLuint * Simple_VertexShader_GLES::indices;
int Simple_VertexShader_GLES::numIndices;

// Rotation angle
GLfloat Simple_VertexShader_GLES::angle;

// MVP matrix
Simple_VertexShader_Matrix Simple_VertexShader_GLES::mvpMatrix;

void Simple_VertexShader_GLES::makeProgram() {
    int vertexShader = loadShader(GL_VERTEX_SHADER, DataManager::getInstance().get(Simple_VertexShader_GLES::VERTEX_SHADER_NAME).c_str());
    int fragmentShader = loadShader(GL_FRAGMENT_SHADER, DataManager::getInstance().get(Simple_VertexShader_GLES::FRAGMENT_SHADER_NAME).c_str());
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    // Delete Shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // Use created program
    glUseProgram(program);
}

GLuint Simple_VertexShader_GLES::loadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}
