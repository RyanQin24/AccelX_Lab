#include "TimeSeries.h"

TimeSeries::TimeSeries(){
    array_size = min_array_size;
    speed_array = new speed_data[min_array_size];
    acceleration_array = new acceleration_data[min_array_size];
}

TimeSeries::~TimeSeries(){
    delete[] speed_array;
    delete[] acceleration_array;
    array_size = 0;
    array_used_capacity = 0;
}

void TimeSeries::LoadCSV(std::string filename){
    std::ifstream csvfile(filename);
    std::string csvStringElement;
    std::string x;
    std::string y;
    std::string z;
    while(std::getline(csvfile,csvStringElement)){
        std::stringstream ss(csvStringElement);
        std::getline(ss,x,',');
        std::getline(ss,y,',');
        std::getline(ss,z);
        if(array_used_capacity >= array_size){
            doubleArray();
        }
        acceleration_array[array_used_capacity].x = std::stoi(x);
        acceleration_array[array_used_capacity].y = std::stoi(y);
        acceleration_array[array_used_capacity].z = std::stoi(z);
        array_used_capacity++;
    }
    std::cout << "success" << std::endl;
}

void TimeSeries::doubleArray(){
    speed_data* temp = speed_array;
    acceleration_data* tempacc = acceleration_array;
    speed_array = new speed_data[array_size * 2];
    acceleration_array = new acceleration_data[array_size * 2];
    array_size = array_size * 2;
    for(std::size_t i = 0; i < array_used_capacity; i++){
        speed_array[i] = temp[i];
        acceleration_array[i] = tempacc[i];
    }
    temp = nullptr;
    tempacc = nullptr;
}

double TimeSeries::VectorMagnitude(std::size_t index){
    return sqrt((speed_array[index].x * speed_array[index].x + 
    speed_array[index].y * speed_array[index].y + speed_array[index].z * speed_array[index].z));;
}