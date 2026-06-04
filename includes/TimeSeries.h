#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>

class TimeSeries{
    public:
        void LoadCSV(std::string filename);
        void Integrate();
        void PrintData();
        void PrintMax();
        TimeSeries();
        ~TimeSeries();
    private:
        class speed_data{
            public:
            double x{0.0};
            double y{0.0};
            double z{0.0};
            double magnitude{0.0};
        };
        class acceleration_data{
            public:
            int x{0};
            int y{0};
            int z{0};
            double ax{0.0};
            double ay{0.0};
            double az{0.0};
        };

        std::size_t array_size{0};
        std::size_t array_used_capacity{0};
        const std::size_t min_array_size{2};
        speed_data* speed_array = nullptr;
        acceleration_data* acceleration_array = nullptr;

        const std::string calfile = "calibration_data/cal.csv";

        double scalar{1.0/16384.0};
        int g_offset{16384};
        double g{9.80665};
        double offset_x{};
        double offset_y{};
        double offset_z{};

        void doubleArray();
        double VectorMagnitude(std::size_t index);
        void ProcessAcceleration();
};
