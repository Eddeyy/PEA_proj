//
// Created by thero on 17.12.2022.
//

#ifndef TSP_BF_SIMULATEDANNEALINGTSP_H
#define TSP_BF_SIMULATEDANNEALINGTSP_H
#include <iostream>
#include <StratTSP.hpp>
#include <HeuristicStratTSP.h>

class SimulatedAnnealingTSP : public StratTSP, HeuristicStratTSP
{
    double _coolingRatio = 0.999;
    double _startTemperature = 1000;
    size_t max_epoch = 100;

private:

    int calculateCost(const std::vector<std::vector<int>> &adj_mat, std::vector<int> &vertices);
    double calculatePropability(const int delta, const double temperature);
    bool makeDecision(const int delta, const double temperature);
    double propabilityOnSamples(const int delta, const double temperature, const int samples);
    void changeOrder(std::vector<int> &vertices);

public:
    int solve(const std::vector<std::vector<int>> &adj_mat) override;
    std::vector<int> getInitialSolution(size_t verticesNumber);

    SimulatedAnnealingTSP(): HeuristicStratTSP(2){};

    SimulatedAnnealingTSP(double coolingRatio, double startTemperature):
    HeuristicStratTSP(2),
    _coolingRatio{coolingRatio}, _startTemperature{startTemperature}{}

    void setCoolingRatio(double coolingRatio){this->_coolingRatio = coolingRatio;};
    void setStartTemperature(double startTemperature){this->_startTemperature = startTemperature;};
    void setMaxEpoch(size_t maxEpoch);
};

#endif //TSP_BF_SIMULATEDANNEALINGTSP_H
