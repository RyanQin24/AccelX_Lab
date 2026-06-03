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
        return true;
    }else if(command_string == "TimeData"){
        return true;
    }else if(command_string == "Max_Speed"){
        return true;
    }else if(command_string == "EXIT"){
        return false;
    }else{
        return false;
    }
}