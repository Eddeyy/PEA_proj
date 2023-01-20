//
// Created by thero on 15.01.2023.
//

#ifndef TSP_BF_ANTCOLONYOPTIMIZATIONTSP_H
#define TSP_BF_ANTCOLONYOPTIMIZATIONTSP_H

#include <iostream>
#include <vector>
#include <HeuristicStratTSP.h>
#include <StratTSP.hpp>
#include <PheromoneLayout.h>
#include <cmath>
#include <numeric>
#include <algorithm>

class AntColonyOptimizationTSP : public StratTSP, HeuristicStratTSP
{
    using intMatrix = std::vector<std::vector<int>>;
    using floatMatrix = std::vector<std::vector<float>>;

public:

    AntColonyOptimizationTSP(double _alpha, double _beta);
    int solve(const std::vector<std::vector<int>> &adj_mat) override;


    void setPheromoneLayout(PheromoneLayout* pheromoneLayout)
    {
        delete this->pheromoneLayout;
        this->pheromoneLayout = pheromoneLayout;
    }
    void setBeta(double beta);

    void setAlpha(double alpha);
private:

    double alpha;

private:
    double beta;
    double q;
    double rho;

    PheromoneLayout* pheromoneLayout;

    static void placeAnts(std::vector<int> &uh);
    static bool isSinglePath(const std::vector<int> &costs);

    double calcPropability(floatMatrix& tau, std::vector<int>& tabu, const intMatrix& adj_mat, size_t i, size_t j) const;

};

#endif //TSP_BF_ANTCOLONYOPTIMIZATIONTSP_H
