//
//  cube.cpp
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#include "cube.h"

Cube::Cube(GLuint shader_program)
    : shader_program_(shader_program)
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);

    // Allocate space and upload the data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertice_pos_) + sizeof(color_) + sizeof(normal_),
                 NULL,
                 GL_STATIC_DRAW);

    // Transfer the vertex positions, colors and normals
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    sizeof(vertice_pos_),
                    vertice_pos_);

    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(vertice_pos_),
                    sizeof(color_),
                    color_);

    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(vertice_pos_) + sizeof(color_),
                    sizeof(normal_),
                    normal_);

    glGenBuffers(1, &eab_);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(indice_),
                 indice_,
                 GL_STATIC_DRAW);

    // Enable position attribute
    GLint position_att = glGetAttribLocation(shader_program_,
                                             "position");
    glVertexAttribPointer(position_att, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_att);

    GLint color_att = glGetAttribLocation(shader_program_, "color");
    glVertexAttribPointer(color_att, 3, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid *) sizeof(vertice_pos_));
    glEnableVertexAttribArray(color_att);

    GLint normal_att = glGetAttribLocation(shader_program_, "normal");
    glVertexAttribPointer(normal_att, 3, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid *) (sizeof(vertice_pos_) + sizeof(color_)));
    glEnableVertexAttribArray(normal_att);

    mvp_uniform_ = glGetUniformLocation(shader_program_, "MVP");
}

void Cube::render(glm::mat4& mvp)
{
    glBindVertexArray(vao_);
    glUniformMatrix4fv(mvp_uniform_, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}