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

    // Random shuffle
    /*
    srand(time(NULL));
    for (int i = 24; i > 0; --i)
    {
        std::swap(loc_[i], loc_[rand() % (i + 1)]);
    }
    */
}

void Display::render(glm::mat4& mv)
{
    glm::mat4 mvp;
    Line l(shader_program_, this);

    for (int j = 0; j < 6; ++j)
    {
        for (int i = 0; i < 6; ++i)
        {
            mvp = glm::translate(glm::mat4(1.0f),
                                 glm::vec3((i * 5.5) - 11,
                                           (j * 5.5) - 11,
                                           5.0f));

            mvp = mv * mvp;
            c_.render(mvp);
        }
    }

    mvp = glm::mat4(1.0f);
    mvp = mv * mvp;
    l.render(mvp);
}

float Display::compute_cost()
{
    float cost = 0.0f;

    for (unsigned i = 0; i < loc_.size(); ++i)
    {
        if (i % 5 < 4)
        {
            cost += dist_(i, i + 1);
        }

        if (i / 5 < 4)
        {
            cost += dist_(i, i + 5);
        }
    }

    return cost;
}

float Display::compute_x(int block)
{
    return loc_[block] / 5 * -5.0f + 10.0f;
}

float Display::compute_y(int block)
{
    return loc_[block] % 5 * -5.0f + 10.0f;
}

std::vector<int>& Display::get_loc()
{
    return loc_;
}

float Display::dist_(int i, int j)
{
    return sqrt(pow(compute_x(j) - compute_x(i), 2) +
                pow(compute_y(j) - compute_y(i), 2));
}