//
//  Renderer.hpp
//  PongGL
//
//  Created by David Paris on 08/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Sprite.hpp"
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class RenderQueue
{
private:
    static const u_int32_t MAX_BUFFER = 1024;
    
private:
    float verticies[MAX_BUFFER];
    int elements[MAX_BUFFER];
    
    u_int32_t vertexCount_{0};
    u_int32_t elementCount_{0};
    u_int32_t queueCount_{0};
    
    float screenWidth_;
    float screenHeight_;
    
    
public:
    RenderQueue(float screenWidth, float screenHeight) : screenWidth_(screenWidth), screenHeight_(screenHeight) {}
    ~RenderQueue() {}
    
    void addToQueue(Sprite* sprite, float x, float y);
    void clearQueue();
    
    float* getVertices()
    {
        return verticies;
    }
    
    int* getElements()
    {
        return elements;
    }
    
    u_int32_t getVertexCount()
    {
        return vertexCount_;
    }
    
    u_int32_t getElementCount()
    {
        return elementCount_;
    }
    
};



class Renderer
{
private:
    static const GLuint BUFFER_COUNT = 1;
private:
    RenderQueue* queue_;
    
    /** Buffers **/
    GLuint vao; //vertex array object
    GLuint vbo[BUFFER_COUNT]; //double vertex buffer object
    GLuint ebo[BUFFER_COUNT]; //double element buffer object
    
    /** Shaders **/
    GLuint shaderProgram_;
    GLuint vertexShader_;
    GLuint fragmentShader_;
    
    /** counter to keep track of the buffer we are rendering to **/
    GLuint currentBufferCount{0};
    
    /** Private init functions **/
    //void initBuffers();
    //void initShaders();
    
public:
    
    Renderer(RenderQueue* queue) : queue_{queue}
    {};
    
    ~Renderer();
    
    void init();
    
    void render();
};


#endif /* Renderer_hpp */
