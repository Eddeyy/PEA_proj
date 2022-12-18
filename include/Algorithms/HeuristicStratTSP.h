//
// Created by thero on 17.12.2022.
//

#ifndef TSP_BF_HEURISTICSTRAT_H
#define TSP_BF_HEURISTICSTRAT_H
#include <iostream>
class HeuristicStratTSP
{
protected:
    const size_t param_count = 0;

    explicit HeuristicStratTSP(size_t paramCount):
    param_count{paramCount}{};

public:
    size_t getParamCount(){return this->param_count;};
};

#endif //TSP_BF_HEURISTICSTRAT_H
