//
//  ShaderLoader.cpp
//  PongGL
//
//  Created by David Paris on 01/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "ShaderLoader.hpp"

//From: http://lazyfoo.net/tutorials/OpenGL/30_loading_text_file_shaders/index.php
//Also see: https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php
GLuint ShaderLoader::loadShaderFromFile(std::string path, GLenum shaderType)
{
    //Open file
    GLuint shaderID = 0;
    std::string shaderString;
    std::ifstream sourceFile(path.c_str());
    
    //Source file loaded
    if(sourceFile)
    {
        //Get shader source
        shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
        //Create shader ID
        shaderID = glCreateShader(shaderType);
        
        //Set shader source
        const GLchar* shaderSource = shaderString.c_str();
        glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);
        
        //Compile shader source
        glCompileShader(shaderID);
        
        //Check shader for errors
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if(shaderCompiled != GL_TRUE)
        {
            printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
            glDeleteShader(shaderID);
            shaderID = 0;
        }
    }
    else
    {
        printf( "Unable to open file %s\n", path.c_str() );
    }
    
    return shaderID;
}


