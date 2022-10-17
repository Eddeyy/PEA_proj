//
// Created by thero on 16.10.2022.
//
#include <Utilities.hpp>


bool ut::is_path_exists(const std::string& s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

void ut::make_directory(const std::string& s)
{
    if (_mkdir(s.c_str()) != 0)
    {
        throw ut::utilityException("Unable to create directory \"" + s + "\"");
    }
}

bool ut::file_exists(const std::string& fileName, const std::string& dir)
{
    std::ifstream infile(dir + fileName);
    return infile.good();
}

std::vector<std::vector<int>>  ut::LoadFile(std::string &filename) {

    /*if (numberOfVertices != 0) {
        for (int i = 0; i < numberOfVertices; i++)
            delete vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
    }*/
    std::string fileExt = filename.substr(filename.find_last_of(".") + 1);
    if (fileExt != "txt" && fileExt != "tsp" && fileExt != "atsp") //dodanie do nazwy pliku rozszerzenia .txt gdy go nie ma
    {
        filename += ".txt";
    }
    fileExt = filename.substr(filename.find_last_of(".") + 1);

    if (fileExt == "txt") {
        return ut::LoadFileTXT(filename);
    }

    if (fileExt == "tsp") {
        return ut::LoadFileTSP(filename);
    }

    if (fileExt == "atsp") {
        return ut::LoadFileATSP(filename);
    }

    return {};
}

std::vector<std::vector<int>> ut::LoadFileTXT(std::string & filename)
{
    std::fstream File;
    File.open(filename, std::ios::in);
    if (!File.good()) {
        std::cout << "\nNie mozna wczytac pliku!\n";
        return {};
    }

    int vertex_number;
    File >> vertex_number;
    std::vector<std::vector<int>> vertices;

    vertices.resize(vertex_number);

    for(auto &v : vertices)
        v.resize(vertex_number);

    int line = 0;

    while (!File.eof()) {
        for (int i = 0; i < vertex_number; i++) {
            for (int j = 0; j < vertex_number; j++) {
                File >> vertices[i][j];
            }

            line++;
        }
    }
    File.close();

    if (line != vertex_number && line != vertex_number * 2) { // zabezpieczenie pir
        std::cout << "-> Zla ilosc danych <-\n";
        return {};
    }
    std::cout << "\nWczytano plik tekstowy!\n";
    return vertices;
}

std::vector<std::vector<int>> ut::LoadFileTSP(std::string & filename)
{
    std::ifstream File;
    File.open(filename, std::ios::in);
    if (!File.good()) {
        std::cout << "\nNie mozna wczytac pliku!\n";
        return {};
    }

    int vertex_number;
    std::vector<std::vector<int>> vertices;

    std::string line;
    while (!File.eof()) {
        getline(File, line);
        {
            if (!line.compare(0, 6, "TYPE: ")) {
                if (!line.compare(7, 3, "TSP")) {
                    std::cout << "\n To nie jest plik TSP\n"; // czy typ pliku to TSP
                    return {};
                }

            }
            else if (!line.compare(0, 7, "TYPE : ")) {
                if (!line.compare(8, 3, "TSP")) {
                    std::cout << "\n To nie jest plik TSP\n"; // czy typ pliku to TSP
                    return {};
                }
            }

            if (!line.compare(0, 11, "DIMENSION: ")) {
                std::string number = line.substr(11, 100);
                vertex_number = stoi(number); //zapisanie ilo�ci wierzcho�k�w
            }
            else if (!line.compare(0, 12, "DIMENSION : ")) {
                std::string number = line.substr(12, 100);
                vertex_number = stoi(number); //zapisanie ilo�ci wierzcho�k�w
            }

            if (!line.compare(0, 18, "EDGE_WEIGHT_TYPE: ")) {
                if (!line.compare(19, 8, "EXPLICIT")) {
                    std::cout << "\n Nieobslugiwany typ danych\n"; // czy zapisano jako wagi kraw�dzi
                    return {};
                }
            }
            else if (!line.compare(0, 19, "EDGE_WEIGHT_TYPE : ")) {
                if (!line.compare(20, 8, "EXPLICIT")) {
                    std::cout << "\n Nieobslugiwany typ danych\n"; // czy zapisano jako wagi kraw�dzi
                    return {};
                }
            }


            if (!line.compare(0, 20, "EDGE_WEIGHT_FORMAT: ")) { //Obs�uga r�nego typu zapisu macierzy
                if (!line.compare(20, 11, "FULL_MATRIX")) {

                    vertices.resize(vertex_number);

                    for(auto &v : vertices)
                        v.resize(vertex_number);

                    std::string temp;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < vertex_number; j++)
                                for (int k = 0; k < vertex_number; k++)
                                    File >> vertices[j][k];
                        }
                    }
                }
                else if (!line.compare(20, 14, "LOWER_DIAG_ROW")) {

                    vertices.resize(vertex_number);

                    for(auto &v : vertices)
                        v.resize(vertex_number);

                    std::string temp;
                    int line_num = 1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < vertex_number; j++) {
                                for (int k = 0; k < line_num; k++) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line_num < vertex_number)
                                    line_num++;
                            }

                        }
                    }
                }
                else if (!line.compare(20, 14, "UPPER_DIAG_ROW")) {

                    vertices.resize(vertex_number);

                    for(auto &v : vertices)
                        v.resize(vertex_number);

                    std::string temp;
                    int line_num = vertex_number - 1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = vertex_number-1; j >= 0; j--) {
                                for (int k = line_num; k >= 0; k--) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line_num >= 0)
                                    line_num--;
                            }
                        }
                    }
                }
                else {
                    std::cout << "\nNieobs�ugiwany format macierzy\n";
                    return {};
                }
            }

            else if (!line.compare(0, 21, "EDGE_WEIGHT_FORMAT : ")) { //Obs�uga r�nego typu zapisu macierzy
                if (!line.compare(21, 11, "FULL_MATRIX")) {

                    vertices.resize(vertex_number);

                    for(auto &v : vertices)
                        v.resize(vertex_number);

                    std::string temp;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < vertex_number; j++)
                                for (int k = 0; k < vertex_number; k++)
                                    File >> vertices[j][k];
                        }
                    }
                }
                else if (!line.compare(21, 14, "LOWER_DIAG_ROW")) {

                    vertices.resize(vertex_number);

                    for(auto &v : vertices)
                        v.resize(vertex_number);

                    std::string temp;
                    int line_num = 1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < vertex_number; j++) {
                                for (int k = 0; k < line_num; k++) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line_num < vertex_number)
                                    line_num++;
                            }

                        }
                    }
                }
                else if (!line.compare(21, 14, "UPPER_DIAG_ROW")) {

                    vertices.resize(vertex_number);

                    for(auto &v : vertices)
                        v.resize(vertex_number);

                    std::string temp;
                    int line_num = vertex_number - 1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = vertex_number - 1; j >= 0; j--) {
                                for (int k = line_num; k >= 0; k--) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line_num >= 0)
                                    line_num--;
                            }
                        }
                    }
                }
                else {
                    std::cout << "\nNieobslugiwany format macierzy\n";
                    return {};
                }
            }
        }

    }
    File.close();
    std::cout << "\nWczytano plik TSP!\n";
    return vertices;
}

std::vector<std::vector<int>> ut::LoadFileATSP(std::string & filename)
{
    std::ifstream File;
    File.open(filename, std::ios::in);
    if (!File.good()) {
        std::cout << "\nNie mozna wczytac pliku!\n";
        return {};
    }


    int vertex_number;
    std::vector<std::vector<int>> vertices;

    std::string line;
    while (!File.eof()) {
        getline(File, line);
        {
            if (!line.compare(0, 6, "TYPE: "))
                if (!line.compare(7, 4, "ATSP")) {
                    std::cout << "\n To nie jest plik ATSP\n"; // czy typ pliku to ATSP
                    return {};
                }

            if (!line.compare(0, 11, "DIMENSION: ")) {
                std::string number = line.substr(11, 100);
                vertex_number = stoi(number); //zapisanie ilo�ci wierzcho�k�w
            }
            if (!line.compare(0, 18, "EDGE_WEIGHT_TYPE: "))
                if (!line.compare(19, 8, "EXPLICIT")) {
                    std::cout << "\n Nieobslugiwany typ danych\n"; // czy zapisano jako wagi kraw�dzi
                    return {};
                }
            if (!line.compare(0, 20, "EDGE_WEIGHT_FORMAT: ")) { //Obs�uga r�nego typu zapisu macierzy
                if (!line.compare(20, 11, "FULL_MATRIX")) {

                    vertices.resize(vertex_number);

                    for(auto &v : vertices)
                        v.resize(vertex_number);

                    std::string temp;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < vertex_number; j++)
                                for (int k = 0; k < vertex_number; k++)
                                    File >> vertices[j][k];
                        }
                    }
                }
                else {
                    std::cout << "\nNieobslugiwany format macierzy\n";
                    return {};
                }
            }
        }

    }
    File.close();
    std::cout << "\nWczytano plik ATSP!\n";
    return vertices;
}

ut::utilityException::utilityException(const std::string& msg)
        : error_message{msg}
{};

void ut::startCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    ut::PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    ut::CounterStart = li.QuadPart;
}

double ut::getCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-ut::CounterStart)/ut::PCFreq;
}

