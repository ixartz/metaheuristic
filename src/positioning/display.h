//
//  display.h
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#ifndef __metaheuristic__display__
#define __metaheuristic__display__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <random>
#include "../model/cube.h"
#include "../model/line.h"

class Display
{
public:
    /// Constructor
    Display(GLuint shader_program);

    /**
     * \brief Render the positioning of the electronic components.
     */
    void render(glm::mat4& mv);

    /**
     * \brief Compute the cost.
     */
    float compute_cost();

    /**
     * \brief Compute the x location.
     */
    float compute_x(int block);

    /**
     * \brief Compute the y location.
     */
    float compute_y(int block);

    /// Return the loc vector
    std::vector<int>& get_loc();

    /// Set the loc vector
    void set_loc(std::vector<int>& loc);

private:
    /**
     * \brief Compute the Manhattan distance.
     */
    float dist_(int i, int j);

private:
    GLuint shader_program_;
    Cube c_;

    std::vector<int> loc_;
};

#endif /* defined(__metaheuristic__display__) */
