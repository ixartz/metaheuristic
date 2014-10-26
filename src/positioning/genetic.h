//
//  genetic.h
//  metaheuristic
//
//  Created by ixi on 26/10/14.
//
//

#ifndef __metaheuristic__genetic__
#define __metaheuristic__genetic__

#include <vector>
#include <random>

class Genetic
{
public:
    /// Constructor
    Genetic(std::vector<int>& loc);

    /**
     * \brief Mutate new offspring.
     */
    void mutate();

    /**
     * \brief Cross over the parents to form offspring.
     */
    std::vector<int> cross_over(int l, int r);

    /// Return the best
    std::vector<int>& get_best();

private:
    std::mt19937 eng_;
    std::uniform_int_distribution<uint32_t> uint_dist_;

    std::vector<std::vector<int>> pop_;
};

#endif /* defined(__metaheuristic__genetic__) */
