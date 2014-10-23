//
//  model.cpp
//  metaheuristic
//
//  Created by ixi on 24/10/14.
//
//

#include "model.h"


Model::Model(GLuint shader_program, int vert_size, int ind_size)
    : shader_program_(shader_program)
    , vert_size_(vert_size)
    , ind_size_(ind_size)
{

}

void Model::init_()
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);

    // Allocate space and upload the data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 3 * vert_size_ * sizeof(GLfloat),
                 NULL,
                 GL_STATIC_DRAW);

    // Transfer the vertex positions, colors and normals
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    vert_size_ * sizeof(GLfloat),
                    vertice_pos_);

    glBufferSubData(GL_ARRAY_BUFFER,
                    vert_size_ * sizeof(GLfloat),
                    vert_size_ * sizeof(GLfloat),
                    color_);

    glBufferSubData(GL_ARRAY_BUFFER,
                    2 * vert_size_ * sizeof(GLfloat),
                    vert_size_ * sizeof(GLfloat),
                    normal_);

    if (ind_size_ > 0)
    {
        glGenBuffers(1, &eab_);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     ind_size_ * sizeof(GLuint),
                     indice_,
                     GL_STATIC_DRAW);
    }

    // Enable position attribute
    GLint position_att = glGetAttribLocation(shader_program_,
                                             "position");
    glVertexAttribPointer(position_att, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_att);

    GLint color_att = glGetAttribLocation(shader_program_, "color");
    glVertexAttribPointer(color_att, 3, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid *) (vert_size_ * sizeof(GLfloat)));
    glEnableVertexAttribArray(color_att);

    GLint normal_att = glGetAttribLocation(shader_program_, "normal");
    glVertexAttribPointer(normal_att, 3, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid *) (2 * vert_size_ * sizeof(GLfloat)));
    glEnableVertexAttribArray(normal_att);

    mvp_uniform_ = glGetUniformLocation(shader_program_, "MVP");
}

void Model::render(glm::mat4& mvp)
{
    glBindVertexArray(vao_);
    glUniformMatrix4fv(mvp_uniform_, 1, GL_FALSE, glm::value_ptr(mvp));
}