//
// Created by thero on 20.01.2023.
//

#ifndef TSP_BF_QAS_H
#define TSP_BF_QAS_H
#include <PheromoneLayout.h>
class QAS : public PheromoneLayout
{
public:
    void update(floatMatrix &tau, intMatrix& paths, const intMatrix& adj_mat) override;
};
#endif //TSP_BF_QAS_H
