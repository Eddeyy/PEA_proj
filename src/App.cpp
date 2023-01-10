//
// Created by thero on 15.10.2022.
//
#include <App.hpp>
#include <BruteForceTSP.hpp>
#include <HeldKarpTSP.h>
#include <SimulatedAnnealingTSP.h>
#include <HeuristicStratTSP.h>

App::App(int argc, char **argv)
{
    std::ifstream config_file;
    config_file.open("tsp.ini");

    if(!config_file.good())
    {
        std::cout << stderr << "\nERROR: Couldn't open config file.\n";
        exit(-1);
    }

    std::string conf_line;
    while(std::getline(config_file,conf_line))
    {
        config_data.push_back(conf_line);
    }
    config_file.close();

    if(argc < 1)
    {
        std::cout << stderr << "\nERROR: Please provide a valid algorithm method.\n";
        exit(-1);
    }
    std::string command = argv[1];
    command.erase(command.begin(), command.begin()+2);
    if(command == "bf") { this->tsp_strat = new BruteForceTSP; method = "Brute Force"; return;}
    if(command == "dp") { this->tsp_strat = new HeldKarpTSP; method = "Dynamic programming"; return;}
    if(command == "sa") { this->tsp_strat = new SimulatedAnnealingTSP; method = "Simulated annealing"; return;}

    if(argc > 1)
        if (argv[1][0] != '-')
        {
            std::cout << stderr << "\nERROR: Unknown command - proceed commands with '-' symbol.\n";
            exit(-1);
        }

    std::cout << stderr << "\nERROR: Unknown command - please provide a valid problem solving method\n";
}

int App::run()
{
    int result;
    std::string conf_data_strings[7]; // 0 - filename, 1 - test ammount, 2 - optimal weight, 3 - optimal path, 4 - cooling ratio, 5 - start temperature, 7 - max epochs
    srand(time(NULL));
    std::ofstream output_file(config_data[config_data.size()-2]);
    std::ofstream output_file_avg(config_data[config_data.size()-1]);
    
    output_file_avg << "nazwa_inst;wielkosc_inst;sr_czas;wynik;opt_sciezka;sr_proc_bledu;mn_schl;temp_pocz;rozm_ep" << std::endl;
    
    while(config_data.size() > 2){
        double elapsed_time = 0;
        double avg_elapsed_time = 0;
        double avg_error_rate = 0;
        std::vector<double> error_rate;

        std::string &data = config_data[0];
        for(int i = 0; i < 7; i++)
        {
            conf_data_strings[i] = data.substr(0,data.find(' '));
            data.erase(data.begin(), data.begin()+data.find(' ')+1);
        }
        conf_data_strings[3] = data;

        std::vector<std::vector<int>> subject = ut::LoadFile(conf_data_strings[0]);

        if(subject.empty())
        {
            printf("Nie udalo sie wczytac pliku %s\n", conf_data_strings[0].c_str());
            config_data.erase(config_data.begin(),config_data.begin()+1);
            continue;
        }


        printf("\nRozwiazywanie %s ", conf_data_strings[0].c_str());
        printf("\nIlosc testow - %s ", conf_data_strings[1].c_str());

        time_data.clear();
        for(int i = 0; i < 3; i++)
        {
            output_file << conf_data_strings[i] << " ";
        }
        output_file << conf_data_strings[3] << std::endl;

        double coolingRatio = std::stod(conf_data_strings[4]);
        double startTemperature = std::stod(conf_data_strings[5]);
        size_t epochSize = std::stoull(conf_data_strings[6]);
        if(dynamic_cast<SimulatedAnnealingTSP*>(tsp_strat))
        {
            dynamic_cast<SimulatedAnnealingTSP *>(tsp_strat)->setCoolingRatio(coolingRatio);
            dynamic_cast<SimulatedAnnealingTSP *>(tsp_strat)->setStartTemperature(startTemperature);
            dynamic_cast<SimulatedAnnealingTSP *>(tsp_strat)->setMaxEpoch(epochSize);
        }
        for(size_t i = 0; i < std::stoi(conf_data_strings[1]); i++)
        {
            printf("\n\nTest nr %d : ", i);
            printf("\nMnoznik schladzania : %f", coolingRatio);
            printf("\nTemperatura poczatkowa : %f", startTemperature);
            printf("\nRozmiar epoki : %d", epochSize);
            ut::startCounter();
            result = this->tsp_strat->solve(subject);
            elapsed_time = ut::getCounter();
            double curr_error_rate = ((((double)result - std::stod(conf_data_strings[2]))*100.0)/(double)result);
            output_file << elapsed_time << ";";
            output_file << curr_error_rate << std::endl;
            printf("\nOperacja zajela %.6f ms czasu.", elapsed_time);
            error_rate.push_back(curr_error_rate);
            printf("\nProcent bledu : %.2f %%", error_rate[i]);
            time_data.push_back(elapsed_time);
        }

        for(auto& i : time_data)
            avg_elapsed_time+=i;

        for(auto& i : error_rate)
            avg_error_rate+=i;

        avg_elapsed_time /= std::stoi(conf_data_strings[1]);
        avg_error_rate /= std::stoi(conf_data_strings[1]);

        output_file_avg << conf_data_strings[0] << ";";
        output_file_avg << this->tsp_strat->getLatestPath().size() << ";";
        output_file_avg << elapsed_time << ";";
        output_file_avg << result << ";";
        output_file_avg << conf_data_strings[2] << ";";
        output_file_avg << avg_error_rate << ";";
        output_file_avg << coolingRatio << ";";
        output_file_avg << startTemperature << ";";
        output_file_avg << epochSize << std::endl;

        printf("\n\nWaga optymalnej sciezki wedlug pliku .ini : %s ", conf_data_strings[2].c_str());
        printf("\nRozwiazanie problemu metoda %s : %d", this->method.c_str(), result);
        printf("\nSredni procent bledu : %.2f %%", avg_error_rate);
        printf("\nOptymalna sciezka wedlug pliku .ini - %s", conf_data_strings[3].c_str());
        printf("\nOptymalna sciezka dla zadanego problemu : ");


        for (const auto& i: tsp_strat->getLatestPath())
        {
            printf("%d ", i);
        }
        printf("%d", tsp_strat->getLatestPath()[0]);

        printf("\nSredni czas wykonywania operacji to %.6f ms czasu.", avg_elapsed_time);

        config_data.erase(config_data.begin(),config_data.begin()+1);
    }
    return result;
}


