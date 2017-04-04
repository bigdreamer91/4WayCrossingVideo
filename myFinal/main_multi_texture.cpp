//Team members Anupa Prudhvi, Geethanjali Jeevanatham, Arko Basu, Sindhusha Dhulipala



// stl include
#include <iostream>
#include <string>

// GLEW include


// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <GL/glew.h>

// glfw includes
#include <GLFW/glfw3.h>

#include <OpenGL/gl.h>
// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Plane3D.h"
#include "Texture.h"
#include "Box3D.h"
#include "Sphere3D.h"
#include "GLObjectObj.h"
#include "GLSphere.h"




using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;


// this is a helper variable to allow us to change the texture blend model
extern int g_change_texture_blend;


int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);
    
    
    // create an apperance object.
    GLAppearance* apperance_0 = new GLAppearance("../../data/shaders/texture_filter.vs", "../../data/shaders/texture_filter.fs");
    
    GLAppearance* apperance_1 = new GLAppearance("../../data/shaders/noise_map.vs", "../../data/shaders/noise_map.fs");
    
    GLAppearance* apperance_2 = new GLAppearance("../../data/shaders/displacement_texture.vs", "../../data/shaders/displacement_texture.fs");
    
    GLAppearance* apperance_3 = new GLAppearance("../../data/shaders/spherical_mapping.vs", "../../data/shaders/spherical_mapping.fs");
    
    GLAppearance* apperance_4 = new GLAppearance("../../data/shaders/multi_texture.vs", "../../data/shaders/multi_texture.fs");
    
    GLAppearance* apperance_7 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
    
    GLAppearance* apperance_5 = new GLAppearance("../../data/shaders/displacement_texture1.vs", "../../data/shaders/displacement_texture1.fs");
    
    GLAppearance* apperance_6 = new GLAppearance("../../data/shaders/spherical_mapping1.vs", "../../data/shaders/spherical_mapping1.fs");
    
    GLAppearance* apperance_8 = new GLAppearance("../../data/shaders/displacement_texture.vs", "../../data/shaders/displacement_texture.fs");
    
    GLAppearance* apperance_9 = new GLAppearance("../../data/shaders/single_texture.vs", "../../data/shaders/single_texture.fs");
    
    GLAppearance* apperance_10 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
    
    GLDirectLightSource  light_sourceload;
    light_sourceload._lightPos = glm::vec4(20.0,20.0,0.0, 0.0);
    light_sourceload._ambient_intensity = 0.2;
    light_sourceload._specular_intensity = 5.5;
    light_sourceload._diffuse_intensity = 2.0;
    light_sourceload._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_10->addLightSource(light_sourceload);
    
    // Create a material object
    GLMaterial material_load;
    material_load._diffuse_material = glm::vec3(1.0, 0.0, 0.2);
    material_load._ambient_material = glm::vec3(1.0, 0.0, 0.2);
    material_load._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material_load._shininess = 12.0;
    material_load._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_10->setMaterial(material_load);
    apperance_10->finalize();

    
    
    GLDirectLightSource  light_source;
    light_source._lightPos = glm::vec4(600.0, 600.0, 600.0, 0.0);
    light_source._ambient_intensity = 0.2;
    light_source._specular_intensity = 4.5;
    light_source._diffuse_intensity = 1.0;
    light_source._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_0->addLightSource(light_source);
    apperance_3->addLightSource(light_source);
    apperance_5->addLightSource(light_source);
    apperance_6->addLightSource(light_source);
    
    GLSpotLightSource spotlight_source;
    spotlight_source._lightPos = glm::vec4(0.0, 100.0, 50.0, 1.0);
    spotlight_source._ambient_intensity = 0.2;
    spotlight_source._specular_intensity = 30.5;
    spotlight_source._diffuse_intensity = 8.0;
    spotlight_source._attenuation_coeff = 0.0002;
    spotlight_source._cone_direction = glm::vec3(-1.0, -1.0, -1.0);
    spotlight_source._cone_angle = 60.0;
    
    apperance_0->addLightSource(spotlight_source);
    apperance_3->addLightSource(spotlight_source);
    apperance_5->addLightSource(spotlight_source);
    apperance_6->addLightSource(light_source);
    
    
    
    GLDirectLightSource  light_source_1;
    light_source_1._lightPos = glm::vec4(-1500.0, 1000.0, 0.0, 0.0);
    light_source_1._ambient_intensity = 0.2;
    light_source_1._specular_intensity = 50.5;
    light_source_1._diffuse_intensity = 500.0;
    light_source_1._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_1->addLightSource(light_source_1);
    apperance_7->addLightSource(light_source_1);
    apperance_8->addLightSource(light_source_1);
    apperance_9->addLightSource(light_source_1);
    
    GLSpotLightSource spotlight_source_1;
    spotlight_source_1._lightPos = glm::vec4(-2250.0, 800.0, 1100.0, 1.0);
    spotlight_source_1._ambient_intensity = 0.8;
    spotlight_source_1._specular_intensity = 10.0;
    spotlight_source_1._diffuse_intensity = 1000.0;
    spotlight_source_1._attenuation_coeff = 0.0002;
    spotlight_source_1._cone_direction = glm::vec3(-1.0, -1.0, -1.0);
    spotlight_source_1._cone_angle = 180.0;
    
    apperance_1->addLightSource(spotlight_source_1);
    apperance_7->addLightSource(spotlight_source_1);
    apperance_8->addLightSource(spotlight_source_1);
    apperance_9->addLightSource(spotlight_source_1);
    
    // Create a material object
    GLMaterial material_1;
    material_1._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
    material_1._ambient_material = glm::vec3(0.0, 0.0, 1.0);
    material_1._specular_material = glm::vec3(0.0, 0.0, 1.0);
    material_1._shininess = 12.0;
    material_1._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_1->setMaterial(material_1);
    apperance_7->setMaterial(material_1);
    apperance_8->setMaterial(material_1);
    apperance_9->setMaterial(material_1);
    
    GLSpotLightSource spotlight_source_2;
    spotlight_source_2._lightPos = glm::vec4(-1750.0, 1200.0, -400.0, 1.0);
    spotlight_source_2._ambient_intensity = 0.2;
    spotlight_source_2._specular_intensity = 10.0;
    spotlight_source_2._diffuse_intensity = 1000.0;
    spotlight_source_2._attenuation_coeff = 0.0002;
    spotlight_source_2._cone_direction = glm::vec3(-1.0, -1.0, -1.0);
    spotlight_source_2._cone_angle = 180.0;
    
    apperance_8->addLightSource(spotlight_source_2);
    
    // Create a material object
    GLMaterial material_2;
    material_2._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
    material_2._ambient_material = glm::vec3(0.0, 1.0, 0.0);
    material_2._specular_material = glm::vec3(0.0, 1.0, 0.0);
    material_2._shininess = 12.0;
    material_2._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_8->setMaterial(material_2);
    
    
    
    // Create a material object
    GLMaterial material_0;
    material_0._diffuse_material = glm::vec3(0.8, 0.8, 0.0);
    material_0._ambient_material = glm::vec3(0.8, 0.8, 0.0);
    material_0._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material_0._shininess = 12.0;
    material_0._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_0->setMaterial(material_0);
    apperance_3->setMaterial(material_0);
    apperance_5->setMaterial(material_0);
    apperance_6->setMaterial(material_0);
    
    
    
    
    //************************************************************************************************
    // Add a texture
    // Add a texture
    GLTexture* texture = new GLTexture();
    int texid = texture->loadAndCreateTexture("../../data/textures1/textured-paper.bmp");
    GLTexture* tex11 = texture;
    apperance_0->setTexture(texture);
    //apperance_0->finalize();
    
    GLTexture* texture1 = new GLTexture();
    int texid1 = texture1->loadAndCreateTexture("../../data/textures1/old_wood_floor_v1_512x512.bmp");
    GLTexture* tex22 = texture1;
    
    
    GLTexture* texture2 = new GLTexture();
    int texid2 = texture2->loadAndCreateTexture("../../data/textures1/wooden-door-with-sandblasted-glass.bmp");
    GLTexture* tex33 = texture2;
    apperance_0->setTexture(texture2);
    
    
    GLTexture* texture3 = new GLTexture();
    int texid3 = texture3->loadAndCreateTexture("../../data/textures1/stone_texture.bmp");
    GLTexture* tex4 = texture3;
    apperance_0->setTexture(texture3);
    
    // Add a texture for displacement mapping
    GLMultiTexture* texture_multi1 = new GLMultiTexture();
    int texid_multi1 = texture_multi1->loadAndCreateTextures("../../data/textures1/textured-paper.bmp", "../../data/textures1/textured-paper.bmp");
    // apperance_1->setTexture(texture_multi1);
    
    // Add a texture for bump mapping
    GLMultiTexture* texture_bump = new GLMultiTexture();
    int texid_bump = texture_bump->loadAndCreateTextures("../../data/textures1/Stone_wall_texture_sketchup_warehouse_type071.bmp", "../../data/maps/texture_brick_NRM.bmp");
    // apperance_2->setTexture(texture_bump);
    
    // Add a texture for bump mapping
    // Add a texture for Environmental mapping
    GLTexture* texture_disp = new GLTexture();
    int texid_disp = texture_disp->loadAndCreateTexture("../../data/textures1/plain_plaster_texture_02_by_goodtextures-d2y1pz6.bmp");
    
    // Add a texture for Environmental mapping
    GLTexture* texture_env = new GLTexture();
    int texid_env = texture_env->loadAndCreateTexture("../../data/textures1/leonid-afremov-paintings-2.bmp");
    //apperance_3->setTexture(texture_env);
    
    // Add a texture for displacement mapping
    GLMultiTexture* texture_multi2 = new GLMultiTexture();
    int texid_multi2 = texture_multi2->loadAndCreateTextures("../../data/textures1/textured-paper.bmp", "../../data/textures1/fresko2_NRM.bmp");
    // apperance_4->setTexture(texture_multi2);
    
    
    
    GLTexture* texturea2 = new GLTexture();
    int texida2 = texturea2->loadAndCreateTexture("../../data/textures1/tekstura-fon-metallik.bmp");
    
    GLTexture* texturea3 = new GLTexture();
    int texida3 = texturea3->loadAndCreateTexture("../../data/textures1/wood_texture_2_by_annfrost_stock.bmp");
    
    GLTexture* texturea4 = new GLTexture();
    int texida4 = texturea4->loadAndCreateTexture("../../data/textures1/wall_paiting_2.bmp");
    
    GLTexture* texturea5 = new GLTexture();
    int texida5 = texturea5->loadAndCreateTexture("../../data/textures1/wall_paiting_1.bmp");
    
    GLTexture* texturea6 = new GLTexture();
    int texida6 = texturea6->loadAndCreateTexture("../../data/textures1/textured-paper.bmp");
    
    GLTexture* texturea7 = new GLTexture();
    int texida7 = texturea7->loadAndCreateTexture("../../data/textures1/194_1orange_peel.bmp");
    
    GLTexture* texturea8 = new GLTexture();
    int texida8 = texturea8->loadAndCreateTexture("../../data/textures1/tileable-basket-weave-textures-1-2.bmp");
    
    glm::vec3 A = glm::vec3(55.0, 130.0, 100.0);
    glm::vec3 B = glm::vec3(70.0, 130.0, 100.0);
    glm::vec3 C = glm::vec3(130.0, 130.0, 100.0);
    glm::vec3 D = glm::vec3(145.0, 130.0, 100.0);
    glm::vec3 E = glm::vec3(117.0, 70.0, 100.0);
    glm::vec3 F = glm::vec3(117.0, 30.0, 100.0);
    glm::vec3 G = glm::vec3(83.0, 30.0, 100.0);
    glm::vec3 H = glm::vec3(83.0, 70.0, 100.0);
    glm::vec3 I = glm::vec3(55.0, 100.0, 100.0);
    glm::vec3 J = glm::vec3(145.0, 100.0, 100.0);
    glm::vec3 K = glm::vec3(100.0, 145.0, 100.0);
    glm::vec3 L = glm::vec3(100.0, 130.0, 100.0);
    glm::vec3 M = glm::vec3(100.0, 100.0, 100.0);
    glm::vec3 N = glm::vec3(100.0, 70.0, 100.0);
    
    
    
    
    //model_matrix7 = translation7 * translation17;
    
    // create the sphere geometry
    
    
    
    
    
    // If you want to change appearance parameters after you init the object, call the update function
    apperance_0->updateLightSources();
    apperance_1->updateLightSources();
    
    
    // enable the program
    glUseProgram(apperance_8->getProgram());
    int location = glGetUniformLocation(apperance_8->getProgram(), "texture_delta");
    glUniform1f(location, 0.00f);
    glUniform1f(glGetUniformLocation(apperance_8->getProgram(), "bump_mode"), 0);
    
    
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector.
    SetViewAsLookAt(glm::vec3(0.0f, 200.0f, 2400.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Blending
    
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // sphere->enableNormalVectorRenderer();
    
   // glfwSetKeyCallback(window, keyboard_callback);
    
    time(0);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
      double lastTime = glfwGetTime();
     long nbFrames = 0;
     long vbFrames = 0;
     int choice = 0;
     float rot = 0.0;
     double currentTime;
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while (!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR, 0, clear_color);
        glClearBufferfv(GL_DEPTH, 0, clear_depth);
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());
       // glfwSetKeyCallback(window, keyboard_callback);
        // draw the objects
        
        cs->draw();
        
        // change the texture appearance blend mode
        bool ret = texture->setTextureBlendMode(g_change_texture_blend);
        if (ret)apperance_0->updateTextures();
        
        
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;
    
    
}

