//
//  Renderer.hpp
//  PongGL
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

class Renderer
{
private:
    static const GLuint MAX_BUFFER_SIZE = 1024;

private:
    /** What we want to render this frame **/
    Graphics* frame_;
    
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
    
public:
    
    Renderer(Graphics* frame, GLfloat screenWidth, GLfloat screenHeight) : frame_{frame}, screenWidth_{screenWidth}, screenHeight_{screenHeight}
    {};
    
    ~Renderer();
    
    /** initialise the renderer **/
    void init();
    
    /** render what is in the queue (and clear it) **/
    void render();
};


#endif /* Renderer_hpp */
