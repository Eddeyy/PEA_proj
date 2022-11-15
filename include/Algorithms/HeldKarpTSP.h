//
// Created by thero on 06.11.2022.
//

#ifndef TSP_BF_HELDKARPTSP_H
#define TSP_BF_HELDKARPTSP_H
#include <StratTSP.hpp>
#include <iostream>
#include <map>

class HeldKarpTSP : public StratTSP
{
    size_t rec_ID = 0;
    std::map<int, int> valid_vertices;
    int heldKarp(int currentVertex, std::vector<bool> remainingVertices, int shortestPath,
                 int currentPath, const std::vector<std::vector<int>> &adj_mat, int rec = 0);
public:
    int solve(const std::vector<std::vector<int>> &adj_mat) override;
};

#endif //TSP_BF_HELDKARPTSP_H
