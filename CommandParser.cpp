#include "CommandParser.h"

CommandParser::CommandParser(){
    std::cout << "starting" << std::endl;
}

bool CommandParser::parseCommand(std::string input){
    std::stringstream temp_args(input);
    std::string command_string;
    std::getline(temp_args,command_string,' ');

    if(command_string == "Load_CSV"){
        std::string filename;
        std::getline(temp_args,filename);
        timeseries.LoadCSV(filename);
        return true;
    }else if(command_string == "Integrate"){
        std::string temp;
        std::getline(temp_args,temp);
        std::cout << temp << std::endl;
        timeseries.Integrate(temp);
        return true;
    }else if(command_string == "TimeData"){
        timeseries.PrintData();
        return true;
    }else if(command_string == "MaxSpeed"){
        timeseries.PrintMax();
        return true;
    }else if(command_string == "EXIT"){
        std::cout << "exiting..." <<std::endl;
        return false;
    }else{
        std::cout << "exiting..." <<std::endl;
        return false;
    }
}