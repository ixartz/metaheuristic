//
//  cube.cpp
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#include "cube.h"

Cube::Cube(GLuint shader_program)
    : Model(shader_program)
{
    vertice_pos_ =
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

    color_ =
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

    normal_ =
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

    indice_ =
    {
        0, 1, 2, 2, 3, 0,
        3, 2, 6, 6, 7, 3,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 5, 6, 6, 2, 1
    };

    float ambient_light[4] = { 0.3, 0.3, 0.3, 1.0 };
    init_(ambient_light);
}

void Cube::render(glm::mat4& mvp)
{
    Model::render(mvp);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
