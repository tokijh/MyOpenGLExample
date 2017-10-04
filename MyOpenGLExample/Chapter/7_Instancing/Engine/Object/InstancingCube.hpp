//
//  InstancingCube.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 4..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef InstancingCube_hpp
#define InstancingCube_hpp

#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

class InstancingCube {
public:
    
    //
    /// \brief Generates geometry for a sphere.  Allocates memory for the vertex data and stores
    ///        the results in the arrays.  Generate index list for a TRIANGLE_STRIP
    /// \param numSlices The number of slices in the sphere
    /// \param vertices If not NULL, will contain array of float3 positions
    /// \param normals If not NULL, will contain array of float3 normals
    /// \param texCoords If not NULL, will contain array of float2 texCoords
    /// \param indices If not NULL, will contain the array of indices for the triangle strip
    /// \return The number of indices required for rendering the buffers (the number of indices stored in the indices array
    ///         if it is not NULL ) as a GL_TRIANGLE_STRIP
    //
    int static genSphere(int numSlices, float radius, GLfloat **vertices, GLfloat **normals, GLfloat **texCoords, GLuint **indices);
    
    //
    /// \brief Generates geometry for a cube.  Allocates memory for the vertex data and stores
    ///        the results in the arrays.  Generate index list for a TRIANGLES
    /// \param scale The size of the cube, use 1.0 for a unit cube.
    /// \param vertices If not NULL, will contain array of float3 positions
    /// \param normals If not NULL, will contain array of float3 normals
    /// \param texCoords If not NULL, will contain array of float2 texCoords
    /// \param indices If not NULL, will contain the array of indices for the triangle strip
    /// \return The number of indices required for rendering the buffers (the number of indices stored in the indices array
    ///         if it is not NULL ) as a GL_TRIANGLE_STRIP
    //
    int static genCube(float scale, GLfloat **vertices, GLfloat **normals, GLfloat **texCoords, GLuint **indices);
    
    //
    /// \brief Generates a square grid consisting of triangles.  Allocates memory for the vertex data and stores
    ///        the results in the arrays.  Generate index list as TRIANGLES.
    /// \param size create a grid of size by size (number of triangles = (size-1)*(size-1)*2)
    /// \param vertices If not NULL, will contain array of float3 positions
    /// \param indices If not NULL, will contain the array of indices for the triangle strip
    /// \return The number of indices required for rendering the buffers (the number of indices stored in the indices array
    ///         if it is not NULL ) as a GL_TRIANGLES
    //
    int static genSquareGrid(int size, GLfloat **vertices, GLuint **indices);
};

#endif /* InstancingCube_hpp */
