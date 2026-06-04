#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <climits>

class TimeSeries{
    public:
        void LoadCSV(std::string filename);
        void Integrate(std::string algorithm);
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

        double g{9.80665};
        double scalar{g/16384.0};
        double time_interval{0.01};
        int g_offset{16384};
        double offset_x{0.0};
        double offset_y{0.0};
        double offset_z{0.0};
        bool IntegrateFlag{false};

        void CalcErr();
        void doubleArray();
        double VectorMagnitude(std::size_t index);
        void Trapezoidal(std::size_t index, double &x, double &y, double &z);
        void Back4Pt(std::size_t index, double &x, double &y, double &z);
};
