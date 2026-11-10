#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"
#include "gl_perspective_camera.h"

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {
        exit (-1);
    }
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    // float aspectRatio = 1.0; // 16.0 / 9.0; // winWidth / (float)winHeight;
    // int winHeight = winWidth / aspectRatio;

    int winWidth = 1000;
    int winHeight = 1000;

    GLperspectiveCamera camera(
    glm::vec3(0.0f, 0.0f, 10.0f), // position
    glm::vec3(0.0f, 0.0f, -1.0f), // looking toward -Z
    50.0,                         // focal length
    36.0,                         // image-plane width
    winWidth,                     // Width
    winHeight,                    // Height
    5.0f,                         // near plane
    -5.0f                        // far plane
);
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    // Need to set a projection matrix that fits the aspect ratio set
    // by the window frame.
    //
    // The ortho parameters, in order: left, right, bottom, top, zNear, zFar


    // float halfWidth = 15.0 / 2.0;
    // float halfHeight = halfWidth / aspectRatio;

    // float left = -halfWidth;
    // float right = halfWidth;

    // float bottom = -halfHeight;
    // float top = halfHeight;

    // float near = 5.0f;
    // float far = -5.0f;


    // glm::mat4 M_ortho  = glm::ortho(left, right, bottom, top, near, far);

    glm::mat4 M_ortho = camera.getProjectionMatrix();
    
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            std::cout << M_ortho[column][row] << (column == 3 ? '\n' : ' ');
        }
    }

    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
    

    // create a Vertex Array Buffer to hold our triangle data    
    GLuint m_triangleVBO[1];                             
    glGenBuffers(1, m_triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    // this is the actual triangle data that will be copied to                                              
    // the GPU memory                                                                                       
    std::vector<float> host_VertexBuffer{
        -3.0f, -3.0f, 0.0f, 1.0f, 0.0f, 0.0f, // V0: red
         3.0f, -3.0f, 0.0f, 0.0f, 1.0f, 1.0f, // V1: green
         0.0f,  3.0f, 0.0f, 0.5f, 0.0f, 1.0f  // V2: blue
    };

    int numBytes = host_VertexBuffer.size() * sizeof(float);

    // copy the numBytes from host_VertexBuffer t the GPU and store in                                      
    // the currently bound VBO                                                                              
    glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // once copied, we no longer need the data on the host                                                  
    host_VertexBuffer.clear();


    GLuint m_VAO;
    // create a vertex array object that will map the attributes in                                         
    // our vertex buffer to different location attributes for our                                           
    // shaders                                                                                              
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // The vertex buffer stores a position followed by a color for each vertex.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glBindVertexArray(0);


    // Create a shader using my GLSLObject class                                                            
    sivelab::GLSLObject shader;
    // shader.addShader( "../OpenGl/Shader/vertexShader_passthrough.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    // shader.addShader( "../OpenGl/Shader/fragmentShader_passthrough.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    shader.addShader("../OpenGL/Shader/vertexShader_withMatrixTransformation.glsl",sivelab::GLSLObject::VERTEX_SHADER);
    shader.addShader("../OpenGL/Shader/fragmentShader_passthrough.glsl",sivelab::GLSLObject::FRAGMENT_SHADER);

    shader.createProgram();

    GLuint projMatrixID, viewMatrixID;
    projMatrixID = shader.createUniform("projMatrix");
    viewMatrixID = shader.createUniform( "viewMatrix" );
        
    // Camera pos
    // glm::vec3 m_pos(0,0,0), m_viewDir(0,0,-1);
    // glm::vec3 m_U(1,0,0), m_V(0,1,0), m_W(0,0,1);

    // double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glm::mat4 M_view  = glm::lookAt( m_pos, m_pos - m_W, m_V );
        glm::mat4 M_view = camera.getViewMatrix();

        /* Render your objects here */
        shader.activate();
        
        // For plain Triangle
        // glBindVertexArray(m_VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);
        
        glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr( M_ortho  ));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr( M_view  ));

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        shader.deactivate();
        // Swap the front and back buffers
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        float moveRatePerFrame = 0.05;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.moveForward(moveRatePerFrame);
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.moveBackward(moveRatePerFrame);
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.moveLeft(moveRatePerFrame);
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.moveRight(moveRatePerFrame);
        }

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0 / timeDiff << std::endl;
        }   

        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
  
    glfwTerminate();
    return 0;
}
