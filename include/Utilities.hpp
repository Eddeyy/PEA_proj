//
// Created by thero on 16.10.2022.
//

#ifndef TSP_BF_UTILITIES_HPP
#define TSP_BF_UTILITIES_HPP

#include <iostream>
#include <cstdlib>
#include <direct.h>
#include <sys/stat.h>
#include <fstream>
#include <exception>
#include <vector>
#include <windows.h>
#include <random>

namespace ut
{
    class utilityException : public std::exception
    {
        std::string error_message;
    public:
        explicit utilityException(const std::string &msg);
        const char* what() const noexcept override {return error_message.c_str();}

    };

    static double PCFreq = 0.0;
    static __int64 CounterStart = 0;

    void startCounter();
    double getCounter();

    double random();
    bool is_path_exists(const std::string& s);
    void make_directory(const std::string& s);
    bool file_exists(const std::string& fileName, const std::string& dir);
    std::vector<std::vector<int>> LoadFile(std::string & filename);
    std::vector<std::vector<int>> LoadFileTSP(std::string & filename);
    std::vector<std::vector<int>> LoadFileATSP(std::string & filename);
    std::vector<std::vector<int>> LoadFileTXT(std::string & filename);


    template <typename T, typename D>
    bool findInPairVector(const std::vector<std::pair<T,D>>&arr, const D&target)
    {
        for(auto &i : arr)
        {
            if(i.second == target)
                return true;
        }
        return false;
    }

    template<typename Base, typename T>
    inline bool instanceof(const T *ptr) {
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }

}


#endif //TSP_BF_UTILITIES_HPP
