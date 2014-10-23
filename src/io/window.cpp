//
//  window.cpp
//  metaheuristic
//
//  Created by ixi on 19/10/14.
//
//

#include "window.h"

Window::Window()
{
    check_glfw();
    create_hint();

    window_ = glfwCreateWindow(500, 500, "Metaheuristic", NULL, NULL);

    if (!window_)
    {
        std::cout << "Failed to open a window!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);

    create_callback();
    print_version();

    check_glew();

    std::string vert_path = std::string(PROJECT_SRC_DIR)
                            + "/src/shaders/vert.shader";

    std::string frag_path = std::string(PROJECT_SRC_DIR)
                            + "/src/shaders/frag.shader";
    shader_program_ = ShaderLoader::create(vert_path, frag_path);
}

Window::~Window()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Window::create_hint()
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

void Window::create_callback()
{
    glfwSetKeyCallback(window_, Keyboard::key_callback);
    glfwSetWindowSizeCallback(window_, Window::window_resized);
}

void Window::check_glfw()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Window::check_glew()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void Window::print_version()
{
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);

    std::cout << "OpenGL - " << major << "."
              << minor << "." << rev << std::endl;
}

void Window::execute()
{
    glm::mat4 projection = glm::perspective(30.f, 500.f / 500.f, 0.1f, 1000.f);

    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -40.0f),
                                 glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));

    glm::mat4 vp = projection * view;
    glm::mat4 mvp;

    glm::mat4 model;
    Cube c(shader_program_);

    while (!glfwWindowShouldClose(window_))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 5.0f));
        mvp = vp * model;
        c.render(mvp);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Window::window_resized(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}
