//
//  Renderer.hpp
//  PongGL
//
//  OpenGL Renderer
//
//  Created by David Paris on 08/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "Graphics.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>


/**
 Renderer is able to render a Graphics frame to screen using OpenGL.
 
 Features:
 - Entities to be drawn are added to a queue as Drawables which are read by the render engine (potential to support multiple threads).
 - Render engine reads the queue on each render call.
 - Render engine renders entities via a single drawElements call to the GPU using OpenGL.
 - Uses trivial implementation of vertex and fragment shaders in GLSL.
 **/
class Renderer
{
public:
    Renderer() {};
    ~Renderer();
    
    /** initialise the renderer **/
    void init(GraphicsPipe* frame, GLfloat screenWidth, GLfloat screenHeight);
    
    /** render what is in the queue (and clear it) **/
    void render();

private:
    static const GLuint MAX_BUFFER_SIZE = 1024;
    
    /** What we want to render this frame **/
    GraphicsPipe* frame_;
    
    /** Screen Size **/
    GLfloat screenWidth_;
    GLfloat screenHeight_;
    
    /** Buffer Objects **/
    GLuint vao; //vertex array object
    GLuint vbo; //vertex buffer object
    GLuint ebo; //element buffer object
    
    /** Buffers **/
    GLfloat vertexBuffer_[MAX_BUFFER_SIZE];
    GLuint elementBuffer_[MAX_BUFFER_SIZE];
    
    /** Counts **/
    GLuint vertexCount_{0}; //number of verticies we added to vertex buffer (includes colours)
    GLuint elementCount_{0}; //number of elements we added to element buffer
    GLuint frameVertexCount_{0}; //number of triangle verticies we have read from the frame
    
    /** Shaders **/
    GLuint shaderProgram_;
    GLuint vertexShader_;
    GLuint fragmentShader_;

    /** init methods **/
    void initBuffers();
    void initShaders();
    
    /** add the current frame to the buffers for rendering **/
    void addFrameToBuffers();
};


#endif /* Renderer_hpp */
