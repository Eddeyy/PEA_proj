//
// Created by thero on 19.01.2023.
//

#ifndef TSP_BF_DAS_H
#define TSP_BF_DAS_H
#include <PheromoneLayout.h>
class DAS : public PheromoneLayout
{
public:
    void update(floatMatrix &tau, intMatrix& paths, const intMatrix& adj_mat) override;
};
#endif //TSP_BF_DAS_H
