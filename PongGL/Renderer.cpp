//
//  Renderer.cpp
//  PongGL
//
//  Created by David Paris on 08/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "ShaderLoader.hpp"
#include "Renderer.hpp"

void RenderQueue::addToQueue(Sprite *sprite, float x, float y)
{
    //1. generate our points
    unsigned int w = sprite->getWidth();
    unsigned int h = sprite->getHeight();
    float r = sprite->getRed();
    float g = sprite->getGreen();
    float b = sprite->getBlue();
    
    float left = (w * -1.0f)/2;
    float right = w/2;
    float top = h/2;
    float bottom = (h * -1.0f)/2;
    
    //2. create our model, view, projection
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::ortho(screenWidth_/2, -screenWidth_/2, -screenHeight_/2, screenHeight_/2, -0.1f, 1.0f);
    glm::mat4 mvp = projection * view * model;
    
    glm::vec4 topLeftPoint = mvp * glm::vec4(left, top, 0.0f, 1.0f );
    glm::vec4 topRightPoint = mvp * glm::vec4(right, top, 0.0f, 1.0f);
    glm::vec4 bottomLeftPoint = mvp * glm::vec4(left, bottom, 0.0f, 1.0f);
    glm::vec4 bottomRightPoint = mvp * glm::vec4(right, bottom, 0.0f, 1.0f);
    
    //3. add to the vertex buffer
    
    //p1
    verticies[vertexCount_++] = topLeftPoint.x;
    verticies[vertexCount_++] = topLeftPoint.y;
    verticies[vertexCount_++] = r;
    verticies[vertexCount_++] = g;
    verticies[vertexCount_++] = b;
    
    //p2
    verticies[vertexCount_++] = topRightPoint.x;
    verticies[vertexCount_++] = topRightPoint.y;
    verticies[vertexCount_++] = r;
    verticies[vertexCount_++] = g;
    verticies[vertexCount_++] = b;
    
    //p3
    verticies[vertexCount_++] = bottomRightPoint.x;
    verticies[vertexCount_++] = bottomRightPoint.y;
    verticies[vertexCount_++] = r;
    verticies[vertexCount_++] = g;
    verticies[vertexCount_++] = b;
    
    //p4
    verticies[vertexCount_++] = bottomLeftPoint.x;
    verticies[vertexCount_++] = bottomLeftPoint.y;
    verticies[vertexCount_++] = r;
    verticies[vertexCount_++] = g;
    verticies[vertexCount_++] = b;
    
    //4. add to the element buffer - points added as (for 1st sprite): 0, 1, 2, 2, 3, 0
    elements[elementCount_++] = 0 + queueCount_*4;
    elements[elementCount_++] = 1 + queueCount_*4;
    elements[elementCount_++] = 2 + queueCount_*4;
    elements[elementCount_++] = 2 + queueCount_*4;
    elements[elementCount_++] = 3 + queueCount_*4;
    elements[elementCount_++] = 0 + queueCount_*4;
    
    //increase the queue count now that we have finished adding to the queue
    queueCount_ += 1;
};


void RenderQueue::clearQueue()
{
    vertexCount_ = 0;
    elementCount_ = 0;
    queueCount_ = 0;
}

void Renderer::init()
{
    glewExperimental = GL_TRUE;
    glewInit();
    
    /***************
     * Set up buffers
     ***************/
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //vertex buffer
    glGenBuffers(BUFFER_COUNT, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[currentBufferCount]); //make vbo the active buffer
    
    //element buffers
    glGenBuffers(BUFFER_COUNT, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[currentBufferCount]); //make ebo the active buffer
    
    /***************
     * Set up Shaders
     ***************/
    
    //load shaders
    ShaderLoader shaderLoader;
    vertexShader_ = shaderLoader.loadShaderFromFile("/Users/davidparis/Documents/C++/PongGL/Shaders/vertex_shader.glsl",
                                                    GL_VERTEX_SHADER);
    fragmentShader_ = shaderLoader.loadShaderFromFile("/Users/davidparis/Documents/C++/PongGL/Shaders/fragment_shader.glsl",
                                                      GL_FRAGMENT_SHADER);
    
    //create a shader program
    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader_);
    glAttachShader(shaderProgram_, fragmentShader_);
    
    //specify which frag output goes to which buffer
    glBindFragDataLocation(shaderProgram_, 0, "outColor");
    
    //link and use the shader programs
    glLinkProgram(shaderProgram_);
    glUseProgram(shaderProgram_);
    
    GLint posAttrib = glGetAttribLocation(shaderProgram_, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    
    GLint colAttrib = glGetAttribLocation(shaderProgram_, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    
    glBindVertexArray(0);
}

void Renderer::render()
{
    glBindVertexArray(vao);
    
    //stream the data to the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[currentBufferCount]); //make vbo the active array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(queue_->getVertices())*queue_->getVertexCount(),queue_->getVertices(), GL_STREAM_DRAW); //send the vertices to the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[currentBufferCount]); //make ebo the active array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(queue_->getElements())*queue_->getElementCount(), queue_->getElements(), GL_STREAM_DRAW); //send the elements to the buffer

    //draw
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawElements(GL_TRIANGLES, queue_->getElementCount(), GL_UNSIGNED_INT, 0);

    //update the buffer count and reset the queue
    currentBufferCount = ++currentBufferCount % BUFFER_COUNT;
    queue_->clearQueue();
}

Renderer::~Renderer()
{
    glDeleteProgram(shaderProgram_);
    glDeleteShader(fragmentShader_);
    glDeleteShader(vertexShader_);
    
    glDeleteBuffers(BUFFER_COUNT, vbo);
    glDeleteBuffers(BUFFER_COUNT, ebo);
    glDeleteVertexArrays(1, &vao);
}



