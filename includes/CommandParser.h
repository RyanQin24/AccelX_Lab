#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "TimeSeries.h"

class CommandParser{

    public:
    bool parseCommand(std::string input);
    private:
    TimeSeries timeseries;

};