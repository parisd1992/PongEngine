//
//  Renderer.cpp
//  PongGL
//
//  Created by David Paris on 08/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "ShaderLoader.hpp"
#include "Renderer.hpp"


void Renderer::initBuffers()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //vertex buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //make vbo the active buffer
    
    //element buffers
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); //make ebo the active buffer
}

void Renderer::initShaders()
{
    //load shaders
    ShaderLoader shaderLoader;
    
    //TODO: file locations are hardcoded!
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
}


void Renderer::init()
{
    glewExperimental = GL_TRUE;
    glewInit();
    
    initBuffers();
    initShaders();
    
    //the vertex buffer stores floats as an array of: [ x, y, r, g, b ]
    GLint posAttrib = glGetAttribLocation(shaderProgram_, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    
    GLint colAttrib = glGetAttribLocation(shaderProgram_, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    
    glBindVertexArray(0);
}

void Renderer::addFrameToBuffers()
{
    std::vector<Drawable> currentFrame = frame_->getCurrentFrame();
    
    for(auto frameIter = currentFrame.begin(); frameIter != currentFrame.end(); ++frameIter)
    {
        auto verticies = frameIter->verticies_;
        auto elementIndicies = frameIter->verticeIndexes_;
        
        //Add our element indices to the element buffer
        for(auto elementIter = elementIndicies.begin(); elementIter != elementIndicies.end(); ++elementIter)
        {
            //We do this before adding our verticies because when we add to element buffer,
            //we need to shift indexes by the number of verticies we have rendered in the frame up until this point.
            elementBuffer_[elementCount_++] = *elementIter + frameVertexCount_;
        }
        
        //Add our vertice data in object coordinates to the vertex buffer in screen coordinates
        for(auto verticeIter = verticies.begin(); verticeIter != verticies.end(); ++verticeIter)
        {
            //Create our model, view, projection
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(frameIter->position_.x_, frameIter->position_.y_, 0.0f));
            glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 projection = glm::ortho(screenWidth_/2, -screenWidth_/2, -screenHeight_/2, screenHeight_/2, -0.1f, 1.0f);
            glm::mat4 mvp = projection * view * model;
            
            //Create our translated point in screen coordinates
            glm::vec4 point = mvp * glm::vec4(verticeIter->x_, verticeIter->y_, 0.0f, 1.0f );
            
            //Add to the vertex buffer
            vertexBuffer_[vertexCount_++] = point.x;
            vertexBuffer_[vertexCount_++] = point.y;
            vertexBuffer_[vertexCount_++] = frameIter->colour_.red_;
            vertexBuffer_[vertexCount_++] = frameIter->colour_.green_;
            vertexBuffer_[vertexCount_++] = frameIter->colour_.blue_;
            
            frameVertexCount_ += 1;
        }
    }
    
    //now that the frame is added we can clear it
    frame_->clearCurrentFrame();
}

void Renderer::render()
{
    //add the frame to the buffers
    addFrameToBuffers();
    
    glBindVertexArray(vao);
    
    //stream the data to the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //make vbo the active array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer_), vertexBuffer_, GL_STREAM_DRAW); //send the vertices to the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); //make ebo the active array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementBuffer_), elementBuffer_, GL_STREAM_DRAW); //send the elements to the buffer

    //draw
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawElements(GL_TRIANGLES, elementCount_, GL_UNSIGNED_INT, 0);

    //reset the counts
    vertexCount_ = 0;
    elementCount_ = 0;
    frameVertexCount_ = 0;
}

Renderer::~Renderer()
{
    glDeleteProgram(shaderProgram_);
    glDeleteShader(fragmentShader_);
    glDeleteShader(vertexShader_);
    
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}



