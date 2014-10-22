#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    glfwWindowHint(GLFW_SAMPLES, 4);

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

    GLfloat vertices_position[24] =
    {
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f
    };

    GLuint indices[36] =
    {
        0, 1, 2, 2, 3, 0,
        3, 2, 6, 6, 7, 3,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 5, 6, 6, 2, 1
    };

    GLfloat colors[24] =
    {
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 0.4, 0.4,
        0.0, 0.4, 0.4,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 0.4, 0.4,
        0.0, 0.4, 0.4
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Allocate space and upload the data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position) + sizeof(colors), NULL, GL_STATIC_DRAW);

    // Transfer the vertex positions:
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_position), vertices_position);
    // Transfer the vertex colors:
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices_position), sizeof(colors), colors);

    GLuint eab;
    glGenBuffers(1, &eab);
    // Transfer the data from indices to eab
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint shaderProgram = create_program("/Users/ixi/Projects/metaheuristic/src/shaders/vert.shader", "/Users/ixi/Projects/metaheuristic/src/shaders/frag.shader");

    // Get the location of the attributes that enters in the vertex shader
    GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
    // Specify how the data for position can be accessed
    glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // Enable the attribute
    glEnableVertexAttribArray(position_attribute);

    GLint color_attribute = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices_position));
    glEnableVertexAttribArray(color_attribute);

    GLint mvp = glGetUniformLocation(shaderProgram, "MVP");

    // LINE
    GLuint line_vao;

    glGenVertexArrays(1, &line_vao);
    glBindVertexArray(line_vao);

    GLfloat lines_vertices_position[6] =
    {
        0.0f, 0.0f, 0.0f,
        8.0f, 0.0f, 0.0f,
    };

    GLfloat lines_colors[6] =
    {
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
    };

    GLuint line_vbo;
    glGenBuffers(1, &line_vbo);

    // Allocate space and upload the data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, line_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lines_vertices_position) + sizeof(lines_colors), NULL, GL_STATIC_DRAW);

    // Transfer the vertex positions:
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lines_vertices_position), lines_vertices_position);
    // Transfer the vertex colors:
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(lines_vertices_position), sizeof(lines_colors), lines_colors);

    // Get the location of the attributes that enters in the vertex shader
    GLint line_position_attribute = glGetAttribLocation(shaderProgram, "position");
    // Specify how the data for position can be accessed
    glVertexAttribPointer(line_position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // Enable the attribute
    glEnableVertexAttribArray(line_position_attribute);

    GLint line_color_attribute = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(line_color_attribute, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(lines_vertices_position));
    glEnableVertexAttribArray(line_color_attribute);

    GLint line_mvp = glGetUniformLocation(shaderProgram, "MVP");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glBindVertexArray(line_vao);
        glm::mat4 Projection;
        // Set the projection matrix
        // glm::ortho(-10.0f, 10.0f, 10.0f, -10.0f, 0.1f, 100.f)
        Projection = glm::perspective(30.f, 500.f / 500.f, 0.1f, 1000.f);

        glm::mat4 View = glm::lookAt(glm::vec3(0, 0, -40.0f), // Camera is at (4,3,3), in World Space
                                     glm::vec3(0, 0, 0), // and looks at the origin
                                     glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
                                     );

        glm::mat4 Model = glm::mat4(1.0f);

        glm::mat4 MVP = Projection * View * Model;
        glUniformMatrix4fv(line_mvp, 1, GL_FALSE, glm::value_ptr(MVP));
        glDrawArrays(GL_LINES, 0, 2);

        glBindVertexArray(vao);
        for (int i = 0; i < 2; ++i)
        {
            glm::mat4 Projection;
            // Set the projection matrix
            // glm::ortho(-10.0f, 10.0f, 10.0f, -10.0f, 0.1f, 100.f)
            Projection = glm::perspective(30.f, 500.f / 500.f, 0.1f, 1000.f);

            glm::mat4 View = glm::lookAt(glm::vec3(0, 0, -40.0f), // Camera is at (4,3,3), in World Space
                                         glm::vec3(0, 0, 0), // and looks at the origin
                                         glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
                                         );

            glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(i * 10, 0, +10.0f));

            glm::mat4 MVP = Projection * View * Model;

            glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(MVP));

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
