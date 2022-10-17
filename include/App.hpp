//
// Created by thero on 15.10.2022.
//

#ifndef TSP_BF_APP_HPP
#define TSP_BF_APP_HPP
#include <iostream>
#include <StratTSP.hpp>
#include <Utilities.hpp>

class App
{
    StratTSP* tsp_strat = nullptr;
    std::string method;

    std::vector<std::string> config_data;
    std::vector<double> time_data;


public:
    App(int argc, char *argv[]);
    int run();
};

#endif //TSP_BF_APP_HPP
