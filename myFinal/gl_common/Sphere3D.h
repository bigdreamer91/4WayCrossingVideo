//Geethanjali Jeevanatham, Anupa Prudhivi, Sindhusha Dhulipala, Arko Basu
//
#pragma once


// stl include
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGL/gl.h>

// locals
#include "GLObject.h"
#include "GLSphere1.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"





class GLSphere3D : public GLSphere1
{
public:
    
    GLSphere3D(float center_x, float center_y, float center_z, float radius, int rows = 10, int segments = 10 );
    ~GLSphere3D();
    

    /*!
     Init the geometry object
     */
    void init(void);
    
protected:
    
    
    
    /*
     Inits the shader program for this object
     */
    virtual void initShader(void);
    



};