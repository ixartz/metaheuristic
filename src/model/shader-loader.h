//
//  ShaderLoader.h
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#ifndef __metaheuristic__shader_loader__
#define __metaheuristic__shader_loader__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <fstream>

class ShaderLoader
{
public:
    static GLuint create(std::string& vert_path, std::string& frag_path);

private:
    static std::string load_file_(std::string& filename);
    static GLuint compile_shader_(std::string& filename,
                                  GLenum shaderType);
};

#endif /* defined(__metaheuristic__shader_loader__) */
