#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "io/window.h"
#include "io/keyboard.h"

// Read a shader source from a file
// store the shader source in a std::vector<char>
void read_shader_src(const char *fname, std::vector<char> &buffer) {
    std::ifstream in;
    in.open(fname, std::ios::binary);
    if(in.is_open()) {
        // Get the number of bytes stored in this file
        in.seekg(0, std::ios::end);
        size_t length = (size_t)in.tellg();
        // Go to start of the file
        in.seekg(0, std::ios::beg);
        // Read the content of the file in a buffer
        buffer.resize(length + 1);
        in.read(&buffer[0], length);
        in.close();
        // Add a valid C - string end
        buffer[length] = '\0';
    }
    else {
        std::cerr << "Unable to open " << fname << " I'm out!" << std::endl;
        exit(-1);
    }
}
// Compile a shader
GLuint load_and_compile_shader(const char *fname, GLenum shaderType) {
    // Load a shader from an external file
    std::vector<char> buffer;
    read_shader_src(fname, buffer);
    const char *src = &buffer[0];
    // Compile the shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    // Check the result of the compilation
    GLint test;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
    if(!test) {
        std::cerr << "Shader compilation failed with this message:" << std::endl;
        std::vector<char> compilation_log(512);
        glGetShaderInfoLog(shader, compilation_log.size(), NULL, &compilation_log[0]);
        std::cerr << &compilation_log[0] << std::endl;
        glfwTerminate();
        exit(-1);
    }
    return shader;
}
// Create a program from two shaders
GLuint create_program(const char *path_vert_shader, const char *path_frag_shader) {
    // Load and compile the vertex and fragment shaders
    GLuint vertexShader = load_and_compile_shader(path_vert_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = load_and_compile_shader(path_frag_shader, GL_FRAGMENT_SHADER);
    // Attach the above shader to a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Flag the shaders for deletion
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // Link and use the program
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    return shaderProgram;
}

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    window = glfwCreateWindow(500, 500, "Metaheuristic", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to open a window!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, Keyboard::key_callback);
    glfwSetWindowSizeCallback(window, Window::window_resized);

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    std::cout << "OpenGL - " << major << "."
              << minor << "." << rev << std::endl;

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat vertices_position[8] =
    {
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5,
    };

    GLuint indices[6] =
    {
        0, 1, 2,
        2, 3, 0
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Allocate space and upload the data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);

    GLuint eab;
    glGenBuffers(1, &eab);
    // Transfer the data from indices to eab
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint shaderProgram = create_program("/Users/ixi/Projects/metaheuristic/src/shaders/vert.shader", "/Users/ixi/Projects/metaheuristic/src/shaders/frag.shader");

    // Get the location of the attributes that enters in the vertex shader
    GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
    // Specify how the data for position can be accessed
    glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // Enable the attribute
    glEnableVertexAttribArray(position_attribute);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
