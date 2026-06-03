#include "TimeSeries.h"

TimeSeries::TimeSeries(){
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