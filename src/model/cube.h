//
//  cube.h
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#ifndef __metaheuristic__cube__
#define __metaheuristic__cube__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../model/shader-loader.h"

class Cube
{
public:
    /// Constructor.
    Cube(GLuint shader_program);

    /**
     * \brief Render the model.
     */
    void render(glm::mat4& mvp);

private:
    GLuint shader_program_;

    GLuint vao_;
    GLuint vbo_;
    GLuint eab_;

    GLint mvp_uniform_;

    GLfloat vertice_pos_[24] =
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

    GLfloat color_[24] =
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

    GLfloat normal_[24] =
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

    GLuint indice_[36] =
    {
        0, 1, 2, 2, 3, 0,
        3, 2, 6, 6, 7, 3,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 5, 6, 6, 2, 1
    };
};

#endif /* defined(__metaheuristic__cube__) */
