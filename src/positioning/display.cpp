//
//  display.cpp
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#include "display.h"

Display::Display(GLuint shader_program)
    : shader_program_(shader_program)
    , c_(shader_program)
    , loc_(25, 0)
{
    for (int i = 0; i < 25; ++i)
    {
        loc_[i] = i;
    }
}

void Display::render(glm::mat4& mv)
{
    glm::mat4 mvp;
    Line l(shader_program_, loc_);

    for (int j = 0; j < 6; ++j)
    {
        for (int i = 0; i < 6; ++i)
        {
            mvp = glm::translate(glm::mat4(1.0f),
                                 glm::vec3((i * 5) - 10,
                                           (j * 5) - 10,
                                           5.0f));

            mvp = mv * mvp;
            c_.render(mvp);
        }
    }

    mvp = glm::mat4(1.0f);
    mvp = mv * mvp;
    l.render(mvp);
}