//
// Created by thero on 15.10.2022.
//

#ifndef TSP_BF_BRUTEFORCETSP_HPP
#define TSP_BF_BRUTEFORCETSP_HPP
#include <StratTSP.hpp>

class BruteForceTSP : public StratTSP
{
public:
    int solve(const std::vector<std::vector<int>> &adj_mat) override;
};

#endif //TSP_BF_BRUTEFORCETSP_HPP
