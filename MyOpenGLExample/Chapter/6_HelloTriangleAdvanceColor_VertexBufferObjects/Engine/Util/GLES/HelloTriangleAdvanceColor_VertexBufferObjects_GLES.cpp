//
//  HelloTriangleAdvanceColor_VertexBufferObjects_GLES.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "HelloTriangleAdvanceColor_VertexBufferObjects_GLES.hpp"

string HelloTriangleAdvanceColor_VertexBufferObjects_GLES::VERTEX_SHADER_NAME = "HelloTriangleAdvanceColor_VertexBufferObjects.vs";
string HelloTriangleAdvanceColor_VertexBufferObjects_GLES::FRAGMENT_SHADER_NAME = "HelloTriangleAdvanceColor_VertexBufferObjects.fs";

GLuint HelloTriangleAdvanceColor_VertexBufferObjects_GLES::program = 0;

void HelloTriangleAdvanceColor_VertexBufferObjects_GLES::makeProgram() {
    int vertexShader = loadShader(GL_VERTEX_SHADER, DataManager::getInstance().get(HelloTriangleAdvanceColor_VertexBufferObjects_GLES::VERTEX_SHADER_NAME).c_str());
    int fragmentShader = loadShader(GL_FRAGMENT_SHADER, DataManager::getInstance().get(HelloTriangleAdvanceColor_VertexBufferObjects_GLES::FRAGMENT_SHADER_NAME).c_str());
    
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

GLuint HelloTriangleAdvanceColor_VertexBufferObjects_GLES::loadShader(GLenum shaderType, const char *pSource) {
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
