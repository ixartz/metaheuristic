//
//  ShaderLoader.cpp
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#include "shader-loader.h"

std::string ShaderLoader::load_file_(std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);

    if (in.is_open())
    {
        std::string src{std::istreambuf_iterator<char>(in),
                        std::istreambuf_iterator<char>()};

        return src;
    }
    else
    {
        std::cerr << "Unable to open " << filename << "!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

GLuint ShaderLoader::compile_shader_(std::string& filename,
                                     GLenum shaderType)
{
    std::string buffer = load_file_(filename);
    const char* src = buffer.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint lenght;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &lenght);

    if (!lenght)
    {
        std::cerr << "Shader compilation failed with this message:"
                  << std::endl;

        std::string log(lenght, ' ');
        glGetShaderInfoLog(shader, log.size(), NULL, &log[0]);
        std::cerr << &log[0] << std::endl;

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return shader;
}

GLuint ShaderLoader::create(std::string& vert_path, std::string& frag_path)
{
    GLuint shader_program = glCreateProgram();

    GLuint vertex_shader = compile_shader_(vert_path, GL_VERTEX_SHADER);
    GLuint fragment_shader = compile_shader_(frag_path, GL_FRAGMENT_SHADER);

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    return shader_program;
}
