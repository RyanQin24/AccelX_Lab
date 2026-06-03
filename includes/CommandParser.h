#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "TimeSeries.h"

class CommandParser{

    public:
    CommandParser();
    bool parseCommand(std::string input);
    private:
    TimeSeries timeseries;

};