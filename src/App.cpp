//
// Created by thero on 15.10.2022.
//
#include <App.hpp>
#include <BruteForceTSP.hpp>

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

    if(argc > 2)
    {
        std::cout << stderr << "\nERROR: Too many commands provided. Provide only the algorithm strategy.\n";
        exit(-1);
    }

    if(argc > 1)
        if (argv[1][0] != '-')
        {
            std::cout << stderr << "\nERROR: Unknown command - proceed commands with '-' symbol.\n";
            exit(-1);
        }


    std::string command = argv[1];

    command.erase(command.begin(), command.begin()+2);

    if(command == "bf") { this->tsp_strat = new BruteForceTSP; method = "Brute Force"; return;}

    std::cout << stderr << "\nERROR: Unknown command - please provide a valid problem solving method\n";
}

int App::run()
{
    int result;
    std::string conf_data_strings[4]; // 0 - filename, 1 - test ammount, 2 - optimal weight, 3 - optimal path

    std::ofstream output_file(config_data[config_data.size()-1]);
    while(config_data.size() > 1){
        double elapsed_time = 0;
        double avg_elapsed_time = 0;

        std::string &data = config_data[0];
        for(int i = 0; i < 3; i++)
        {
            conf_data_strings[i] = data.substr(0,data.find(' '));
            data.erase(data.begin(), data.begin()+data.find(' ')+1);
        }
        conf_data_strings[3] = data;

        std::vector<std::vector<int>> subject = ut::LoadFile(conf_data_strings[0]);

        if(subject.empty())
        {
            printf("Nie udało się wczytać pliku %s\n", conf_data_strings[0].c_str());
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

        for(size_t i = 0; i < std::stoi(conf_data_strings[1]); i++)
        {
            printf("\nTest nr %d : ", i);
            ut::startCounter();
            result = this->tsp_strat->solve(subject);
            elapsed_time = ut::getCounter();
            output_file << elapsed_time << std::endl;
            printf("Operacja zajela %.6f ms czasu.", elapsed_time);
            time_data.push_back(elapsed_time);
        }
        for(auto& i : time_data)
        {
            avg_elapsed_time+=i;
        }
        avg_elapsed_time /= std::stoi(conf_data_strings[1]);



        printf("\n\nWaga optymalnej sciezki wedlug pliku .ini : %s ", conf_data_strings[2].c_str());
        printf("\nRozwiazanie problemu metoda %s : %d", this->method.c_str(), result);

        printf("\nOptymalna sciezka wedlug pliku .ini - %s", conf_data_strings[3].c_str());
        printf("\nOptymalna sciezka dla zadanego problemu : ");

        printf("0 ");
        for (auto i: tsp_strat->getLatestPath())
        {
            printf("%d ", i);
        }
        printf("0");

        printf("\nSredni czas wykonywania operacji to %.6f ms czasu.", avg_elapsed_time);

        config_data.erase(config_data.begin(),config_data.begin()+1);
    }
    return result;
}


