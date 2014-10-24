//
//  line.cpp
//  metaheuristic
//
//  Created by ixi on 24/10/14.
//
//

#include "line.h"

Line::Line(GLuint shader_program, std::vector<int>& loc)
    : Model(shader_program)
{
    vertice_pos_ =
    {
        loc[0] / 5 * -4.5f + 9.0f, loc[0] % 5 * -4.5f + 9.0f, 0.0f,
        loc[1] / 5 * -4.5f + 9.0f, loc[1] % 5 * -4.5f + 9.0f, 0.0f,
    };

    color_ =
    {
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
    };

    normal_ =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
    };

    init_();
}

void Line::render(glm::mat4& mvp)
{
    Model::render(mvp);
    glDrawArrays(GL_LINES, 0, 2);
}
