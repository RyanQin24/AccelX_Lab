#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class TimeSeries{
    public:
        void LoadCSV(std::string filename);
        void PrintData();
        void PrintMax();
        TimeSeries();
        ~TimeSeries();
    private:
        std::size_t array_size{0};
        std::size_t array_used_capacity{0};
        const std::size_t min_array_size{2};

        void doubleArray();
};
