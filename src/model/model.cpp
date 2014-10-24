//
//  model.cpp
//  metaheuristic
//
//  Created by ixi on 24/10/14.
//
//

#include "model.h"


Model::Model(GLuint shader_program)
    : shader_program_(shader_program)
{

}

void Model::init_(float ambient_light[4])
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);

    // Allocate space and upload the data from CPU to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 3 * vertice_pos_.size() * sizeof(GLfloat),
                 NULL,
                 GL_STATIC_DRAW);

    // Transfer the vertex positions, colors and normals
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    vertice_pos_.size() * sizeof(GLfloat),
                    vertice_pos_.data());

    glBufferSubData(GL_ARRAY_BUFFER,
                    vertice_pos_.size() * sizeof(GLfloat),
                    vertice_pos_.size() * sizeof(GLfloat),
                    color_.data());

    glBufferSubData(GL_ARRAY_BUFFER,
                    2 * vertice_pos_.size() * sizeof(GLfloat),
                    vertice_pos_.size() * sizeof(GLfloat),
                    normal_.data());

    if (vertice_pos_.size() > 0)
    {
        glGenBuffers(1, &eab_);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indice_.size() * sizeof(GLuint),
                     indice_.data(),
                     GL_STATIC_DRAW);
    }

    // Enable position attribute
    GLint position_att = glGetAttribLocation(shader_program_,
                                             "position");
    glVertexAttribPointer(position_att, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_att);

    GLint color_att = glGetAttribLocation(shader_program_, "color");
    glVertexAttribPointer(color_att, 3, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid *) (vertice_pos_.size() * sizeof(GLfloat)));
    glEnableVertexAttribArray(color_att);

    GLint normal_att = glGetAttribLocation(shader_program_, "normal");
    glVertexAttribPointer(normal_att, 3, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid *) (2 * vertice_pos_.size()
                                      * sizeof(GLfloat)));
    glEnableVertexAttribArray(normal_att);

    mvp_uniform_ = glGetUniformLocation(shader_program_, "MVP");

    GLint ambien_unif = glGetUniformLocation(shader_program_, "ambient_light");
    glProgramUniform4fv(shader_program_, ambien_unif, 1, ambient_light);
}

void Model::render(glm::mat4& mvp)
{
    glBindVertexArray(vao_);
    glUniformMatrix4fv(mvp_uniform_, 1, GL_FALSE, glm::value_ptr(mvp));
}