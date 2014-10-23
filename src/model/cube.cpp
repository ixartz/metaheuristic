//
//  cube.cpp
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#include "cube.h"

Cube::Cube(GLuint shader_program)
    : Model(shader_program, 24, 36)
{
    vertice_pos_ = new GLfloat[vert_size_]
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

    color_ = new GLfloat[vert_size_]
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

    normal_ = new GLfloat[vert_size_]
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

    indice_ = new GLuint[ind_size_]
    {
        0, 1, 2, 2, 3, 0,
        3, 2, 6, 6, 7, 3,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 5, 6, 6, 2, 1
    };

    init_();
}

Cube::~Cube()
{
    delete [] vertice_pos_;
    delete [] color_;
    delete [] normal_;
    delete [] indice_;
}

void Cube::render(glm::mat4& mvp)
{
    Model::render(mvp);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
