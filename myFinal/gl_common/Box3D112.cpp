//Geethanjali Jeevanatham, Anupa Prudhivi, Sindhusha Dhulipala, Arko Basu
#include "Box3D112.h"




GLBox3D112::GLBox3D112()
{
      _program = 0;

}


GLBox3D112::~GLBox3D112()
{
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(1, _vaoID);
    glDeleteProgram(_program);

}




/*!
 Init the geometry object
 */
void GLBox3D112::init(void)
{
    
    _num_vertices = 0;
    
    initShader();
    initVBO();
    


}


/*!
 Draw the objects
 */
void GLBox3D112::draw(void)
{
    
    //////////////////////////////////////////////////
    // Renders the sphere
    
    // Enable the shader program
    glUseProgram(_program);
    
    // this changes the camera location
    glm::mat4 rotated_view =  rotatedViewMatrix();
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
    glUniformMatrix4fv(_inverseViewMatrixLocation, 1, GL_FALSE, &invRotatedViewMatrix()[0][0]);
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); //
    
    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(_vaoID[0]);
    
   // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // allows to see the primitives
    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
    glDrawArrays(GL_TRIANGLE_STRIP, 8, 8);
    glDrawArrays(GL_TRIANGLE_STRIP, 16, 8);
    glDrawArrays(GL_TRIANGLES, 24, 24);
   // glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
   // glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
    
    // Unbind our Vertex Array Object
    glBindVertexArray(0);
    
    // Unbind the shader program
    glUseProgram(0);
    
    
}



/*
 Inits the shader program for this object
 */
void GLBox3D112::initShader(void)
{
    
    if(!_apperance.exists())return;
    
    // This loads the shader program from a file
    _program = _apperance.getProgram();
    

    glUseProgram(_program);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Vertex information / names
    
    glBindAttribLocation(_program, 0, "in_Position");
    glBindAttribLocation(_program, 1, "in_Normal");
    glBindAttribLocation(_program, 2, "in_TexCoord");
    
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Define the model view matrix.
    _modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    addModelViewMatrixToProgram(_program);
    
 

    glUseProgram(0);

}


/*!
 Create the vertex buffer object for this element
 */
void GLBox3D112::initVBO(void)
{
    
    
    _vertex_points.clear();
    _normal_vectors.clear();
    
    //---------------------------------------------------------
    // This creates the box geometry
    make_box(_vertex_points, _normal_vectors);
    
    _num_vertices = _vertex_points.size();
    
    
    // create memory for the vertices, etc.
    float* vertices = new float[_num_vertices * 5];
    float* normals = new float[_num_vertices * 3];
    
    
    // copy the data to the vectors
    for(int i=0; i<_vertex_points.size() ; i++)
    {
        Vertex v = _vertex_points[i];
        vertices[(i*5)] = v.x(); vertices[(i*5)+1] = v.y(); vertices[(i*5)+2] = v.z();
        vertices[(i*5)+3] = v.u(); vertices[(i*5)+4] = v.v();
        
        Vertex n = _normal_vectors[i];
        normals[(i*3)] = n.x(); normals[(i*3)+1] = n.y(); normals[(i*3)+2] = n.z();

    }
    
    glUseProgram(_program);
    
    
    glGenVertexArrays(1, _vaoID); // Create our Vertex Array Object
    glBindVertexArray(_vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(3, _vboID); // Generate our Vertex Buffer Object
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, _num_vertices * 5 * sizeof(GLfloat), &vertices[0], GL_DYNAMIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    
    int locPos = glGetAttribLocation(_program, "in_Position");
    glVertexAttribPointer((GLuint)locPos, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(locPos); //
    
    
    int tex_idx = glGetAttribLocation(_program, "in_TexCoord");
    glEnableVertexAttribArray(tex_idx);
    glVertexAttribPointer((GLuint)tex_idx, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat),
                          (const GLvoid*)(3 * sizeof(GLfloat)));
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, _vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, _num_vertices * 3 *  sizeof(GLfloat), normals, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    int locNorm = glGetAttribLocation(_program, "in_Normal");
    glEnableVertexAttribArray(locNorm); //
    glVertexAttribPointer((GLuint)locNorm, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    // delete the memory
    delete vertices;
    delete normals;
}




/*!
 Creates the points and the normal vectors for this box
 */
void GLBox3D112::make_box(vector<Vertex>& vp, vector<Vertex>& nv )
{
    // TODO: add a better vertex generation code, one which incorporates the number of rows and colums.
    
    // allocate the memory.
    vp = vector<Vertex>(50);
    nv = vector<Vertex>(50);
    
    //--------------------------------------------------------
    // xy-plane, positive z direction
    vp[0].x() = -30.0;
    vp[0].y() = 360.0;
    vp[0].z() = -30.0;
    vp[0].u() = 0.0;
    vp[0].v() = 0.0;
    
    vp[1].x() = -30.0;
    vp[1].y() = 360.0;
    vp[1].z() = 30.0;
    vp[1].u() = 0.0;
    vp[1].v() = 1.0;
    
    vp[2].x() = -25.0;
    vp[2].y() = 365.0;
    vp[2].z() = -25.0;
    vp[2].u() = 1.0;
    vp[2].v() = 0.0;
    
    vp[3].x() = -25.0;
    vp[3].y() = 365.0;
    vp[3].z() = 25.0;
    vp[3].u() = 1.0;
    vp[3].v() = 1.0;

    for (int i=0; i<4; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = 0.0;
        nv[i].z() = 1.0;
    }

    
    //--------------------------------------------------------
    // xy-plane, negative z direction
    vp[4].x() = 25.0;
    vp[4].y() = 365.0;
    vp[4].z() = -25.0;
    vp[4].u() = 0.0;
    vp[4].v() = 0.0;
    
    vp[5].x() = 25.0;
    vp[5].y() = 365.0;
    vp[5].z() = 25.0;
    vp[5].u() = 0.0;
    vp[5].v() = 1.0;
    
    vp[6].x() = 30.0;
    vp[6].y() = 360.0;
    vp[6].z() = -30.0;
    vp[6].u() = 1.0;
    vp[6].v() = 0.0;
    
    vp[7].x() = 30.0;
    vp[7].y() = 360.0;
    vp[7].z() = 30.0;
    vp[7].u() = 1.0;
    vp[7].v() = 1.0;
    
    for (int i=4; i<8; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = 0.0;
        nv[i].z() = -1.0;
    }
    
    //--------------------------------------------------------
    // yz-plane, positive x direction
    
    //--------------------------------------------------------
    // xy-plane, negative z direction
    vp[8].x() = -5.0;
    vp[8].y() = 365.0;
    vp[8].z() = 5.0;
    vp[8].u() = 0.0;
    vp[8].v() = 0.0;
    
    vp[9].x() = -5.0;
    vp[9].y() = 385.0;
    vp[9].z() = 5.0;
    vp[9].u() = 0.0;
    vp[9].v() = 1.0;
    
    vp[10].x() = -5.0;
    vp[10].y() = 365.0;
    vp[10].z() = 5.0;
    vp[10].u() = 1.0;
    vp[10].v() = 0.0;
    
    vp[11].x() = 5.0;
    vp[11].y() = 385.0;
    vp[11].z() = 5.0;
    vp[11].u() = 1.0;
    vp[11].v() = 1.0;
    
    for (int i=8; i<12; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = 0.0;
        nv[i].z() = -1.0;
    }
    
    //--------------------------------------------------------
    // yz-plane, positive x direction
    
    //--------------------------------------------------------
    // xy-plane, negative z direction
    vp[12].x() = 5.0;
    vp[12].y() = 365.0;
    vp[12].z() = -5.0;
    vp[12].u() = 0.0;
    vp[12].v() = 0.0;
    
    vp[13].x() = 5.0;
    vp[13].y() = 385.0;
    vp[13].z() = -5.0;
    vp[13].u() = 0.0;
    vp[13].v() = 1.0;
    
    vp[14].x() = -5.0;
    vp[14].y() = 365.0;
    vp[14].z() = -5.0;
    vp[14].u() = 1.0;
    vp[14].v() = 0.0;
    
    vp[15].x() = -5.0;
    vp[15].y() = 385.0;
    vp[15].z() = -5.0;
    vp[15].u() = 1.0;
    vp[15].v() = 1.0;
    
    for (int i=12; i<16; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = 0.0;
        nv[i].z() = -1.0;
    }
    
    //--------------------------------------------------------
    // yz-plane, positive x direction
    
    //--------------------------------------------------------
    // xy-plane, negative z direction
    vp[16].x() = -45.0;
    vp[16].y() = 410.0;
    vp[16].z() = -45.0;
    vp[16].u() = 0.0;
    vp[16].v() = 0.0;
    
    vp[17].x() = -45.0;
    vp[17].y() = 410.0;
    vp[17].z() = 45.0;
    vp[17].u() = 0.0;
    vp[17].v() = 1.0;
    
    vp[18].x() = -35.0;
    vp[18].y() = 385.0;
    vp[18].z() = -35.0;
    vp[18].u() = 1.0;
    vp[18].v() = 0.0;
    
    vp[19].x() = -35.0;
    vp[19].y() = 385.0;
    vp[19].z() = 35.0;
    vp[19].u() = 1.0;
    vp[19].v() = 1.0;
    
    for (int i=16; i<20; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = -1.0;
        nv[i].z() = 0.0;
    }
    
    //--------------------------------------------------------
    // yz-plane, positive x direction
    
    // xy-plane, negative z direction
    vp[20].x() = 35.0;
    vp[20].y() = 385.0;
    vp[20].z() = -35.0;
    vp[20].u() = 0.0;
    vp[20].v() = 0.0;
    
    vp[21].x() = 35.0;
    vp[21].y() = 385.0;
    vp[21].z() = 35.0;
    vp[21].u() = 0.0;
    vp[21].v() = 1.0;
    
    vp[22].x() = 45.0;
    vp[22].y() = 410.0;
    vp[22].z() = -45.0;
    vp[22].u() = 1.0;
    vp[22].v() = 0.0;
    
    vp[23].x() = 45.0;
    vp[23].y() = 410.0;
    vp[23].z() = 45.0;
    vp[23].u() = 1.0;
    vp[23].v() = 1.0;
    
    for (int i=20; i<24; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = 0.0;
        nv[i].z() = 1.0;
    }

    // xy-plane, negative z direction
    vp[24].x() = -30.0;
    vp[24].y() = 360.0;
    vp[24].z() = -30.0;
    vp[24].u() = 0.0;
    vp[24].v() = 0.0;
    
    vp[25].x() = 30.0;
    vp[25].y() = 360.0;
    vp[25].z() = -30.0;
    vp[25].u() = 0.0;
    vp[25].v() = 1.0;
    
    vp[26].x() = -25.0;
    vp[26].y() = 365.0;
    vp[26].z() = -25.0;
    vp[26].u() = 1.0;
    vp[26].v() = 0.0;
    
    vp[27].x() = 30.0;
    vp[27].y() = 360.0;
    vp[27].z() = -30.0;
    vp[27].u() = 1.0;
    vp[27].v() = 1.0;
    
    for (int i=24; i<28; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = -1.0;
        nv[i].z() = 0.0;
    }
    
    
    // xy-plane, negative z direction
    vp[28].x() = -25.0;
    vp[28].y() = 365.0;
    vp[28].z() = -25.0;
    vp[28].u() = 0.0;
    vp[28].v() = 0.0;
    
    vp[29].x() = 25.0;
    vp[29].y() = 365.0;
    vp[29].z() = -25.0;
    vp[29].u() = 0.0;
    vp[29].v() = 1.0;
    
    vp[30].x() = -30.0;
    vp[30].y() = 360.0;
    vp[30].z() = 30.0;
    vp[30].u() = 1.0;
    vp[30].v() = 0.0;
    
    vp[31].x() = 30.0;
    vp[31].y() = 360.0;
    vp[31].z() = 30.0;
    vp[31].u() = 1.0;
    vp[31].v() = 1.0;
    
    vp[32].x() = -25.0;
    vp[32].y() = 365.0;
    vp[32].z() = 25.0;
    vp[32].u() = 0.0;
    vp[32].v() = 0.0;
    
    for (int i=28; i<33; i++) {
        nv[i].x() = 1.0;
        nv[i].y() = 0.0;
        nv[i].z() = 0.0;
    }
    
    vp[33].x() = 30.0;
    vp[33].y() = 360.0;
    vp[33].z() = 30.0;
    vp[33].u() = 0.0;
    vp[33].v() = 1.0;
    
    vp[34].x() = -25.0;
    vp[34].y() = 365.0;
    vp[34].z() = 25.0;
    vp[34].u() = 1.0;
    vp[34].v() = 0.0;
    
    vp[35].x() = 25.0;
    vp[35].y() = 365.0;
    vp[35].z() = 25.0;
    vp[35].u() = 1.0;
    vp[35].v() = 1.0;
    
    vp[36].x() = -45.0;
    vp[36].y() = 410.0;
    vp[36].z() = -45.0;
    vp[36].u() = 0.0;
    vp[36].v() = 0.0;
    
    for (int i=33; i<37; i++) {
        nv[i].x() = -1.0;
        nv[i].y() = 0.0;
        nv[i].z() = 0.0;
    }
    
    vp[37].x() = 45.0;
    vp[37].y() = 410.0;
    vp[37].z() = -45.0;
    vp[37].u() = 0.0;
    vp[37].v() = 1.0;
    
    vp[38].x() = -35.0;
    vp[38].y() = 385.0;
    vp[38].z() = -35.0;
    vp[38].u() = 1.0;
    vp[38].v() = 0.0;
    
    vp[39].x() = 45.0;
    vp[39].y() = 410.0;
    vp[39].z() = -45.0;
    vp[39].u() = 1.0;
    vp[39].v() = 1.0;
    
    vp[40].x() = -35.0;
    vp[40].y() = 385.0;
    vp[40].z() = -35.0;
    vp[40].u() = 0.0;
    vp[40].v() = 0.0;
    
    for (int i=37; i<41; i++) {
        nv[i].x() = -1.0;
        nv[i].y() = 0.0;
        nv[i].z() = 0.0;
    }
    
    vp[41].x() = 35.0;
    vp[41].y() = 385.0;
    vp[41].z() = -35.0;
    vp[41].u() = 0.0;
    vp[41].v() = 1.0;
    
    vp[42].x() = -45.0;
    vp[42].y() = 410.0;
    vp[42].z() = 45.0;
    vp[42].u() = 1.0;
    vp[42].v() = 0.0;
    
    vp[43].x() = 45.0;
    vp[43].y() = 410.0;
    vp[43].z() = 45.0;
    vp[43].u() = 1.0;
    vp[43].v() = 1.0;
    
    vp[44].x() = -35.0;
    vp[44].y() = 385.0;
    vp[44].z() = 35.0;
    vp[44].u() = 0.0;
    vp[44].v() = 0.0;
    
    for (int i=41; i<45; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = 0.0;
        nv[i].z() = -1.0;
    }
    
    vp[45].x() = 45.0;
    vp[45].y() = 410.0;
    vp[45].z() = 45.0;
    vp[45].u() = 0.0;
    vp[45].v() = 1.0;
    
    vp[46].x() = -35.0;
    vp[46].y() = 385.0;
    vp[46].z() = 35.0;
    vp[46].u() = 1.0;
    vp[46].v() = 0.0;
    
    vp[47].x() = 35.0;
    vp[47].y() = 385.0;
    vp[47].z() = 35.0;
    vp[47].u() = 1.0;
    vp[47].v() = 1.0;

    
    for (int i=45; i<48; i++) {
        nv[i].x() = 0.0;
        nv[i].y() = 0.0;
        nv[i].z() = 1.0;
    }
    

}





























