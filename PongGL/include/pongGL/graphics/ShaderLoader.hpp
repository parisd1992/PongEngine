//
//  ShaderLoader.hpp
//  PongGL
//
//  Created by David Paris on 01/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef ShaderLoader_hpp
#define ShaderLoader_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <GL/glew.h>

using namespace std;

/**
 Class responsible for loading OpenGL Shaders.
 **/
class ShaderLoader
{
public:
    
    /*Loads a shader from file and returns its ID.
     Please remember to delete the shader using the ID once it is no longer needed*/
    GLuint loadShaderFromFile(std::string path, GLenum shaderType);
};

#endif /* ShaderLoader_hpp */
