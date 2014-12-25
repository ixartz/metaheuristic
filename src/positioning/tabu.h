//
//  tabu.h
//  metaheuristic
//
//  Created by ixi on 26/10/14.
//
//

#ifndef __metaheuristic__tabu__
#define __metaheuristic__tabu__

#include <limits>
#include <vector>
#include <utility>
#include <algorithm>
#include "display.h"

class Tabu
{
public:
    /// Constructor
    Tabu(Display& d);

    /**
     * \brief Tabu search algorithm.
     */
    float search();

private:
    /**
     * \brief Compute next list position.
     */
    void next_pos_();

private:
    std::mt19937 eng_;
    std::uniform_int_distribution<uint32_t> uint_dist_;

    std::vector<std::pair<int, int>> list_;
    unsigned int pos_;

    Display& d_;
};

#endif /* defined(__metaheuristic__tabu__) */
