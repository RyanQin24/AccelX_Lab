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
    CalcErr();
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
    std::cout << std::endl;
    std::cout << "Loaded acceleration data!" << std::endl;
}

void TimeSeries::CalcErr(){
    std::ifstream csvfile(calfile);
    std::string csvStringElement;
    std::string acc_x;
    std::string acc_y;
    std::string acc_z;
    long long x{0};
    long long y{0};
    long long z{0};
    std::size_t n{0};
    while(std::getline(csvfile,csvStringElement)){
        std::stringstream ss(csvStringElement);
        std::getline(ss,acc_x,',');
        std::getline(ss,acc_y,',');
        std::getline(ss,acc_z);
        x += std::stoi(acc_x) - g_offset;
        y += std::stoi(acc_y);
        z += std::stoi(acc_z);
        n++;
    }
    offset_x = (double)x /(double)n;
    offset_y = (double)y /(double)n;
    offset_z = (double)z /(double)n;
    std::cout << "error calculated!" << std::endl;
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
    speed_array[index].y * speed_array[index].y + speed_array[index].z * speed_array[index].z));
}