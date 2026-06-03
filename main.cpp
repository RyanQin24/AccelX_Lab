#include "CommandParser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main();

/*

    CITATION: External sources was used as refernece manual to find C++ standard libraries and functions for storing string inputs where strings after space must be included to
    allow CommandParser to process the entire string command. For example, I didn't want string input to store "UPDATE_P1" if user enters command "UPDATE_P1 2023 33.2". Instead, I wanted
    string input to store entire string "UPDATE_P1 2023 33.2".
    The sources included https://www.geeksforgeeks.org/cpp/getline-string-c/.

*/
int main(){
    std::string input;
    CommandParser CommandParser;
    bool run{true};
    while(run){
        std::getline(std::cin, input); 
        run = CommandParser.parseCommand(input);
    }
    return 0;
}
