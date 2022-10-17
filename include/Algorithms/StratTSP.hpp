//
// Created by thero on 15.10.2022.
//

#ifndef TSP_BF_STRATTSP_HPP
#define TSP_BF_STRATTSP_HPP
#include <iostream>
#include <vector>

class StratTSP
{
protected:
    std::vector<int> latest_path;
public:
    virtual int solve(const std::vector<std::vector<int>> &adj_mat) = 0;
    std::vector<int> getLatestPath(){return this->latest_path;};
};

#endif //TSP_BF_STRATTSP_HPP
